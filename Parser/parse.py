import sys
import shlex
import re

import xml.etree.ElementTree as ET
from xml.dom import minidom

def safe_get(lst, index, default=None):
    if lst == None:
        return default
    return lst[index] if 0 <= index < len(lst) else default

def is_build_in_class(word):
    if word == "Object":
        return True
    if word == "Nil":
        return True
    if word == "True":
        return True
    if word == "False":
        return True
    if word == "Integer":
        return True
    if word == "String":
        return True
    if word == "Block":
        return True

    return False

def tokenize(code):
    token_pattern = re.compile(r"""
    "[^"]*"                # Zachytí celé řetězce v uvozovkách
    | '[^']*'              # Zachytí text v jednoduchých uvozovkách
    | \:\w+               # Zachytí klíčové slovo s dvojtečkou, např. ":x"
    | \w+\:               # Zachytí slovo s dvojtečkou na konci, např. "from:"
    | :=                  # Zachytí ":="
    | [\[\]{}().,:|]       # Zachytí speciální znaky
    | \w+                 # Zachytí běžná slova
""", re.VERBOSE)

    description = ""
    
    words = token_pattern.findall(code)

    tokens = []
    for i, word in enumerate(words):
        unrecognized = True

        # Textový řetězec
        if '"' in word:
            if description == "":
                description = word
            unrecognized = False
        
        elif "'" in word:
            tokens.append(("String", word))
            unrecognized = False
        
        elif word.isdigit():
            tokens.append(("Integer", word))
            unrecognized = False

        elif "[" in word:
            tokens.append(("zacatek bloku", word))
            unrecognized = False
        
        elif "|" in word:
            tokens.append(("stred bloku", word))
            unrecognized = False
        
        elif "]" in word:
            tokens.append(("konec bloku", word))
            unrecognized = False

        elif "}" in word:
            tokens.append(("konec tridy", word))
            unrecognized = False

        # Možná zbytečný
        elif word == "true":
            tokens.append(("true", word))
            unrecognized = False

        # Možná zbytečný
        elif word == "false":
            tokens.append(("false", word))
            unrecognized = False

        # Vestavěné třídy
        elif is_build_in_class(word):
            tokens.append(("BUILDINCLASS", word))
            unrecognized = False

        elif word == ":=":
            tokens.append(("Assign", word))
            unrecognized = False

        elif re.fullmatch(r'^:?[a-zA-Z0-9_]+:?$', word):
            if word[0] == ':':
                tokens.append(("Parameter", word))
            elif word[-1] == ':':
                tokens.append(("Selector", word))
            elif word[0].isupper():
                tokens.append(("Class", word))
            else:
                tokens.append(("Argument", word))

            unrecognized = False

        # Nerozpoznaný token
        if unrecognized:
            tokens.append(("other", word))

    return tokens, description

def tokens_to_xml(tokens):
    xml = [] # [0] - jmeno parametru, pak hodnoty [1] [2]
    num_of_starts_blocks = 0
    num_of_starts_brace = 0
    assign_order = 0
    assign_order_stack = []
    for index, (token_type, token) in enumerate(tokens):
        xml1 = []
        next_token = safe_get(tokens, index + 1)
        next_token_name = ""
        if next_token:
            next_token_name = next_token[1]

        print(f"{num_of_starts_blocks} {num_of_starts_brace} {index} {token_type} {token}")
        # class_name = Název třídy
        # parent_class = Rodič, pokud existuje (musí se kontrolovat, zda není prázdný řetězec)
        if token == "class":
            class_name = tokens[index + 1][1]
            parent_class = ""
            if tokens[index + 2][1] == ":":
                parent_class = tokens[index + 3][1]

            tokens.pop(index + 3)
            tokens.pop(index + 2)
            tokens.pop(index + 1)

            xml.append(("class", class_name, parent_class))
            print(f"{class_name} {parent_class}")

        # Metoda - name = Název metody
        elif (token_type == "Selector" or token_type == "Argument" and next_token_name == "[") and num_of_starts_brace == 0 and num_of_starts_blocks == 0 and next_token_name != ":=" and (':' in next_token_name or next_token_name == "["):
            method_name = ""
            
            if next_token:
                if next_token[0] == "Selector":
                    method_name += tokens[index][1]
                    while tokens[index + 1][0] == "Selector":
                        method_name += tokens[index + 1][1]
                        tokens.pop(index + 1)
                else:
                    method_name = token
            
            xml.append(("method", method_name))
            print(f"metoda: {method_name}")
        
        # Začátek bloku - arity = arity
        # Parameters - parameters[index] = Název; index + 1 = order
        elif token_type == "zacatek bloku":
            assign_order_stack.append(assign_order)
            assign_order = 0
            parameters = []
            arity = 0
            while tokens[index + 1][0] == "Parameter":
                parameters.append(tokens[index + 1][1])
                tokens.pop(index + 1)
                arity += 1

            num_of_starts_blocks += 1

            xml.append(("block", arity))
            for i, param in enumerate(parameters):
                xml.append(("parameter", i + 1, param))

            print(f"{parameters} {arity}")

        elif token_type == "konec bloku":
            if assign_order_stack != []:
                assign_order = assign_order_stack.pop()
            num_of_starts_blocks -= 1
            xml.append(("konec bloku", ""))

        elif token == "(":
            con = True
            arr = []
            while con:

                if tokens[index][1] == "(":
                    num_of_starts_brace += 1
                    tokens.pop(index)
                elif tokens[index][1] == ")":
                    num_of_starts_brace -= 1
                else:
                    arr.append(tokens[index])
                    tokens.pop(index)

                if num_of_starts_brace == 0:
                    con = False
            print(f"test: {arr}")
            xml1 = tokens_to_xml(arr)
        elif token == ")":
            num_of_starts_brace -= 1

        # assign_order = Pořadí přiřazení
        # assign_var = Proměnná, do které se přiřazení uloží
        elif token_type == "Assign":
            assign_order += 1
            assign_var = tokens[index - 1][1]
            assign_expr = []
            assign_send = ""
            assign_arg = []

            hranata = False

            if safe_get(tokens, index + 1)[1] != "(" and safe_get(tokens, index + 1)[1] != "[":
                assign_expr = tokens[index + 1]
                    
            else:
                if tokens[index + 1][1] == "[":
                    hranata = True
                num_of_brace = 1
                assign_expr.append(tokens[index + 1])
                while num_of_brace > 0:
                    if tokens[index + 2][1] == "(" or tokens[index + 2][1] == "[":
                        num_of_brace += 1
                    elif tokens[index + 2][1] == ")" or tokens[index + 2][1] == "]":
                        num_of_brace -= 1
                    
                    assign_expr.append(tokens[index + 2])
                    tokens.pop(index + 2)

            if tokens[index + 2][1] == "ifTrue:" or tokens[index + 2][1] == "ifFalse:":
                assign_send = "ifTrue:ifFalse:"
                end = 1
                body = []
                body.append(tokens[index + 3])
                tokens.pop(index + 3)

                while end > 0:
                    body.append(tokens[index + 3])
                    
                    if tokens[index + 3][1] == "[":
                        end += 1
                    elif tokens[index + 3][1] == "]":
                        end -= 1
                    
                    tokens.pop(index + 3)

                # Zde se ještě musí popnout vše co je v else větvi
                tokens.pop(index + 3) #ifElse:
                body = []
                body.append(tokens[index + 3])
                tokens.pop(index + 3) #[
                end = 1
                while end > 0:
                    body.append(tokens[index + 3])

                    if tokens[index + 3][1] == "[":
                        end += 1
                    elif tokens[index + 3][1] == "]":
                        end -= 1
                    
                    tokens.pop(index + 3)
                tokens.pop(index + 2)
            elif not hranata:
                counter = 0
                while tokens[index + 2][1] != ".":
                    if tokens[index + 2][0] == "Selector" or (counter % 2 == 0 and ':' not in assign_send):
                        assign_send += tokens[index + 2][1]
                    elif tokens[index + 2][0] == "Argument" or tokens[index + 2][0] == "String" or tokens[index + 2][0] == "Integer":
                        assign_arg.append(tokens[index + 2])
                    tokens.pop(index + 2)
                    counter += 1

            tokens.pop(index + 1)

            if assign_expr[0][1] == "[" or assign_expr[0][1] == "(":
                print("TADY:")
                xml1 = tokens_to_xml(assign_expr)
                print("--------------------")

            xml.append(("assign", assign_order))
            xml.append(("var", assign_var))
            if xml1 != []:
                for x in xml1:
                    xml.append(x)
            else:
                if assign_send != "":
                    xml.append(("expr", ""))
                    xml.append(("send", assign_send))
                xml.append(("expr", ""))
                if not isinstance(assign_expr, list):
                    if assign_expr[0] == "Argument":
                        xml.append(("var", assign_expr[1]))
                    else:
                        xml.append(("literal", assign_expr[0], assign_expr[1]))
                for i, arg in enumerate(assign_arg):
                    xml.append(("arg", i + 1))
                    xml.append(("expr", ""))
                    if arg[0] == "Argument":
                        xml.append(("var", arg[1]))
                    else:
                        xml.append(("literal", arg[0], arg[1]))

            print(f"{assign_order} {assign_var} = {assign_expr} {assign_send} {assign_arg}")

        elif token_type == "konec tridy":
            xml.append(("konec tridy", ""))
        else:
            print("ELSE")

    return xml

    # -------------------------------------------

def generate_xml(xml_tokens, description):
    root = ET.Element("program", language="SOL25", description=description)
    recurse = []
    recurse.append(root)
    class_element = ""
    method_element = ""

    for i, token in enumerate(xml_tokens):
        parent = recurse[-1].tag
        if token[0] == "class":
            recurse.append(ET.SubElement(recurse[-1], token[0], name=token[1], parent=token[2]))
        elif token[0] == "method":
            while not(parent == "class"):
                recurse.pop()
                parent = recurse[-1].tag
            recurse.append(ET.SubElement(recurse[-1], token[0], selector=token[1]))
        elif token[0] == "block":
            recurse.append(ET.SubElement(recurse[-1], token[0], artiy=str(token[1])))
        elif token[0] == "assign":
            while not(parent == "program" or parent == "class" or parent == "block"):
                recurse.pop()
                parent = recurse[-1].tag
            recurse.append(ET.SubElement(recurse[-1], token[0], order=str(token[1])))
        elif token[0] == "var":
            ET.SubElement(recurse[-1], token[0], name=token[1])
            if parent == "expr":
                recurse.pop()
        elif token[0] == "literal":
            ET.SubElement(recurse[-1], token[0], {"class": token[1]}, value=str(token[2]))
            if parent == "expr":
                recurse.pop()
        elif token[0] == "expr":
            recurse.append(ET.SubElement(recurse[-1], token[0]))
        elif token[0] == "send":
            recurse.append(ET.SubElement(recurse[-1], token[0], selector=token[1]))
        elif token[0] == "arg":
            if parent == "expr":
                recurse.pop()
            if recurse[-1].tag == "arg":
                recurse.pop()
            recurse.append(ET.SubElement(recurse[-1], token[0], order=str(token[1])))
        elif token[0] == "parameter":
            ET.SubElement(recurse[-1], token[0], order=str(token[1]), name = token[2])
        elif token[0] == "konec tridy":
            while parent != "program":
                recurse.pop()
                parent = recurse[-1].tag
        elif token[0] == "konec bloku":
            while parent != "block":
                recurse.pop()
                parent = recurse[-1].tag
            recurse.pop()
        else:
            ET.SubElement(root, token[0], name="ELSE--------------")

    # Vygenerování XML řetězce s odsazením
    xml_str = ET.tostring(root, encoding="utf-8").decode("utf-8")

    # Přidání deklarace na začátek souboru
    xml_declaration = '<?xml version="1.0" encoding="UTF-8"?>'
    xml_output = xml_declaration + xml_str

    return xml_output

        
def print_help():
    print(f"Jak používat script")

def main():
    args_list = sys.argv[1:]
    
    # Případ, kdy je jeden z parametrů --help
    if "--help" in args_list:
        if len(args_list) == 1:
            print_help()
            exit(0)
        else:
            exit(10)

    # Klíčová slova:
    # class, self, super, nil, true, false
    # Object, Nil, True, False, Integer, String, Block

    # Načte celý kód na vstupu
    code = sys.stdin.read()

    print("TOKENS:")
    tokens, description = tokenize(code)
    for token_type, token in tokens:
        print(f"{token_type}: {token}")

    xml_tokens = tokens_to_xml(tokens)

    print("------------ XML --------------")
    #for t in xml_tokens:
    #    print(t)
    print(xml_tokens)

    output = generate_xml(xml_tokens, description)

    for char in output:
        print(char, end="")
        if char == '>':
            print()

if __name__ == "__main__":
    main()

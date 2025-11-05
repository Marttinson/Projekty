import sys
import xml.etree.ElementTree as ET
from xml.dom import minidom

def print_help():
    print("Nápověda:")
    print("  --help        Zobrazí tuto nápovědu.")
    print("Použití:")
    print("  script.py <pozicovany_argument> [--volitelny_argument <hodnota>]")

def is_var(slovo):
    return not(not("GF@" in slovo) and not("LF@" in slovo) and not("TF@" in slovo))

def is_type(slovo):
    return not(not("int" in slovo) and not("bool" in slovo) and not("string" in slovo)) and not('@' in slovo)

def is_litral(slovo):
    # Kontrola zda se v řetězci vyskytuje '\'
    if "string@" in slovo:
        if '\\' in slovo:
            pozice = slovo.find("\\")
            if not(pozice != -1 and pozice + 4 <= len(slovo) and slovo[pozice + 1:pozice + 4].isdigit()):
                sys.exit(23)

    # Kontrola zda je správně zadáno číslo (podporuje hexadecimální, oktálovou a pochopitelně desítkovou)
    if "int@" in slovo:
        if 'o' in slovo:
            cislo = slovo.split('o')
            if '8' in cislo[1] or '9' in cislo[1] or any(char.isalpha() for char in cislo[1]):
                sys.exit(23)
        elif 'x' in slovo:
            cislo = slovo.split('x')
            if any(char.isalpha() and 'g' <= char.lower() <= 'z' for char in cislo[1]):
                sys.exit(23)
    return not(not("int@" in slovo) and not("bool@" in slovo) and not("string@" in slovo) and not("nil@" in slovo))

def main():
    # Kontrola argumentu --help
    if "--help" in sys.argv[1:]:
        if len(sys.argv) > 2:
            sys.exit(10)
        else:
            print_help()
            sys.exit(0)

    # Načtení vstupu
    obsah_souboru = sys.stdin.read()

    radky = obsah_souboru.splitlines()
    order = 1
    empty = True

    for radek in radky:
        slova = radek.split()

        # Když je hlavička zapsána, vždy měníme názvy funkcí na velké znaky
        if not(empty) and len(slova) > 0:
            slova[0] = slova[0].upper()
        
        # Určení zda je na řádku komentář
        if '#' in radek:
            rozdeleni = radek.split('#')
            slova = rozdeleni[0].split()
        
        # Kontrola zda se nejedná o prázdný řádek, případně zda není na levé straně od '#' prázdný řetězec
        if len(slova) == 0:
            continue
        
        # Rozvětvené podmínky pro určení o jakou instrukci se jedná
        if empty and slova[0] == ".IPPcode24":
            if order == 1:
                # Vytvoření XML dokumentu
                root = ET.Element("program")
                root.set("language", "IPPcode24")
                empty = False
            else:
                sys.exit(23)
        elif not(empty) and (slova[0] == "MOVE" or slova[0] == "INT2CHAR" or slova[0] == "STRLEN" or slova[0] == "TYPE" or slova[0] == "NOT"):
            if len(slova) != 3:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if not(is_var(slova[1])):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "var")
            arg1.text = slova[1]

            if is_var(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                arg2.set("type", "var")
                arg2.text = slova[2]
            elif is_litral(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                rozdeleni = slova[2].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg2.set("type", rozdeleni[0])
                arg2.text = rozdeleni[1]
            else:
                sys.exit(23)

            order += 1
            # /var, symb
        elif not(empty) and (slova[0] == "CREATEFRAME" or slova[0] == "PUSHFRAME" or slova[0] == "POPFRAME" or slova[0] == "RETURN" or slova[0] == "BREAK"):
            if len(slova) != 1:
                sys.exit(23)

            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            order += 1
            # /without arguments
        elif not(empty) and (slova[0] == "DEFVAR" or slova[0] == "POPS"):
            if len(slova) != 2:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if not(is_var(slova[1])):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "var")
            arg1.text = slova[1]

            order += 1
            # /var
        elif not(empty) and (slova[0] == "CALL" or slova[0] == "LABEL" or slova[0] == "JUMP"):
            if len(slova) != 2:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if is_var(slova[1]) or is_litral(slova[1]):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "label")
            arg1.text = slova[1]

            order += 1
            # /label
        elif not(empty) and (slova[0] == "PUSHS" or slova[0] == "WRITE" or slova[0] == "EXIT" or slova[0] == "DPRINT"):
            if len(slova) != 2:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if is_var(slova[1]):
                arg1 = ET.SubElement(instruction, "arg1")
                arg1.set("type", "var")
                arg1.text = slova[1]
            elif is_litral(slova[1]):
                arg1 = ET.SubElement(instruction, "arg1")
                rozdeleni = slova[1].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg1.set("type", rozdeleni[0])
                arg1.text = rozdeleni[1]
            else:
                sys.exit(23)

            order += 1
            # /symb
        elif not(empty) and (slova[0] == "ADD" or slova[0] == "SUB" or slova[0] == "MUL" or slova[0] == "IDIV" or slova[0] == "LT" or slova[0] == "GT" or slova[0] == "EQ" or slova[0] == "AND" or slova[0] == "OR" or slova[0] == "STRI2INT" or slova[0] == "CONCAT" or slova[0] == "GETCHAR" or slova[0] == "SETCHAR"):
            if len(slova) != 4:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if not(is_var(slova[1])):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "var")
            arg1.text = slova[1]

            if is_var(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                arg2.set("type", "var")
                arg2.text = slova[2]
            elif is_litral(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                rozdeleni = slova[2].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg2.set("type", rozdeleni[0])
                arg2.text = rozdeleni[1]
            else:
                sys.exit(23)

            if is_var(slova[3]):
                arg3 = ET.SubElement(instruction, "arg3")
                arg3.set("type", "var")
                arg3.text = slova[3]
            elif is_litral(slova[3]):
                arg3 = ET.SubElement(instruction, "arg3")
                rozdeleni = slova[3].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg3.set("type", rozdeleni[0])
                arg3.text = rozdeleni[1]
            else:
                sys.exit(23)

            order += 1
            # /var, symb1, symb2
        elif not(empty) and (slova[0] == "READ"):
            if len(slova) != 3:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if not(is_var(slova[1])):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "var")
            arg1.text = slova[1]

            if is_type(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                arg2.set("type", "type")
                arg2.text = slova[2]
            else:
                sys.exit(23)

            order += 1
            # /var, type
        elif not(empty) and (slova[0] == "JUMPIFEQ" or slova[0] == "JUMPIFNEQ"):
            if len(slova) != 4:
                sys.exit(23)
            
            instruction = ET.SubElement(root, "instruction")
            instruction.set("order", str(order))
            instruction.set("opcode", slova[0])

            if is_var(slova[1]) or is_litral(slova[1]):
                sys.exit(23)
            arg1 = ET.SubElement(instruction, "arg1")
            arg1.set("type", "label")
            arg1.text = slova[1]

            if is_var(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                arg2.set("type", "var")
                arg2.text = slova[2]
            elif is_litral(slova[2]):
                arg2 = ET.SubElement(instruction, "arg2")
                rozdeleni = slova[2].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg2.set("type", rozdeleni[0])
                arg2.text = rozdeleni[1]
            else:
                sys.exit(23)

            if is_var(slova[3]):
                arg3 = ET.SubElement(instruction, "arg3")
                arg3.set("type", "var")
                arg3.text = slova[3]
            elif is_litral(slova[3]):
                arg3 = ET.SubElement(instruction, "arg3")
                rozdeleni = slova[3].split('@')
                if len(rozdeleni) != 2:
                    sys.exit(23)
                arg3.set("type", rozdeleni[0])
                arg3.text = rozdeleni[1]
            else:
                sys.exit(23)

            order += 1
            # /label, symb1, symb2
        else:
            sys.exit(23)
        # Konec cyklu procházejícího řádky
    
    if not(empty):
        # Převedení XML na řetězec, formátování a výpis
        xml_str = ET.tostring(root, encoding="utf-8").decode("utf-8")
        xml_dom = minidom.parseString(xml_str)
        pretty_xml_str = xml_dom.toprettyxml(indent="    ")
        vystup = pretty_xml_str[:20] + 'encoding="UTF-8"' + pretty_xml_str[20:]
        sys.stdout.write(vystup)
        sys.exit(0)
    else:
        sys.exit(23)

if __name__ == "__main__":
    main()
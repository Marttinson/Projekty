<?php

namespace IPP\Student;

use IPP\Core\AbstractInterpreter;
use IPP\Student\Text;
use IPP\Student\Frames;
use IPP\Student\Labels;
use IPP\Student\Instruction;

class Interpreter extends AbstractInterpreter
{
    private $dom;
    private $root;

    private $frame;

    private $labels;

    private $instruction;

    private $calls;

    private $stack;

    private $num_of_instruction;

    protected function init() : void{
        parent::init();
        
        $this->dom = $this->source->getDOMDocument();
        $this->root = $this->dom->documentElement;

        $this->frame = new Frames();

        $this->labels = new Labels();

        $this->instruction = array();

        $this->calls = array();

        $this->stack = new \SplStack();

        $this->num_of_instruction = 0;
    }

    public function execute(): int
    {
        // Načtení celého kodu do vytvořených tříd
        foreach($this->root->childNodes as $instruction){
            if ($instruction->nodeType === XML_ELEMENT_NODE && $instruction->nodeName === 'instruction') {
                $this->instruction[] = new Instruction($instruction);
            }
        }
        
        // Hlavni cyklus a volání funkce
        for($index = 0; $index < count($this->instruction); $index++){
            $index = $this->loop($index);
            $this->num_of_instruction++;

            // Kontrola, zda nebyla použita instrukce EXIT
            if($index < 0){
                if($index == -10)
                    return 0;
                return -1 * $index;
            }
        }

        return 0;
    }

    // Stěžejní metoda, která nejprve rozpozná požadovanou metodu a následně se ji pokusí vykonat
    // nebo zavolá pomocné metody
    private function loop($index) : int{
        // Nastavení názvu na velké písmena, aby byl case insensitive
        $instruction = $this->instruction[$index];
        $name = mb_strtoupper($instruction->name);

        // Zde je rozsáhlá podmínka, kontrolující všechny instrukce, pokud je instrukce neznámá
        // program pokračuje dál a takovou instrukci ignoruje
        if($name == "MOVE"){
            $param = $instruction->param["arg1"];
            $value = $instruction->param["arg2"]->value;
            $this->insert($param, $value, $instruction->param["arg2"]->type);
        }
        else if($name === "CREATEFRAME"){
            $this->frame->TF->init();
        }
        else if($name === "PUSHFRAME"){
            $this->frame->pushFrame();
        }
        else if($name === "POPFRAME"){
            $this->frame->popFrame();
        }
        else if($name === "DEFVAR"){
            $parts = explode("@", $instruction->param["arg1"]->value);
            if($parts[0] == "GF"){
                $this->frame->GF->defvar($parts[1]);
            }
            else if($parts[0] == "TF"){
                $this->frame->TF->defvar($parts[1]);
            }
            else if($parts[0] == "LF"){
                $this->frame->LF->defvar($parts[1]);
            }
        }
        else if($name === "CALL"){
            $this->calls[] = $instruction->param["arg1"]->value;
        }
        else if($name === "RETURN"){
            if(count($this->calls) > 0){
                $here = $this->search_for_label(end($this->calls));
                if($here >= 0){
                    $index = $here;
                    array_pop(($this->calls));
                }
            }
        }
        else if($name === "PUSHS"){
            $value = $this->get_value_from_symb($instruction->param["arg1"]);
            $this->stack->push($value);
        }
        else if($name === "POPS"){
            if($this->stack->isEmpty())
                exit(56);

            $param = $instruction->param["arg1"];
            $value = $this->stack->pop();
            if($value == "true" || $value == "false")
                $this->insert($param, $value, "bool");
            else if(is_numeric($value))
                $this->insert($param, $value, "int");
            else
                $this->insert($param, $value, "string");
        }
        else if($name === "ADD"){
            if(($instruction->param["arg2"]->type == "int" && $instruction->param["arg3"]->type == "int") ||
            $instruction->param["arg2"]->type == "var" || $instruction->param["arg3"]->type == "var"){
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

                $this->insert($instruction->param["arg1"], $arg2 + $arg3, "int");
            }
        }
        else if($name === "SUB"){
            if(($instruction->param["arg2"]->type == "int" && $instruction->param["arg3"]->type == "int") ||
            $instruction->param["arg2"]->type == "var" || $instruction->param["arg3"]->type == "var"){
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

                $this->insert($instruction->param["arg1"], $arg2 - $arg3, "int");
            }
        }
        else if($name === "MUL"){
            if(($instruction->param["arg2"]->type == "int" && $instruction->param["arg3"]->type == "int") ||
            $instruction->param["arg2"]->type == "var" || $instruction->param["arg3"]->type == "var"){
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

                $this->insert($instruction->param["arg1"], $arg2 * $arg3, "int");
            }
        }
        else if($name === "IDIV"){
            if(($instruction->param["arg2"]->type == "int" && $instruction->param["arg3"]->type == "int") ||
            $instruction->param["arg2"]->type == "var" || $instruction->param["arg3"]->type == "var"){
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

                if($arg3 == 0)
                    exit(57);

                $this->insert($instruction->param["arg1"], $arg2 / $arg3, "int");
            }
        }
        else if($name === "LT" || $name === "GT" || $name === "EQ"){
            $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

            if($name === "LT"){
                if($arg2 < $arg3)
                    $this->insert($instruction->param["arg1"], "true", "bool");
                else
                    $this->insert($instruction->param["arg1"], "false", "bool");
            }
            if($name === "GT"){
                if($arg2 > $arg3)
                    $this->insert($instruction->param["arg1"], "true", "bool");
                else
                    $this->insert($instruction->param["arg1"], "false", "bool");
            }
            if($name === "EQ"){
                if($arg2 == $arg3)
                    $this->insert($instruction->param["arg1"], "true", "bool");
                else
                    $this->insert($instruction->param["arg1"], "false", "bool");
            }
        }
        else if($name === "AND" && $name === "OR"){
            $arg2 = $instruction->param["arg2"];
            $arg3 = $instruction->param["arg3"];
            if(($arg2->type === "bool" || $this->get_type($arg2)) === "bool" && 
            ($arg3->type === "bool" || $this->get_type($arg3) == "bool")){
                $arg2_val = $this->get_value_from_symb($arg2);
                $arg3_val = $this->get_value_from_symb($arg3);
                if($name === "AND"){
                    if($arg2_val && $arg3_val)
                        $this->insert($instruction->param["arg1"], "true", "bool");
                    else
                        $this->insert($instruction->param["arg1"], "false", "bool");
                }
                else{
                    if($arg2_val || $arg3_val)
                        $this->insert($instruction->param["arg1"], "true", "bool");
                    else
                        $this->insert($instruction->param["arg1"], "false", "bool");
                }
            }
        }
        else if($name === "NOT"){
            if($this->get_value_from_symb($instruction->param["arg2"]) === "true")
                $this->insert($instruction->param["arg1"], "false", "bool");
            else
                $this->insert($instruction->param["arg1"], "true", "bool");
        }
        else if($name === "INT2CHAR"){
            $value = $this->get_value_from_symb($instruction->param["arg2"]);
            $this->insert($instruction->param["arg1"], mb_chr($value, "UTF-8"), "string");
        }
        else if($name === "STRI2INT"){
            $value = $this->get_value_from_symb($instruction->param["arg2"]);
            $this->insert($instruction->param["arg1"], mb_ord($value, "UTF-8"), "int");
        }
        else if($name === "READ"){
            $arg2 = $instruction->param["arg2"]->value;
            if($arg2 === "int")
                $this->insert($instruction->param["arg1"], $this->input->readInt(), "int");
            else if($arg2 === "string")
                $this->insert($instruction->param["arg1"], $this->input->readString(), "string");
            else if($arg2 === "bool")
                $this->insert($instruction->param["arg1"], $this->input->readBool(), "bool");
        }
        else if($name === "WRITE"){
            $value = $this->get_value_from_symb($instruction->param["arg1"]);
            if($value != null){
                if($instruction->param["arg1"]->type == "string" || $this->get_type($instruction->param["arg1"]) == "string"){
                    $str = new Text($value);
                    $this->stdout->writeString($str->text);
                }
                else if($instruction->param["arg1"]->type == "int" || $this->get_type($instruction->param["arg1"]) == "int"){
                    $this->stdout->writeInt($value);
                }
                else if($instruction->param["arg1"]->type == "bool" || $this->get_type($instruction->param["arg1"]) == "bool"){
                    $this->stdout->writeString($value);
                }
            }
        }
        else if($name === "CONCAT"){
            $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

            $this->insert($instruction->param["arg1"], $arg2 . $arg3, "string");
        }
        else if($name === "STRLEN"){
            $arg2 = $this->get_value_from_symb( $instruction->param["arg2"]);
            $this->insert($instruction->param["arg1"], strlen($arg2), "int");
        }
        else if($name === "GETCHAR"){
            $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

            if($arg3 >= strlen($arg2))
                exit(58);
            $this->insert($instruction->param["arg1"], $arg2[$arg3], "string");
        }
        else if($name === "SETCHAR"){
            $arg1 = $this->get_value_from_symb($instruction->param["arg1"]);
            $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);

            if(strlen($arg3) < $arg2)
                exit(58);

            if(strlen($arg1) < $arg2)
                $arg1[$arg2] = $arg3[$arg2];
            else
                $arg1[0] = $arg3[$arg2];

            $this->insert($instruction->param["arg1"], $arg1, "string");
        }
        else if($name === "TYPE"){
            if($instruction->param["arg2"]->type === "var"){
                $type = $this->get_type($instruction->param["arg2"]);
                $this->insert($instruction->param["arg1"], $type, "string");
            }
            else{
                $value = $this->get_value_from_symb( $instruction->param["arg2"]);
                if($value == "true" || $value == "false")
                    $this->insert($instruction->param["arg1"], "bool", "string");
                else if(is_numeric($value))
                    $this->insert($instruction->param["arg1"], "int", "string");
                else
                    $this->insert($instruction->param["arg1"], "string", "string");
            }
        }
        else if($name === "LABEL"){
            $this->labels->add($instruction->param["arg1"]->value);
        }
        else if($name === "JUMP"){
            $here = $this->search_for_label($instruction->param["arg1"]->value);
            if($here >= 0)
                $index = $here;
        }
        else if($name === 'JUMPIFEQ'){
            if($instruction->param["arg2"]->type == "var")
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            else
                $arg2 = $instruction->param["arg2"]->value;

            if($instruction->param["arg3"]->type == "var")
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);
            else
                $arg3 = $instruction->param["arg3"]->value;

            if($arg2 == $arg3)
                $index = $this->search_for_label($instruction->param["arg1"]->value);
        }
        else if($name === 'JUMPIFNEQ'){
            if($instruction->param["arg2"]->type == "var")
                $arg2 = $this->get_value_from_symb($instruction->param["arg2"]);
            else
                $arg2 = $instruction->param["arg2"]->value;

            if($instruction->param["arg3"]->type == "var")
                $arg3 = $this->get_value_from_symb($instruction->param["arg3"]);
            else
                $arg3 = $instruction->param["arg3"]->value;

            if($arg2 != $arg3)
                $index = $this->search_for_label($instruction->param["arg1"]->value);
        }
        else if($name === "EXIT"){
            $value = $this->get_value_from_symb($instruction->param["arg1"]);
            if($value == 0)
                return -10;
            return -1 * $value;
        }
        else if($name === "DPRINT"){
            $value = $this->get_value_from_symb($instruction->param["arg1"]->value);
            if($value == "true")
                $this->stderr->writeBool(true);
            else if($value == "false")
                $this->stderr->writeBool(false);
            else if(is_numeric($value))
                $this->stderr->writeInt($value);
            else
                $this->stderr->writeString($value);
        }
        else if($name === "BREAK"){
            $this->stderr->writeString("Vykonanych instrukci: " . $this->num_of_instruction);
        }

        return $index;
    }

    // Pomocná metoda, která vyhledá návěští podle názvu a vrátí jeho pozici
    private function search_for_label($label_name){
        $array = $this->instruction;
        for($i = 0; $i < count($array); $i++){
            if(($array[$i]->name == "LABEL" || $array[$i]->name == "CALL") && $array[$i]->param["arg1"]->value == $label_name)
                return $i;
        }
        return -1;
    }

    // Pomocná metoda pro vložení hodnoty do správné proměnné ve správném rámci
    private function insert($param, $value, $type){
        $parts = explode("@", $param->value);
        if($parts[0] == "GF"){
            $this->frame->GF->insert($param, $value, $type);
        }
        else if($parts[0] == "TF"){
            $this->frame->TF->insert($param, $value, $type);
        }
        else if($parts[0] == "LF"){
            $this->frame->LF->insert($param, $value, $type);
        }
    }

    // Pomocná metoda pro získání hodnoty ze symbolu (proměnné, nebo literálu)
    private function get_value_from_symb($param){
        if($param->type == "var"){
            $parts = explode("@", $param->value);

            if($parts[0] == "GF")
                return $this->frame->GF->get_data($parts[1]);
            else if($parts[0] == "LF")
                return $this->frame->LF->get_data($parts[1]);
            else if($parts[0] == "TF")
                return $this->frame->TF->get_data($parts[1]);
        }
        else
            return $param->value;
    }

    // Pomocná metoda pro získání typu proměnné
    private function get_type($param){
        $parts = explode("@", $param->value);

        if($parts[0] == "GF")
            return $this->frame->GF->get_type($parts[1]);
        else if($parts[0] == "LF")
            return $this->frame->LF->get_type($parts[1]);
        else if($parts[0] == "TF")
            return $this->frame->TF->get_type($parts[1]);
    }
}

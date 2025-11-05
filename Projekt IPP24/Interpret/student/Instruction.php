<?php

namespace IPP\Student;

use IPP\Student\Param;

// Třída reprezentující jednotlivé instrekce, obsahuje jejich název a parametry (pokud nějaké má)
class Instruction
{
    public $name;
    public $param;

    public function __construct($instruction){
        $this->name = $instruction->attributes->getNamedItem("opcode")->nodeValue;
        $this->param = array();
        foreach($instruction->childNodes as $arg){
            if($arg->nodeName == "arg1")
                $this->param["arg1"] = new Param($arg);
            else if($arg->nodeName == "arg2")
                $this->param["arg2"] = new Param($arg);
            else if($arg->nodeName == "arg3")
                $this->param["arg3"] = new Param($arg);
        }
    }
}

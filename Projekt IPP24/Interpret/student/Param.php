<?php

namespace IPP\Student;

// Třída reprezentující jednotlivé parametry instrukcí, obsahuje jejich název, typ a hodnotu
class Param
{
    public $name;
    public $type;
    
    public $value;

    public function __construct($item){
        $this->name = $item->nodeName;
        $this->type = $item->attributes->getNamedItem("type")->nodeValue;
        $this->value = $item->nodeValue;
    }
}

<?php

namespace IPP\Student;

// Třída reprezentující návěští, přidává jednotlivé názvy návěští do pole a kontroluje, zda se v poli
// název již nenachází, pokud ano zahlásí chybu
class Labels
{
    private $names;

    public function __construct(){
        $this->names = array();
    }

    public function add($label){
        // Kontrola, zda se label už v poli nevyskytuje
        if(in_array($label, $this->names))
            exit(52);
        $this->names[] = $label;
    }
}

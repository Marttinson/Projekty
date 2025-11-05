<?php

namespace IPP\Student;

// Třída definující dočasný rámec, dědí z globálního rámce a metody si částečně upravuje
class TF_frame extends GF_frame
{
    private $enable;

    public function __construct(){
        $this->data = array();
        $this->type = array();
        $this->enable = false;
    }

    public function init(){
        $this->data = array();
        $this->type = array();
        $this->enable = true;
    }
    
    public function remove(){
        $this->data = array();
        $this->type = array();
        $this->enable = false;
    }

    // Tato funkce slouží pro převod lokálního rámce na dočasný
    public function LT_to_TF($frame, $type){
        $this->data = $frame;
        $this->type = $type;
        $this->enable = true;
    }

    public function defvar($index){
        if($this->isEnable())
            parent::defvar($index);
    }

    public function insert($index, $data, $type){
        if($this->isEnable())
            parent::insert($index, $data, $type);
    }

    public function get_type($index){
        if($this->isEnable())
            return parent::get_type($index);
    }

    public function get_data($index){
        if($this->isEnable())
            return parent::get_data($index);
    }

    public function isEnable(){
        return $this->enable;
    }

    public function get_array(){
        if($this->isEnable())
            return $this->data;
        return null;
    }

    public function get_types(){
        if($this->isEnable())
            return $this->type;
        return null;
    }
}

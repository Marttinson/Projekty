<?php

namespace IPP\Student;

// Třída definující globální rámec
class GF_frame
{
    protected $data;
    protected $type;

    public function __construct(){
        $this->data = array();
        $this->type = array();
    }

    public function defvar($index){
        if(array_key_exists($index, $this->data))
            exit(52);
        $this->data[$index] = null;
    }

    public function insert($index, $data, $type){
        $parts = explode("@", $index->value);
        if(array_key_exists($parts[1], $this->data)){
            $this->data[$parts[1]] = $data;
            $this->type[$parts[1]] = $type;
        }
    }

    public function get_type($index){
        return $this->type[$index];
    }

    public function get_data($index){
        return $this->data[$index];
    }
}

<?php

namespace IPP\Student;

// Třída definující lokální rámec
class LF_frame
{
    private $data;

    private $type;
    private $aktualni_frame;

    public function __construct(){
        $this->data = array();
        $this->type = array();
        $this->aktualni_frame = -1;
    }

    // Následující 3 metody slouží pro posouvání dočasného rámce na zásobník a ze zásobníku zpět
    public function pushFrame($TF_data, $TF_type){
        if($TF_data != null){
            $this->data[] = $TF_data;
            $this->type[] = $TF_type;
            $this->aktualni_frame++;
        }
    }
    
    public function pop_data(){
        if(!$this->isEnable())
            exit(55);
        $res = $this->data[$this->aktualni_frame];
        $this->data[$this->aktualni_frame] = array();
        return $res;
    }

    public function pop_type(){
        $res = $this->type[$this->aktualni_frame];
        $this->type[$this->aktualni_frame--] = array();
        return $res;
    }

    public function defvar($index){
        if($this->isEnable()){
            if(array_key_exists($index, $this->data[$this->aktualni_frame]))
                exit(52);
            $this->data[$this->aktualni_frame][$index] = null;
        }
    }

    public function insert($index, $data, $type){
        if($this->isEnable()){
            $parts = explode("@", $index->value);
            if(array_key_exists($parts[1], $this->data[$this->aktualni_frame])){
                $this->data[$this->aktualni_frame][$parts[1]] = $data;
                $this->type[$this->aktualni_frame][$parts[1]] = $type;
            }
        }
    }

    public function get_type($index){
        if($this->isEnable())
            return $this->type[$this->aktualni_frame][$index];
    }

    public function get_data($index){
        if($this->isEnable())
            return $this->data[$this->aktualni_frame][$index];
    }

    private function isEnable(){
        return $this->aktualni_frame >= 0;
    }
}

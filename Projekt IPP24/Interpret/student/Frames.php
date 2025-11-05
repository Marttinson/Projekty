<?php

namespace IPP\Student;

use IPP\Student\GF_frame;
use IPP\Student\TF_frame;
use IPP\Student\LF_frame;

// Třída spojující rámce dohromady, obsahuje metody používané při převodu z lokálního rámce na dočasný
// a naopak a zároveň vytváří jednotlivé rámce
class Frames
{
    public $GF;
    public $TF;
    public $LF;
    public function __construct(){
        $this->GF = new GF_frame();
        $this->TF = new TF_frame();
        $this->LF = new LF_frame();
    }

    public function pushFrame(){
        if(!$this->TF->isEnable())
            exit(55);

        $this->LF->pushFrame($this->TF->get_array(), $this->TF->get_types());
        $this->TF->remove();
    }

    public function popFrame(){
        $this->TF->LT_to_TF($this->LF->pop_data(), $this->LF->pop_type());
    }
}

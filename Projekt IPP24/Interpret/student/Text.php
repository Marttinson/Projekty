<?php

namespace IPP\Student;

// Třída reprezentující textový řetězec, převádí jednotlivé escape sekvence na požadované znaky
class Text
{
    public $text;
    public function __construct(string $retezec) {
        $this->text = stripcslashes($retezec);
        $this->format();
    }

    // Funkce převádí dekadické čísla na oktálové a volá integrovanou funkci, která pak oktálové hodnoty
    // převede na samotné znaky
    private function format(){
        $text = $this->text;
        $escapes = array();
        
        for( $i = 0; $i < strlen($text); $i++ ){
            if($text[$i] < 1000 && !ctype_digit($text[$i]) && $text[$i] != " "){
                $oct = decoct(ord($text[$i]));
                $oct = decoct($oct);

                $escapes[] = $oct;
            }
        }
        
        $j = 0;
        $newtext = "";
        for($i = 0; $i < strlen($text); $i++){
            if(ctype_digit($text[$i])){
                $newtext .= $text[$i];
            }
            else if($text[$i] < 1000 && $text[$i] != " "){
                $str = "\\0" . $escapes[$j++];
                $newtext .= $str;
            }
            else{
                $newtext .= $text[$i];
            }
        }
        $this->text = stripcslashes($newtext);
    }
}

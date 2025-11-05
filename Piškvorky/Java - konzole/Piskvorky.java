public class Piskvorky {
    static boolean kontrolaVyhry(Hraci_plocha plocha, char znak, int pocet_na_vyhru, int x, int y){
        return 
        kontrolaVyhryVodorovne(plocha, znak, pocet_na_vyhru, x, y) || 
        kontrolaVyhrySvisle(plocha, znak, pocet_na_vyhru, x, y) || 
        kontrolaVyhryOstry(plocha, znak, pocet_na_vyhru, x, y) || 
        kontrolaVyhryTupy(plocha, znak, pocet_na_vyhru, x, y);
    }

    //-
    static boolean kontrolaVyhryVodorovne(Hraci_plocha plocha, char znak, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int soucet = 0;

        //do prava
        while(true){
            if(x < plocha.getSirka()){
                if(plocha.CharAt(x++, y) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //do leva
        x = puvodni_x - 1;
        while(true){
            if(x >= 0){
                if(plocha.CharAt(x--, y) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet vodorovne: " + soucet);
        if(soucet >= pocet_na_vyhru)
            return true;

        return false;
    }

    //|
    static boolean kontrolaVyhrySvisle(Hraci_plocha plocha, char znak, int pocet_na_vyhru, int x, int y){
        int puvodni_y = y;
        int soucet = 0;
        
        //nahoru
        while(true){
            if(y >= 0){
                if(plocha.CharAt(x, y--) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //dolu
        y = puvodni_y + 1;
        while(true){
            if(y < plocha.getVyska()){
                if(plocha.CharAt(x, y++) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet svisle: " + soucet);
        if(soucet >= pocet_na_vyhru)
            return true;

        return false;
    }
    
    ///
    static boolean kontrolaVyhryOstry(Hraci_plocha plocha, char znak, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x < plocha.getSirka() && y >= 0){
                if(plocha.CharAt(x++, y--) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //dolu
        x = puvodni_x - 1;
        y = puvodni_y + 1;
        while(true){
            if(x >= 0 && y < plocha.getVyska()){
                if(plocha.CharAt(x--, y++) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet ostre: " + soucet);
        if(soucet >= pocet_na_vyhru)
            return true;

        return false;
    }

    //\
    static boolean kontrolaVyhryTupy(Hraci_plocha plocha, char znak, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(plocha.CharAt(x--, y--) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //dolu
        x = puvodni_x + 1;
        y = puvodni_y + 1;

        while(true){
            if(x < plocha.getSirka() && y < plocha.getVyska()){
                if(plocha.CharAt(x++, y++) == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet tupe: " + soucet);
        if(soucet >= pocet_na_vyhru)
            return true;

        return false;
    }
}

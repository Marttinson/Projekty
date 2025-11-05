public class Piskvorky {
    static boolean kontrolaVyhry(char znak, int x, int y){
        return 
        kontrolaVyhryVodorovne(znak, x, y) || 
        kontrolaVyhrySvisle(znak, x, y) || 
        kontrolaVyhryOstry(znak, x, y) || 
        kontrolaVyhryTupy(znak, x, y);
    }

    //-
    static boolean kontrolaVyhryVodorovne(char znak, int x, int y){
        int puvodni_x = x;
        int soucet = 0;

        //do prava
        while(true){
            if(x < Info.sirka){
                if(Info.plocha[y][x++] == znak)
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
                if(Info.plocha[y][x--] == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet vodorovne: " + soucet);
        if(soucet >= Info.pocet_na_vyhru)
            return true;

        return false;
    }

    //|
    static boolean kontrolaVyhrySvisle(char znak, int x, int y){
        int puvodni_y = y;
        int soucet = 0;
        
        //nahoru
        while(true){
            if(y >= 0){
                if(Info.plocha[y--][x] == znak)
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
            if(y < Info.vyska){
                if(Info.plocha[y++][x] == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet svisle: " + soucet);
        if(soucet >= Info.pocet_na_vyhru)
            return true;

        return false;
    }
    
    ///
    static boolean kontrolaVyhryOstry(char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x < Info.sirka && y >= 0){
                if(Info.plocha[y--][x++] == znak)
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
            if(x >= 0 && y < Info.vyska){
                if(Info.plocha[y++][x--] == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet ostre: " + soucet);
        if(soucet >= Info.pocet_na_vyhru)
            return true;

        return false;
    }

    //\
    static boolean kontrolaVyhryTupy(char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(Info.plocha[y--][x--] == znak)
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
            if(x < Info.sirka && y < Info.vyska){
                if(Info.plocha[y++][x++] == znak)
                    soucet++;
                else
                    break;
            }
            else
                break;
        }

        //System.out.println("Soucet tupe: " + soucet);
        if(soucet >= Info.pocet_na_vyhru)
            return true;

        return false;
    }
}

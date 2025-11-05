import java.util.Random;

public class Bot {
    //Bot bude staticky, asi se bude volat v komunikaci jak hráč dohraje kolo...
    static Hraci_plocha zacinaHru(Hraci_plocha plocha){
        int x = plocha.getSirka() / 2;
        int y = plocha.getVyska() / 2;

        plocha.pridatPolicko(x, y, 'X');
        return plocha;
    }

    static Hraci_plocha nezacinaHru(Hraci_plocha plocha){
        int x = plocha.getSirka() / 2;
        int y = plocha.getVyska() / 2;

        if(plocha.CharAt(x, y) != ' ')
            x--;
        
            plocha.pridatPolicko(x, y, 'O');

            return plocha;
    }

    static Hraci_plocha hraje(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru){
        //znaky[0] - hrac, znaky[1] - bot
        int[] souradnice = new int[2];

        for(int y = 0; y < plocha.getVyska(); y++){
            for(int x = 0; x < plocha.getSirka(); x++){
                if(kontrolaVodorovne(plocha, znaky[1], pocet_na_vyhru - 1, x, y)){
                    souradnice = vodorovne(plocha, znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        plocha.pridatPolicko(souradnice[0], souradnice[1], znaky[1]);
                        return plocha;
                    }
                }
                if(kontrolaSvisle(plocha, znaky[1], pocet_na_vyhru - 1, x, y)){
                    souradnice = svisle(plocha, znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        plocha.pridatPolicko(souradnice[0], souradnice[1], znaky[1]);
                        return plocha;
                    }
                }
                if(kontrolaOstre(plocha, znaky[1], pocet_na_vyhru - 1, x, y)){
                    souradnice = ostre(plocha, znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        plocha.pridatPolicko(souradnice[0], souradnice[1], znaky[1]);
                        return plocha;
                    }
                }
                if(kontrolaTupe(plocha, znaky[1], pocet_na_vyhru, x, y)){
                    souradnice = tupe(plocha, znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        plocha.pridatPolicko(souradnice[0], souradnice[1], znaky[1]);
                        return plocha;
                    }
                }
            }
        }
        
        souradnice = obrana(plocha, znaky, pocet_na_vyhru);

        if(souradnice[0] < 0)
            souradnice = utok(plocha, znaky, pocet_na_vyhru);

        plocha.pridatPolicko(souradnice[0], souradnice[1], znaky[1]);

        return plocha;
    }

    static int[] obrana(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru){
        //res[0] - x, res[1] - y
        int[] res = new int[2];
        res[0] = -1;
        res[1] = -1;

        for(int y = 0; y < plocha.getVyska(); y++){
            for(int x = 0;  x < plocha.getSirka(); x++){
                if(kontrolaVodorovne(plocha, znaky[0], pocet_na_vyhru - 1, x, y)){
                    res = vodorovne(plocha, znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaSvisle(plocha, znaky[0], pocet_na_vyhru - 1, x, y)){
                    res = svisle(plocha, znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaOstre(plocha, znaky[0], pocet_na_vyhru - 1, x, y)){
                    res = ostre(plocha, znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaTupe(plocha, znaky[0], pocet_na_vyhru - 1, x, y)){
                    res = tupe(plocha, znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
            }
        }

        if(pocet_na_vyhru > 3){
            for(int y = 0; y < plocha.getVyska(); y++){
                for(int x = 0;  x < plocha.getSirka(); x++){
                    if(predvidacVodorovne(plocha, znaky, pocet_na_vyhru, x, y)){
                        res = vodorovne(plocha, znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacSvisle(plocha, znaky, pocet_na_vyhru, x, y)){
                        res = svisle(plocha, znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacOstre(plocha, znaky, pocet_na_vyhru, x, y)){
                        res = ostre(plocha, znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacTupe(plocha, znaky, pocet_na_vyhru, x, y)){
                        res = tupe(plocha, znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                }
            }
        }

        return res;
    }

    static int[] utok(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru){
        //res[0] - x, res[1] - y
        int[] res = new int[2];
        res[0] = -1;
        int soucet = 0;
        int max = 0;
        int maxx = pocet_na_vyhru - 1;

        do{
            for(int y = 0; y < plocha.getVyska(); y++){
                for(int x = 0; x < plocha.getSirka(); x++){
                    soucet = soucetVodorovne(plocha, znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = vodorovne(plocha, znaky[0], x, y);
                    }
                    soucet = soucetSvisle(plocha, znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = svisle(plocha, znaky[0], x, y);
                    }
                    soucet = soucetOstre(plocha, znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = ostre(plocha, znaky[0], x, y);
                    }
                    soucet = soucetTupe(plocha, znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = tupe(plocha, znaky[0], x, y);
                    }
                }
            }
            max = 0;
            maxx--;

            if(maxx == 0){
                int random_x, random_y;
                do{
                Random rand = new Random();
                random_x = rand.nextInt(plocha.getSirka());
                random_y = rand.nextInt(plocha.getVyska());

                }while(!plocha.kontrolaSouradnice(random_x, random_y));
                res[0] = random_x;
                res[1] = random_y;
            }
        }while(res[0] == -1);

        return res;
    }

    //-
    static boolean kontrolaVodorovne(Hraci_plocha plocha, char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetVodorovne(Hraci_plocha plocha, char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacVodorovne(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int soucet = 0;

        //do prava
        while(true){
            if(x < plocha.getSirka()){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x++;
            }
            else
                break;
        }

        //do leva
        x = puvodni_x - 1;
        while(true){
            if(x >= 0){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x--;
            }
            else
                break;
        }

        if(soucet == pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] vodorovne(Hraci_plocha plocha, char znak, int x, int y){
        int puvodni_x = x;
        int res[] = new int[2];
        res[1] = y;

        //do prava
        while(true){
            if(x < plocha.getSirka()){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else
                    x++;
            }
            else
                break;
        }

        //do leva
        x = puvodni_x - 1;
        while(true){
            if(x >= 0){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else
                    x--;
            }
            else
                break;
        }

        res[0] = -1;
        res[1] = -1;
        return res;
    }

    //|
    static boolean kontrolaSvisle(Hraci_plocha plocha, char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetSvisle(Hraci_plocha plocha, char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacSvisle(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru, int x, int y){
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(y >= 0){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                y--;
            }
            else
                break;
        }

        //dolu
        y = puvodni_y + 1;
        while(true){
            if(y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                y++;
            }
            else
                break;
        }

        if(soucet == pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] svisle(Hraci_plocha plocha, char znak, int x, int y){
        int puvodni_y = y;
        int[] res = new int[2];
        res[0] = x;

        //nahoru
        while(true){
            if(y >= 0){
                if(plocha.CharAt(x, y) == ' '){
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else
                    y--;
            }
            else
                break;
        }

        //dolu
        y = puvodni_y + 1;
        while(true){
            if(y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == ' '){
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else
                    y++;
            }
            else
                break;
        }

        res[0] = -1;
        res[1] = -1;
        return res;
    }

    ///
    static boolean kontrolaOstre(Hraci_plocha plocha, char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetOstre(Hraci_plocha plocha, char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacOstre(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x < plocha.getSirka() && y >= 0){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x++;
                y--;
            }
            else
                break;
        }

        //dolu
        x = puvodni_x - 1;
        y = puvodni_y + 1;
        while(true){
            if(x >= 0 && y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x--;
                y++;
            }
            else
                break;
        }

        if(soucet == pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] ostre(Hraci_plocha plocha, char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int[] res = new int[2];

        //nahoru
        while(true){
            if(x < plocha.getSirka() && y >= 0){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else{
                    x++;
                    y--;
                }
            }
            else
                break;
        }

        //dolu
        x = puvodni_x - 1;
        y = puvodni_y + 1;
        while(true){
            if(x >= 0 && y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else{
                    x--;
                    y++;
                }
            }
            else
                break;
        }

        res[0] = -1;
        res[1] = -1;
        return res;
    }

    //\
    static boolean kontrolaTupe(Hraci_plocha plocha, char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetTupe(Hraci_plocha plocha, char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacTupe(Hraci_plocha plocha, char[] znaky, int pocet_na_vyhru, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x--;
                y--;
            }
            else
                break;
        }

        //dolu
        x = puvodni_x + 1;
        y = puvodni_y + 1;
        while(true){
            if(x < plocha.getSirka() && y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == znaky[0])
                    soucet++;
                else if(plocha.CharAt(x, y) == znaky[1])
                    return false;
                else
                    break;
                x++;
                y++;
            }
            else
                break;
        }

        if(soucet == pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] tupe(Hraci_plocha plocha, char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int[] res = new int[2];

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else{
                    x--;
                    y--;
                }
            }
            else
                break;
        }

        //dolu
        x = puvodni_x + 1;
        y = puvodni_y + 1;

        while(true){
            if(x < plocha.getSirka() && y < plocha.getVyska()){
                if(plocha.CharAt(x, y) == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(plocha.CharAt(x, y) == znak)
                    break;
                else{
                    x++;
                    y++;
                }
            }
            else
                break;
        }

        res[0] = -1;
        res[1] = -1;
        return res;        
    }

}

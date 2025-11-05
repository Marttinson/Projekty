import java.util.Random;

public class Bot {
    //Bot bude staticky, asi se bude volat v komunikaci jak hráč dohraje kolo...
    static void zacinaHru(Okno okno){
        int x = Info.sirka / 2;
        int y = Info.vyska / 2;

        Info.plocha[y][x] = 'X';
        okno.setPolicko(x, y, "X");
    }

    static void nezacinaHru(Okno okno){
        int x = Info.sirka / 2;
        int y = Info.vyska / 2;

        if(Info.plocha[y][x] != ' ')
            x--;

        Info.plocha[y][x] = 'O';
        okno.setPolicko(x, y, "O");
    }

    static void hraje(Okno okno){
        //znaky[0] - hrac, znaky[1] - bot
        int[] souradnice = new int[2];
        boolean pokracovat = true;

        for(int y = 0; y < Info.vyska; y++){
            for(int x = 0; x < Info.sirka; x++){
                if(kontrolaVodorovne(Info.znaky[1], Info.pocet_na_vyhru - 1, x, y)){
                    souradnice = vodorovne(Info.znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        pokracovat = false;
                        break;
                    }
                }
                if(kontrolaSvisle(Info.znaky[1], Info.pocet_na_vyhru - 1, x, y)){
                    souradnice = svisle(Info.znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        pokracovat = false;
                        break;
                    }
                }
                if(kontrolaOstre(Info.znaky[1], Info.pocet_na_vyhru - 1, x, y)){
                    souradnice = ostre(Info.znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        pokracovat = false;
                        break;
                    }
                }
                if(kontrolaTupe(Info.znaky[1], Info.pocet_na_vyhru, x, y)){
                    souradnice = tupe(Info.znaky[0], x, y);
                    if(souradnice[0] >= 0){
                        pokracovat = false;
                        break;
                    }
                }
            }
            if(!pokracovat)
                break;
        }
        
        if(pokracovat){
            souradnice = obrana();
            if(souradnice[0] >= 0)
                pokracovat = false;
        }

        if(pokracovat)
            souradnice = utok();

        Info.plocha[souradnice[1]][souradnice[0]] = Info.znaky[1];
        okno.setPolicko(souradnice[0], souradnice[1], Character.toString(Info.znaky[1]));
        
        if(Piskvorky.kontrolaVyhry(Info.znaky[1], souradnice[0], souradnice[1]))
            Info.dohrano = true;
    }

    static int[] obrana(){
        //res[0] - x, res[1] - y
        int[] res = new int[2];
        res[0] = -1;
        res[1] = -1;

        for(int y = 0; y < Info.vyska; y++){
            for(int x = 0;  x < Info.sirka; x++){
                if(kontrolaVodorovne(Info.znaky[0], Info.pocet_na_vyhru - 1, x, y)){
                    res = vodorovne(Info.znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaSvisle(Info.znaky[0], Info.pocet_na_vyhru - 1, x, y)){
                    res = svisle(Info.znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaOstre(Info.znaky[0], Info.pocet_na_vyhru - 1, x, y)){
                    res = ostre(Info.znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
                if(kontrolaTupe(Info.znaky[0], Info.pocet_na_vyhru - 1, x, y)){
                    res = tupe(Info.znaky[1], x, y);
                    if(res[0] >= 0)
                        return res;
                }
            }
        }

        if(Info.pocet_na_vyhru > 3){
            for(int y = 0; y < Info.vyska; y++){
                for(int x = 0;  x < Info.sirka; x++){
                    if(predvidacVodorovne(x, y)){
                        res = vodorovne(Info.znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacSvisle(x, y)){
                        res = svisle(Info.znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacOstre(x, y)){
                        res = ostre(Info.znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                    if(predvidacTupe(x, y)){
                        res = tupe(Info.znaky[1], x, y);
                        if(res[0] >= 0)
                            return res;
                    }
                }
            }
        }

        return res;
    }

    static int[] utok(){
        //res[0] - x, res[1] - y
        int[] res = new int[2];
        res[0] = -1;
        int soucet = 0;
        int max = 0;
        int maxx = Info.pocet_na_vyhru - 1;

        do{
            for(int y = 0; y < Info.vyska; y++){
                for(int x = 0; x < Info.sirka; x++){
                    soucet = soucetVodorovne(Info.znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = vodorovne(Info.znaky[0], x, y);
                    }
                    soucet = soucetSvisle(Info.znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = svisle(Info.znaky[0], x, y);
                    }
                    soucet = soucetOstre(Info.znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = ostre(Info.znaky[0], x, y);
                    }
                    soucet = soucetTupe(Info.znaky[1], x, y);
                    if(soucet > max && soucet < maxx){
                        max = soucet;
                        res = tupe(Info.znaky[0], x, y);
                    }
                }
            }
            max = 0;
            maxx--;

            if(maxx == 0){
                int random_x, random_y;
                do{
                Random rand = new Random();
                random_x = rand.nextInt(Info.sirka);
                random_y = rand.nextInt(Info.vyska);

                }while(Info.plocha[random_y][random_x] != ' ');
                res[0] = random_x;
                res[1] = random_y;
            }
        }while(res[0] == -1);

        return res;
    }

    //-
    static boolean kontrolaVodorovne(char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetVodorovne(char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacVodorovne(int x, int y){
        int puvodni_x = x;
        int soucet = 0;

        //do prava
        while(true){
            if(x < Info.sirka){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
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
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
                    return false;
                else
                    break;
                x--;
            }
            else
                break;
        }

        if(soucet == Info.pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] vodorovne(char znak, int x, int y){
        int puvodni_x = x;
        int res[] = new int[2];
        res[1] = y;

        //do prava
        while(true){
            if(x < Info.sirka){
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
    static boolean kontrolaSvisle(char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetSvisle(char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacSvisle(int x, int y){
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(y >= 0){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
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
            if(y < Info.vyska){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
                    return false;
                else
                    break;
                y++;
            }
            else
                break;
        }

        if(soucet == Info.pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] svisle(char znak, int x, int y){
        int puvodni_y = y;
        int[] res = new int[2];
        res[0] = x;

        //nahoru
        while(true){
            if(y >= 0){
                if(Info.plocha[y][x] == ' '){
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
            if(y < Info.vyska){
                if(Info.plocha[y][x] == ' '){
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
    static boolean kontrolaOstre(char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetOstre(char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacOstre(int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x < Info.sirka && y >= 0){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
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
            if(x >= 0 && y < Info.vyska){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
                    return false;
                else
                    break;
                x--;
                y++;
            }
            else
                break;
        }

        if(soucet == Info.pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] ostre(char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int[] res = new int[2];

        //nahoru
        while(true){
            if(x < Info.sirka && y >= 0){
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
            if(x >= 0 && y < Info.vyska){
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
    static boolean kontrolaTupe(char znak, int pocet, int x, int y){
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

        if(soucet == pocet)
            return true;

        return false;
    }

    static int soucetTupe(char znak, int x, int y){
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

        return soucet;
    }

    static boolean predvidacTupe(int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int soucet = 0;

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
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
            if(x < Info.sirka && y < Info.vyska){
                if(Info.plocha[y][x] == Info.znaky[0])
                    soucet++;
                else if(Info.plocha[y][x] == Info.znaky[1])
                    return false;
                else
                    break;
                x++;
                y++;
            }
            else
                break;
        }

        if(soucet == Info.pocet_na_vyhru - 2)
            return true;

        return false;
    }

    static int[] tupe(char znak, int x, int y){
        int puvodni_x = x;
        int puvodni_y = y;
        int[] res = new int[2];

        //nahoru
        while(true){
            if(x >= 0 && y >= 0){
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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
            if(x < Info.sirka && y < Info.vyska){
                if(Info.plocha[y][x] == ' '){
                    res[0] = x;
                    res[1] = y;
                    return res;
                }
                else if(Info.plocha[y][x] == znak)
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

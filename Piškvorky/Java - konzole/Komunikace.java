import java.util.Scanner;

public class Komunikace {
    static int[] zalozeniPlochy(){
        Scanner sc = new Scanner(System.in);
        int x, y;
        while(true){
            y = 0;
            x = 0;
            Boolean plati = true;

            System.out.println("Zadej postupně výšku a šířku hracího pole (minimum je 3, maximum 10 a 30)");

            String s = sc.nextLine();
            if(s.length() <= 2){
                char[] pole = s.toCharArray();

                plati = kontrolaCisla(pole);
            }

            if(plati)
                y = Integer.parseInt(s);

            s = sc.nextLine();
            if(s.length() <= 2){
                char[] pole = s.toCharArray();

                plati = kontrolaCisla(pole);
            }

            if(plati)
                x = Integer.parseInt(s);

            if((y >= 3 && y <= 10) && (x >= 3 && x <= 30))
                break;
            
            System.out.println("\n\nChybně zadaná hodnota, zkus to znovu");
        }

        int[] res =  new int[2];
        res[0] = x;
        res[1] = y;
        return res;
    }

    static boolean volbaHry(){
        Scanner sc = new Scanner(System.in);
        String vyber = "";
        while(true){
            System.out.println("Zvol si možnost jak chceš hrát:");
            System.out.println("1. 1v1");
            System.out.println("2. Bot");
            vyber = sc.nextLine();
            
            if(vyber.equals("1") || vyber.equals("2"))
                break;

            System.out.println("\n\nChybně zadaná hodnota, zkus to znovu");
        }
        return vyber.equals("2");
    }

    static int volbaPoctu(int x, int y){
        Scanner sc = new Scanner(System.in);
        String vyber = "";
        int max;
        String uvod = "Zvol si kolik se musí spojit na výhru (minimum jsou 3 a maximum ";
        if(x > y){
            uvod += y + ")";
            max = y;
        }
        else{
            uvod += x + ")";
            max = x;
        }
        while(true){
            System.out.println(uvod);
            vyber = sc.nextLine();
            char[] pole = vyber.toCharArray();

            int i = 0;
            if(kontrolaCisla(pole))
                i = Integer.parseInt(vyber);
            if(i >= 3 && i <= max)
                break;

            System.out.println("\n\nChybně zadaná hodnota, zkus to znovu");
        }
        return Integer.parseInt(vyber);
    }

    static Hraci_plocha volbaSouradnic(Hraci_plocha plocha, char znak, int pocet_na_vyhru){
        Scanner sc = new Scanner(System.in);
        String x, y;

        do{
            while(true){
                System.out.println("Zadej postupně souřadnice x a y políčka, které chceš označit");
                System.out.println("x - šířka");
                System.out.println("y - výška");

                x = sc.nextLine();
                y = sc.nextLine();

                if(kontrolaSouradnice(x) && kontrolaSouradnice(y))
                    break;
                System.out.println("\n\nNeplatné souřadnice");
            }
        }while(!plocha.pridatPolicko(x, y, znak));

        int[] souradnice = stringToInt(x, y);
        plocha.setDohrano(Piskvorky.kontrolaVyhry(plocha, znak, pocet_na_vyhru, souradnice[0], souradnice[1]));

        if(plocha.getDohrano())
            System.out.println("Vyhrál hráč s " + znak);
        
        return plocha;
    }

    static char volbaZnaku(){
        Scanner sc = new Scanner(System.in);
        String volba;
        while(true){
            System.out.println("Vyber si znak za který chceš hrát");
            System.out.println("1. X (začína)");
            System.out.println("2. O");

            volba = sc.nextLine();

            volba = volba.toUpperCase();
            if(volba.equals("X") || volba.equals("1"))
                return 'X';
            if(volba.equals("O") || volba.equals("2"))
                return 'O';
        }
    }

    static Hraci_plocha volbaSouradnicBot(Hraci_plocha plocha, char znak, int pocet_na_vyhru){
        Scanner sc = new Scanner(System.in);
        String x, y;

        do{
            while(true){
                System.out.println("Zadej postupně souřadnice x a y políčka, které chceš označit");
                System.out.println("x - šířka");
                System.out.println("y - výška");

                x = sc.nextLine();
                y = sc.nextLine();

                if(kontrolaSouradnice(x) && kontrolaSouradnice(y))
                    break;
                System.out.println("\n\nNeplatné souřadnice");
            }
        }while(!plocha.pridatPolicko(x, y, znak));

        int[] souradnice = stringToInt(x, y);
        plocha.setDohrano(Piskvorky.kontrolaVyhry(plocha, znak, pocet_na_vyhru, souradnice[0], souradnice[1]));

        if(plocha.getDohrano())
            System.out.println("Vyhrál si, gratuluji!");

        plocha.setPosledni_x(x);
        plocha.setPosledni_y(y);
        
        return plocha;
    }

    static Boolean kontrolaCisla(char[] pole){
        for(int i = 0; i < pole.length; i++){
            if(!(pole[i] >= 48 && pole[i] <= 57)){
                return false;
            }
        }
        return true;
    }

    static boolean kontrolaSouradnice(String string){
        if(string.length() > 1)
            return false;
        
        string = string.toUpperCase();
        for(int i = 0; i < string.length(); i++){
            if(!(string.charAt(i) >= 49 && string.charAt(i) <= 57) && !(string.charAt(i) >= 65 && string.charAt(i) <= 90)){
                return false;
            }
        }
        return true;
    }

    static int[] stringToInt(String x, String y){
        int X, Y;
        x = x.toUpperCase();
        y = y.toUpperCase();
        
        if(x.charAt(0) <= 57){
            X = Integer.parseInt(x) - 1;
        }
        else{
            X = x.toCharArray()[0] - 55 - 1;
        }

        if(y.charAt(0) <= 57){
            Y = Integer.parseInt(y) - 1;
        }
        else{
            Y = y.toCharArray()[0] - 55 - 1;
        }

        int[] res = new int[2];
        res[0] = X;
        res[1] = Y;
        return res;
    }
}

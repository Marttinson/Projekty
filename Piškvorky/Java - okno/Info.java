public class Info {
    static int pocet_kol = 0;
    static int sirka = 10;
    static int vyska = 10;
    static int pocet_na_vyhru = 4;
    static boolean hra_s_botem = false;
    static char[][] plocha;
    static boolean dohrano = false;
    static char[] znaky = new char[2];

    static void vypisPlochy(){
        for(int i = 0; i < vyska; i++){
            for(int j = 0; j < sirka; j++){
                System.out.print(plocha[i][j]);
            }
            System.out.println();
        }
    }
}

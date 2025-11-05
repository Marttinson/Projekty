public class Hraci_plocha {
    private char[][] plocha;
    private int vyska;
    private int sirka;
    private char[] souradnice = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U'};
    private boolean dohrano;
    private String posledni_x;
    private String posledni_y;

    public void zalozeniPlochy(int vyska, int sirka){
        this.vyska = vyska;
        this.sirka = sirka;
        dohrano = false;

        plocha = new char[vyska][sirka];

        for(int i = 0; i < vyska; i++){
            for(int j = 0; j < sirka; j++){
                plocha[i][j] = ' ';
            }
        }
    }

    public void vypisHraciPlochy(){
        int b = 0;
        System.out.print(" ");
        for(int j = 0; j < sirka * 2 + 1; j++){
            if(j % 2 == 1){
                System.out.print(souradnice[b]);
                b++;
            }
            else
                System.out.print("-");
        }
        System.out.println();

        for(int i = 0; i < vyska; i++){
            System.out.print(souradnice[i] + "|");
            for(int j = 0; j < sirka; j++){
                System.out.print(plocha[i][j] + "|");
            }

            System.out.println();
            for(int j = 0; j < sirka * 2 + 1; j++)
                System.out.print("-");
            System.out.println();
        }
    }

    public boolean pridatPolicko(String x, String y, char znak){
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

        if (kontrolaPolicka(X, Y)){
            plocha[Y][X] = znak;
            return true;
        }
        return false;
    }

    public void pridatPolicko(int x, int y, char znak){
        plocha[y][x] = znak;
    }

    private boolean kontrolaPolicka(int x, int y){
        if(x >= sirka)
            return false;
        if(y >= vyska)
            return false;
        if(plocha[y][x] == ' ')
            return true;

        System.out.println("\n\nObsazené souřadnice");
        return false;
    }

    public boolean kontrolaSouradnice(int x, int y){
        if(plocha[y][x] == ' ')
            return true;
        return false;
    }

    public int getVyska() {
        return vyska;
    }

    public int getSirka() {
        return sirka;
    }

    public char[] getSouradnice() {
        return souradnice;
    }

    public char CharAt(int x, int y){
        return plocha[y][x];
    }

    public boolean getDohrano(){
        return dohrano;
    }
    
    public String getPosledni_x() {
        return posledni_x;
    }

    public String getPosledni_y() {
        return posledni_y;
    }

    public void setPosledni_x(String posledni_x) {
        this.posledni_x = posledni_x;
    }

    public void setPosledni_y(String posledni_y) {
        this.posledni_y = posledni_y;
    }

    public void setDohrano(boolean dohrano) {
        this.dohrano = dohrano;
    }
}

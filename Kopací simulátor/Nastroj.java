public class Nastroj {
    private String nazev;
    private int nasobitel;
    private int cena;
    
    public Nastroj(String nazev, int nasobitel, int cena) {
        this.nazev = nazev;
        this.nasobitel = nasobitel;
        this.cena = cena;
    }

    public void nastaveni(Nastroj nastroj){
        nazev = nastroj.nazev;
        nasobitel = nastroj.nasobitel;
        cena = nastroj.cena;
    }

    public int getNasobitel() {
        return nasobitel;
    }

    public int getCena() {
        return cena;
    }

    @Override
    public String toString() {
        return nazev + " za " + cena + ", vykope: " + nasobitel;
    }
}

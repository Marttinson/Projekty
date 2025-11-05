public class Batoh {
    private String nazev;
    private int velikost;
    private int cena;

    public Batoh(String nazev, int velikost, int cena) {
        this.nazev = nazev;
        this.velikost = velikost;
        this.cena = cena;
    }

    public void nastaveni(Batoh batoh){
        nazev = batoh.nazev;
        velikost = batoh.velikost;
        cena = batoh.cena;
    }

    public int getVelikost() {
        return velikost;
    }

    public int getCena() {
        return cena;
    }

    @Override
    public String toString() {
        return nazev + " za " + cena + ", kapacita: " + velikost;
    }
}

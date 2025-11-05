public class Item {
    private String nazev;
    private int hodonta;
    private int zakladni_hodnota;
    private int pocet;

    Item(String nazev, int hodnota){
        this.nazev = nazev;
        this.hodonta = hodnota;
        zakladni_hodnota = hodnota;
        pocet = 0;
    }

    public void pridat() {
        pocet++;
    }

    public void zvysHodntou(int nasobitel){
        hodonta = zakladni_hodnota * nasobitel;
    }

    public String getNazev() {
        return nazev;
    }

    public int getHodonta() {
        return hodonta;
    }

    public int getPocet() {
        return pocet;
    }

    public void setPocet(int pocet) {
        this.pocet = pocet;
    }

    @Override
    public String toString() {
        return pocet + "x " + nazev + ", hodnota: " + hodonta;
    }
}

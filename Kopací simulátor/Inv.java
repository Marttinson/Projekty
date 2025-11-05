public class Inv {
    private Item kamen;
    private Item plechovka;
    private Item zelezo;
    private Item med;
    private Item zlato;
    private Item diamand;
    private Item fosilie;
    private int velikost_inv;
    private int pocet_itemu;
    
    Inv(){
        kamen = new Item("Kamen", 1);
        plechovka = new Item("Plechovka", 2);
        zelezo = new Item("Železo", 3);
        med = new Item("Měď", 4);
        zlato = new Item("Zlato", 50);
        diamand = new Item("Diamand", 250);
        fosilie = new Item("Fosilie", 500);
        velikost_inv = 1;
        pocet_itemu = 0;
    }

    public void vypisItemu(){
        System.out.println(kamen);
        System.out.println(plechovka);
        System.out.println(zelezo);
        System.out.println(med);
        System.out.println(zlato);
        System.out.println(diamand);
        System.out.println(fosilie);
    }

    public void vypis(){
        System.out.println("Tvoje inventář:");
        vypisItemu();
    }

    public void vypisHlavicky(){
        System.out.println("Inventář: " + pocet_itemu + "/" + velikost_inv);
    }

    public int prodej(){
        vypisItemu();
        
        int soucet = 0;

        soucet += kamen.getPocet() * kamen.getHodonta();
        soucet += plechovka.getPocet() * plechovka.getHodonta();
        soucet += zelezo.getPocet() * zelezo.getHodonta();
        soucet += med.getPocet() * med.getHodonta();
        soucet += zlato.getPocet() * zlato.getHodonta();
        soucet += diamand.getPocet() * diamand.getHodonta();
        soucet += fosilie.getPocet() * fosilie.getHodonta();

        kamen.setPocet(0);
        plechovka.setPocet(0);
        zelezo.setPocet(0);
        med.setPocet(0);
        zlato.setPocet(0);
        diamand.setPocet(0);
        fosilie.setPocet(0);
        pocet_itemu = 0;

        System.out.println("Tohle všechno si prodal za " + soucet);
        return soucet;
    }

    public void setNasobitel(int nasobitel) {
        kamen.zvysHodntou(nasobitel);
        plechovka.zvysHodntou(nasobitel);
        zelezo.zvysHodntou(nasobitel);
        med.zvysHodntou(nasobitel);
        zlato.zvysHodntou(nasobitel);
        diamand.zvysHodntou(nasobitel);
        fosilie.zvysHodntou(nasobitel);
    }

    public void setVelikost_inv(int velikost_inv) {
        this.velikost_inv = velikost_inv;
    }

    public void setPocet_itemu(int pocet_itemu) {
        this.pocet_itemu = pocet_itemu;
    }

    public int pridatKamen(){
        kamen.pridat();
        pocet_itemu++;
        return kamen.getHodonta();
    }

    public int pridatPlechovku(){
        plechovka.pridat();
        pocet_itemu++;
        return plechovka.getHodonta();
    }

    public int pridatZelezo(){
        zelezo.pridat();
        pocet_itemu++;
        return zelezo.getHodonta();
    }

    public int pridatMed(){
        med.pridat();
        pocet_itemu++;
        return med.getHodonta();
    }

    public int pridatZlato(){
        zlato.pridat();
        pocet_itemu++;
        return zlato.getHodonta();
    }

    public int pridatDiamand(){
        diamand.pridat();
        pocet_itemu++;
        return diamand.getHodonta();
    }

    public int pridatFosilie(){
        fosilie.pridat();
        pocet_itemu++;
        return fosilie.getHodonta();
    }

    public int getPocet_itemu() {
        return pocet_itemu;
    }

    public int getVelikost_inv() {
        return velikost_inv;
    }
}

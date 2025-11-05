public class Hrac {
    private String jmeno;
    private int penize;
    private int xp;
    public Inv inv;
    private Nastroj nastroj;
    private int cislo_nastroje;
    private Batoh batoh;
    private int cislo_batohu;
    private String[] ranky = {"Amatér", "Mgr.", "Zkušený", "Polobůh", "Ing."};
    private int potrebne_xp;
    private int rank;
    
    Hrac(){
        jmeno = "";
        penize = 10;
        xp = 0;
        inv = new Inv();
        nastroj = new Nastroj("Ruce", 1, 0);
        batoh = new Batoh("Kapsy", 1, 0);
        potrebne_xp = 10;
        rank = 0;

        cislo_nastroje = 0;
        cislo_batohu = 0;
    }

    public void prodej(){
        penize += inv.prodej();
    }

    public void vypisRanku(){
        System.out.println("Tvůj rank: " + ranky[rank]);
    }

    public void vypisXp(){
        if(ranky[rank].equals("Ing.")){
            System.out.println("Xp: " + xp);
        }
        else{
            System.out.println("Xp: " + xp + "/" + potrebne_xp);
        }
    }

    public void vypisPenez(){
        System.out.println("Penize: " + penize);
    }

    public void vypisHrace(){
        System.out.println(jmeno);
        vypisRanku();
        vypisXp();
        vypisPenez();
        System.out.println("Nástroj: " + nastroj);
        System.out.println("Batoh: " + batoh);
        inv.vypisHlavicky();
    }

    public boolean kontrolaXp(){
        if(xp > potrebne_xp){
            xp -= potrebne_xp;
            potrebne_xp *= 10;
            rank++;
            return true;
        }
        return false;
    }

    public void pridatXp(int xp){
        this.xp += xp;
    }

    public String getJmeno() {
        return jmeno;
    }

    public void setJmeno(String jmeno) {
        this.jmeno = jmeno;
    }

    public int getPenize() {
        return penize;
    }

    public Nastroj getNastroj(){
        return nastroj;
    }

    public String getRank(){
        return ranky[rank];
    }

    public int getCislo_nastroje() {
        return cislo_nastroje;
    }

    public int getCislo_batohu() {
        return cislo_batohu;
    }

    public void setPenize(int penize) {
        this.penize = penize;
    }

    public void setNastroj(Nastroj nastroj){
        this.nastroj.nastaveni(nastroj);
        inv.setNasobitel(this.nastroj.getNasobitel());
    }

    public void setBatoh(Batoh batoh){
        this.batoh.nastaveni(batoh);
        inv.setVelikost_inv(this.batoh.getVelikost());
    }

    public void setCislo_nastroje(int cislo_nastroje) {
        this.cislo_nastroje = cislo_nastroje;
    }

    public void setCislo_batohu(int cislo_batohu) {
        this.cislo_batohu = cislo_batohu;
    }
}

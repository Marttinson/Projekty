import java.util.Random;
import java.util.Scanner;

public class Hra {
    private Hrac hrac;
    private Scanner sc;
    private boolean hraje_se;
    private String vyber;
    private Obchod obchod;

    Hra(){
        hrac = new Hrac();
        sc = new Scanner(System.in);
        hraje_se = true;
        vyber = "";
        obchod = new Obchod();

        zalozeniHrace();
    }

    public void zalozeniHrace(){
        System.out.println("--------------------------");
        System.out.println("---- Kopací Simulator ----");
        System.out.println("--------------------------");
        System.out.println();

        System.out.print("Zadej své jméno: ");
        hrac.setJmeno(sc.nextLine());
    }

    public void hrej(){
        while(hraje_se){
            menu();
        }
    }

    private void hlavicka(){
        clear();
        System.out.println("----------------------" + "\n-- Kopací Simulator --" + "\n----------------------\n");
        hrac.vypisHrace();
    }

    private void menu(){
        hlavicka();
        
        System.out.println("\n1. Kopání");
        System.out.println("2. Inventář");
        System.out.println("3. Prodej");
        System.out.println("4. Obchod\n");

        System.out.print("Rozhodnutí: ");
        vyber = sc.nextLine();
        rozhodnuti();
    }

    private void rozhodnuti(){
        switch(vyber){
        case "1":
            kopani();
            break;
        case "2":
            inv();
            break;
        case "3":
            prodej();
            break;
        case "4":
            obchod();
            break;
        default:
            System.out.println("Neplatná volba");
            sc.nextLine();
            menu();
            break;
        }

    }

    private void kopani(){
        if(hrac.inv.getPocet_itemu() < hrac.inv.getVelikost_inv()){
            System.out.print("Vykopal si ");

            for (int i = 0; i < hrac.getNastroj().getNasobitel(); i++){
                if(hrac.inv.getPocet_itemu() < hrac.inv.getVelikost_inv()){
                    Random random = new Random();
                    int a = random.nextInt(100) + 1;

                    if (a <= 39){
                        System.out.print("kámen");
                        hrac.pridatXp(hrac.inv.pridatKamen());
                    }
                    else if (a <= 69){
                        System.out.print("plechovku");
                        hrac.pridatXp(hrac.inv.pridatPlechovku());
                    }
                    else if (a <= 81){
                        System.out.print("železo");
                        hrac.pridatXp(hrac.inv.pridatZelezo());
                    }
                    else if (a <= 91){
                        System.out.print("měď");
                        hrac.pridatXp(hrac.inv.pridatMed());
                    }
                    else if (a <= 97){
                        System.out.print("zlato");
                        hrac.pridatXp(hrac.inv.pridatZlato());
                    }
                    else if (a <= 99){
                        System.out.print("diamand");
                        hrac.pridatXp(hrac.inv.pridatDiamand());
                    }
                    else{
                        System.out.print("fosilii");
                        hrac.pridatXp(hrac.inv.pridatFosilie());
                    }

                    if(i + 1 < hrac.getNastroj().getNasobitel() && i + 1 < hrac.inv.getVelikost_inv())
                        System.out.print(", ");
                }
            }
            System.out.println();
            if(hrac.kontrolaXp())
                System.out.println("Gratuluji k povýšení na rank: " + hrac.getRank());
        }
        else{
            System.out.println("Tvůj inventář je plný");
        }

        sc.nextLine();
    }

    private void inv(){
        clear();
        hrac.inv.vypis();
        
        sc.nextLine();
    }

    private void prodej(){
        hrac.prodej();

        sc.nextLine();
    }

    private void obchod(){
        obchod.vypis();

        boolean koupeno = false;
        String vyber = sc.nextLine();
        switch(vyber){
            case "1":
                if(hrac.getPenize() >= obchod.getLopatu(0).getCena()){
                    if(hrac.getCislo_nastroje() > 0){
                        System.out.println("Vlastníš lepší nástroj");
                        sc.nextLine();
                    }
                    else{
                        hrac.setNastroj(obchod.getLopatu(0));
                        hrac.setPenize(hrac.getPenize() - obchod.getLopatu(0).getCena());
                        hrac.setCislo_nastroje(1);
                    }
                    koupeno = true;
                }
                break;
            case "2":
                if(hrac.getPenize() >= obchod.getLopatu(1).getCena()){
                    if(hrac.getCislo_nastroje() > 1){
                        System.out.println("Vlastníš lepší nástroj");
                        sc.nextLine();
                    }
                    else{
                        hrac.setNastroj(obchod.getLopatu(1));
                        hrac.setPenize(hrac.getPenize() - obchod.getLopatu(1).getCena());
                        hrac.setCislo_nastroje(2);
                    }
                    koupeno = true;
                }
                break;
            case "3":
                if(hrac.getPenize() >= obchod.getLopatu(2).getCena()){
                    if(hrac.getCislo_nastroje() > 2){
                        System.out.println("Vlastníš lepší nástroj");
                        sc.nextLine();
                    }
                    else{
                        hrac.setNastroj(obchod.getLopatu(2));
                        hrac.setPenize(hrac.getPenize() - obchod.getLopatu(2).getCena());
                        hrac.setCislo_nastroje(3);
                    }
                    koupeno = true;
                }
                break;
            case "4":
                if(hrac.getPenize() >= obchod.getLopatu(3).getCena()){
                    if(hrac.getCislo_nastroje() > 3){
                        System.out.println("Vlastníš lepší nástroj");
                        sc.nextLine();
                    }
                    else{
                        hrac.setNastroj(obchod.getLopatu(3));
                        hrac.setPenize(hrac.getPenize() - obchod.getLopatu(3).getCena());
                        hrac.setCislo_nastroje(4);
                    }
                    koupeno = true;
                }
                break;
            case "5":
                if(hrac.getPenize() >= obchod.getLopatu(4).getCena()){
                    if(hrac.getCislo_nastroje() > 4){
                        System.out.println("Vlastníš lepší nástroj");
                        sc.nextLine();
                    }
                    else{
                        hrac.setNastroj(obchod.getLopatu(4));
                        hrac.setPenize(hrac.getPenize() - obchod.getLopatu(4).getCena());
                        hrac.setCislo_nastroje(5);
                    }
                    koupeno = true;
                }
                break;
            case "6":
                if(hrac.getPenize() >= obchod.getBatoh(0).getCena()){
                    if(hrac.getCislo_batohu() > 0){
                        System.out.println("Vlastníš lepší batoh");
                        sc.nextLine();
                    }
                    else{
                        hrac.setBatoh(obchod.getBatoh(0));
                        hrac.setPenize(hrac.getPenize() - obchod.getBatoh(0).getCena());
                        hrac.setCislo_batohu(1);
                    }
                    koupeno = true;
                }
                break;
            case "7":
                if(hrac.getPenize() >= obchod.getBatoh(1).getCena()){
                    if(hrac.getCislo_batohu() > 1){
                        System.out.println("Vlastníš lepší batoh");
                        sc.nextLine();
                    }
                    else{
                        hrac.setBatoh(obchod.getBatoh(1));
                        hrac.setPenize(hrac.getPenize() - obchod.getBatoh(1).getCena());
                        hrac.setCislo_batohu(2);
                    }
                    koupeno = true;
                }
                break;
            case "8":
                if(hrac.getPenize() >= obchod.getBatoh(2).getCena()){
                    if(hrac.getCislo_batohu() > 2){
                        System.out.println("Vlastníš lepší batoh");
                        sc.nextLine();
                    }
                    else{
                        hrac.setBatoh(obchod.getBatoh(2));
                        hrac.setPenize(hrac.getPenize() - obchod.getBatoh(2).getCena());
                        hrac.setCislo_batohu(3);
                    }
                    koupeno = true;
                }
                break;
            case "9":
                if(hrac.getPenize() >= obchod.getBatoh(3).getCena()){
                    if(hrac.getCislo_batohu() > 3){
                        System.out.println("Vlastníš lepší batoh");
                        sc.nextLine();
                    }
                    else{
                        hrac.setBatoh(obchod.getBatoh(3));
                        hrac.setPenize(hrac.getPenize() - obchod.getBatoh(3).getCena());
                        hrac.setCislo_batohu(4);
                    }
                    koupeno = true;
                }
                break;
            default:
                koupeno = true;
                break;
        }
        if(!koupeno){
            System.out.println("Nedostatek peněz");
            sc.nextLine();
        }

    }

    private void clear(){
        for(int i = 0; i < 25; i++){
            System.out.println();
        }
    }
}

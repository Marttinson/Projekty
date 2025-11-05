import java.util.ArrayList;

public class Obchod {
    private ArrayList<Nastroj> lopaty;
    private ArrayList<Batoh> batohy;

    public Obchod(){
        lopaty = new ArrayList<Nastroj>();
        batohy = new ArrayList<Batoh>();

        lopaty.add(new Nastroj("Rezavá lopata", 2, 10));
        lopaty.add(new Nastroj("Nová lopata", 3, 500));
        lopaty.add(new Nastroj("Krumpáč", 4, 1500));
        lopaty.add(new Nastroj("Zbíječka", 5, 5000));
        lopaty.add(new Nastroj("Bagr", 10, 25000));

        batohy.add(new Batoh("Batůžek", 10, 250));
        batohy.add(new Batoh("Kýbl", 25, 1000));
        batohy.add(new Batoh("Kolečka", 100, 2500));
        batohy.add(new Batoh("Tatra", 250, 20000));
    }

    public void vypis(){
        int a = 1;
        System.out.println("Lopaty:");
        for(int i = 0; i < lopaty.size(); i++){
            System.out.println(a++ + "." + lopaty.get(i));
        }

        System.out.println("\nBatohy:");
        for(int i = 0; i < batohy.size(); i++){
            System.out.println(a++ + "." + batohy.get(i));
        }

        System.out.print("\nZvol svoji položku (Neplatnou volbu pro krok zpět): ");
    }

    public Nastroj getLopatu(int index){
        return lopaty.get(index);
    }

    public Batoh getBatoh(int index){
        return batohy.get(index);
    }
}

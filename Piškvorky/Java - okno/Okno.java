import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

import java.awt.Color;
import java.awt.Font;

public class Okno {
    private JFrame okno = new JFrame();
    private Policko[][] plocha;
    final private int SIRKA = 1100;
    final private int VYSKA = 800;

    private JPanel menu = new JPanel();

    private JButton sirka = new JButton();
    private JButton sirka_minus = new JButton();
    private JButton sirka_plus = new JButton();

    private JButton vyska = new JButton();
    private JButton vyska_minus = new JButton();
    private JButton vyska_plus = new JButton();

    private JButton pocet_na_vyhru = new JButton();
    private JButton pocet_minus = new JButton();
    private JButton pocet_plus = new JButton();

    private JButton bot_tlacitko = new JButton();
    private JButton bot_x = new JButton();
    private JButton bot_y = new JButton();

    private JButton hrat = new JButton();

    Okno(){
        okno.setTitle("Piškvorky");
        okno.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        okno.setResizable(false);
        okno.setSize(SIRKA, VYSKA);
        okno.getContentPane().setBackground(new Color(0, 0, 0));
        okno.setLayout(null);
        okno.setVisible(true);

        nastaveniTlacitek();
    }

    private void nastaveniTlacitek(){
        menu.setVisible(true);
        menu.setBounds(0, 0, SIRKA, VYSKA);
        menu.setLayout(null);
        menu.setBackground(new Color(100, 100, 100));

        nastaveniSirky();
        nastaveniVysky();
        nastaveniPoctu();
        nastaveniBot();

        hrat.setBounds(405, 500, 300, 50);
        hrat.setText("Hrat");
        hrat.setFont(new Font("MV boli", Font.BOLD, 24));
        hrat.setBorder(BorderFactory.createLineBorder(Color.black));
        hrat.setBackground(new Color(100, 200, 100));
        hrat.addActionListener(e -> zacatekHry());
        menu.add(hrat);

        okno.add(menu);
    }

    private void nastaveniSirky(){
        sirka.setBounds(405, 150, 300, 50);
        sirka.setText("Sirka (max 20): " + Integer.toString(Info.sirka));
        sirka.setFont(new Font("MV boli", Font.BOLD, 24));
        sirka.setBorder(BorderFactory.createLineBorder(Color.black));
        sirka.setEnabled(false);
        sirka.setBackground(new Color(100, 100, 255));
        menu.add(sirka);

        sirka_minus.setBounds(345, 150, 50, 50);
        sirka_minus.setText("-");
        sirka_minus.setFont(new Font("MV boli", Font.BOLD, 24));
        sirka_minus.setBorder(BorderFactory.createLineBorder(Color.black));
        sirka_minus.setBackground(new Color(100, 100, 255));
        sirka_minus.addActionListener(e -> akceSirka(-1));
        menu.add(sirka_minus);

        sirka_plus.setBounds(715, 150, 50, 50);
        sirka_plus.setText("+");
        sirka_plus.setFont(new Font("MV boli", Font.BOLD, 24));
        sirka_plus.setBorder(BorderFactory.createLineBorder(Color.black));
        sirka_plus.setBackground(new Color(100, 100, 255));
        sirka_plus.addActionListener(e -> akceSirka(1));
        menu.add(sirka_plus);
    }

    private void nastaveniVysky(){
        vyska.setBounds(405, 275, 300, 50);
        vyska.setText("Vyska (max 10): " + Integer.toString(Info.vyska));
        vyska.setFont(new Font("MV boli", Font.BOLD, 24));
        vyska.setBorder(BorderFactory.createLineBorder(Color.black));
        vyska.setEnabled(false);
        vyska.setBackground(new Color(100, 100, 255));
        menu.add(vyska);

        vyska_minus.setBounds(345, 275, 50, 50);
        vyska_minus.setText("-");
        vyska_minus.setFont(new Font("MV boli", Font.BOLD, 24));
        vyska_minus.setBorder(BorderFactory.createLineBorder(Color.black));
        vyska_minus.setBackground(new Color(100, 100, 255));
        vyska_minus.addActionListener(e -> akceVyska(-1));
        menu.add(vyska_minus);

        vyska_plus.setBounds(715, 275, 50, 50);
        vyska_plus.setText("+");
        vyska_plus.setFont(new Font("MV boli", Font.BOLD, 24));
        vyska_plus.setBorder(BorderFactory.createLineBorder(Color.black));
        vyska_plus.setBackground(new Color(255, 100, 100));
        vyska_plus.addActionListener(e -> akceVyska(1));
        menu.add(vyska_plus);
    }

    private void nastaveniPoctu(){
        pocet_na_vyhru.setBounds(405, 400, 300, 50);
        pocet_na_vyhru.setText("Na vyhru (max 10): " + Integer.toString(Info.pocet_na_vyhru));
        pocet_na_vyhru.setFont(new Font("MV boli", Font.BOLD, 24));
        pocet_na_vyhru.setBorder(BorderFactory.createLineBorder(Color.black));
        pocet_na_vyhru.setEnabled(false);
        pocet_na_vyhru.setBackground(new Color(100, 100, 255));
        menu.add(pocet_na_vyhru);

        pocet_minus.setBounds(345, 400, 50, 50);
        pocet_minus.setText("-");
        pocet_minus.setFont(new Font("MV boli", Font.BOLD, 24));
        pocet_minus.setBorder(BorderFactory.createLineBorder(Color.black));
        pocet_minus.setBackground(new Color(100, 100, 255));
        pocet_minus.addActionListener(e -> akcePocet(-1));
        menu.add(pocet_minus);

        pocet_plus.setBounds(715, 400, 50, 50);
        pocet_plus.setText("+");
        pocet_plus.setFont(new Font("MV boli", Font.BOLD, 24));
        pocet_plus.setBorder(BorderFactory.createLineBorder(Color.black));
        pocet_plus.setBackground(new Color(100, 100, 255));
        pocet_plus.addActionListener(e -> akcePocet(1));
        menu.add(pocet_plus);
    }

    private void nastaveniBot(){
        bot_tlacitko.setBounds(405, 50, 300, 50);
        bot_tlacitko.setText("BOT");
        bot_tlacitko.setFont(new Font("MV boli", Font.BOLD, 24));
        bot_tlacitko.setBorder(BorderFactory.createLineBorder(Color.black));
        bot_tlacitko.setBackground(new Color(255, 100, 100));
        bot_tlacitko.addActionListener(e -> akceBot());
        bot_tlacitko.setFocusable(false);
        menu.add(bot_tlacitko);

        bot_x.setBounds(345, 50, 50, 50);
        bot_x.setText("X");
        bot_x.setFont(new Font("MV boli", Font.BOLD, 24));
        bot_x.setBorder(BorderFactory.createLineBorder(Color.black));
        bot_x.setBackground(new Color(100, 255, 100));
        bot_x.addActionListener(e -> akceZnak('X'));
        bot_x.setFocusable(false);
        bot_x.setVisible(false);
        menu.add(bot_x);

        bot_y.setBounds(715, 50, 50, 50);
        bot_y.setText("O");
        bot_y.setFont(new Font("MV boli", Font.BOLD, 24));
        bot_y.setBorder(BorderFactory.createLineBorder(Color.black));
        bot_y.setBackground(new Color(255, 100, 100));
        bot_y.addActionListener(e -> akceZnak('O'));
        bot_y.setFocusable(false);
        bot_y.setVisible(false);
        menu.add(bot_y);

        Info.znaky[0] = 'X';
        Info.znaky[1] = 'O';
    }

    private void akceSirka(int cislo){
        if(menu.isVisible()){
            if(Info.sirka + cislo >= 3 && Info.sirka + cislo <= 20){
                Info.sirka += cislo;
                sirka.setText("Sirka (max 20): " + Integer.toString(Info.sirka));

                if(Info.sirka < Info.pocet_na_vyhru){
                    Info.pocet_na_vyhru = Info.sirka;
                    pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.sirka) + "): " + Integer.toString(Info.pocet_na_vyhru));
                }
                else{
                    if(Info.sirka < Info.vyska)
                        pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.sirka) + "): " + Integer.toString(Info.pocet_na_vyhru));
                    else
                    pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.vyska) + "): " + Integer.toString(Info.pocet_na_vyhru));
                }

                if(Info.sirka == 3){
                    pocet_plus.setBackground(new Color(255, 100, 100));
                    pocet_minus.setBackground(new Color(255, 100, 100));
                }
                else if(Info.sirka == Info.pocet_na_vyhru)
                    pocet_plus.setBackground(new Color(255, 100, 100));
                else{
                    pocet_plus.setBackground(new Color(100, 100, 255));
                    pocet_minus.setBackground(new Color(100, 100, 255));
                }
            }
            if(Info.sirka == 20)
                sirka_plus.setBackground(new Color(255, 100, 100));
            else if(Info.sirka == 3)
                sirka_minus.setBackground(new Color(255, 100, 100));
            else{
                sirka_plus.setBackground(new Color(100, 100, 255));
                sirka_minus.setBackground(new Color(100, 100, 255));
            }
        }
    }

    private void akceVyska(int cislo){
        if(menu.isVisible()){
            if(Info.vyska + cislo >= 3 && Info.vyska + cislo <= 10){
                Info.vyska += cislo;
                vyska.setText("Vyska (max 10): " + Integer.toString(Info.vyska));

                if(Info.vyska < Info.pocet_na_vyhru){
                    Info.pocet_na_vyhru = Info.vyska;
                    pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.vyska) + "): " + Integer.toString(Info.pocet_na_vyhru));
                }
                else{
                    if(Info.sirka < Info.vyska)
                        pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.sirka) + "): " + Integer.toString(Info.pocet_na_vyhru));
                    else
                    pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(Info.vyska) + "): " + Integer.toString(Info.pocet_na_vyhru));
                }

                if(Info.vyska == 3){
                    pocet_plus.setBackground(new Color(255, 100, 100));
                    pocet_minus.setBackground(new Color(255, 100, 100));
                }
                else if(Info.vyska == Info.pocet_na_vyhru)
                    pocet_plus.setBackground(new Color(255, 100, 100));
                else{
                    pocet_plus.setBackground(new Color(100, 100, 255));
                    pocet_minus.setBackground(new Color(100, 100, 255));
                }
            }
            if(Info.vyska == 10)
                vyska_plus.setBackground(new Color(255, 100, 100));
            else if(Info.sirka == 3)
                vyska_minus.setBackground(new Color(255, 100, 100));
            else{
                vyska_plus.setBackground(new Color(100, 100, 255));
                vyska_minus.setBackground(new Color(100, 100, 255));
            }
        }
    }

    private void akcePocet(int cislo){
        if(menu.isVisible()){
            int max = 0;
            if(Info.sirka < Info.vyska)
                max = Info.sirka;
            else
                max = Info.vyska;

            if(Info.pocet_na_vyhru + cislo >= 3 && Info.pocet_na_vyhru + cislo <= max){
                Info.pocet_na_vyhru += cislo;
                pocet_na_vyhru.setText("Na vyhru (max " + Integer.toString(max) + "): " + Integer.toString(Info.pocet_na_vyhru));
            }
            
            if(max == 3){
                pocet_plus.setBackground(new Color(255, 100, 100));
                pocet_minus.setBackground(new Color(255, 100, 100));
            }
            else{
                if(Info.pocet_na_vyhru == max)
                    pocet_plus.setBackground(new Color(255, 100, 100));
                else if(Info.pocet_na_vyhru == 3)
                    pocet_minus.setBackground(new Color(255, 100, 100));
                else{
                    pocet_plus.setBackground(new Color(100, 100, 255));
                    pocet_minus.setBackground(new Color(100, 100, 255));
                }
            }
        }
    }

    private void akceBot(){
        if(Info.hra_s_botem){
            Info.hra_s_botem = false;
            bot_tlacitko.setBackground(new Color(255, 100, 100));
            bot_x.setVisible(false);
            bot_y.setVisible(false);
        }
        else{
            Info.hra_s_botem = true;
            bot_tlacitko.setBackground(new Color(100, 255, 100));
            bot_x.setVisible(true);
            bot_y.setVisible(true);
        }
    }

    private void akceZnak(char znak){
        if(znak == 'X'){
            Info.znaky[0] = 'X';
            Info.znaky[1] = 'O';
            bot_x.setBackground(new Color(100, 255, 100));
            bot_y.setBackground(new Color(255, 100, 100));
        }
        else{
            Info.znaky[0] = 'O';
            Info.znaky[1] = 'X';
            bot_x.setBackground(new Color(255, 100, 100));
            bot_y.setBackground(new Color(100, 255, 100));
        }
    }

    private void zacatekHry(){
        if(menu.isVisible()){
            hrat.setVisible(false);
            hrat.setEnabled(false);
            menu.setVisible(false);
            naplneniPlochy();

            if(Info.hra_s_botem){
                if(Info.znaky[0] == 'O')
                    Bot.zacinaHru(this);
            }
        }
    }    

    private void naplneniPlochy(){
        plocha = new Policko[Info.vyska][Info.sirka];
        int sirka, vyska;
        if(Info.sirka % 2 == 0)
            sirka = SIRKA / 2 - (Info.sirka / 2) * 52 - 5;
        else
            sirka = (SIRKA / 2 - 26) - (Info.sirka / 2) * 52 - 5;

        if(Info.vyska % 2 == 0)
            vyska = VYSKA / 2 - (Info.vyska / 2) * 52 - 15;
        else
            vyska = (VYSKA / 2 - 26) - (Info.vyska / 2)  * 52 - 15;


        int puvodni_sirka = sirka;
        for(int y = 0; y < Info.vyska; y++){
            for(int x = 0; x < Info.sirka; x++){
                plocha[y][x] = new Policko();
                plocha[y][x].zalozeni(sirka, vyska, 50, 50, y, x);
                final int Y = y;
                final int X = x;
                plocha[y][x].getTlacitko().addActionListener(e -> plocha[Y][X].click(this));
                okno.add(plocha[y][x].getTlacitko());
                sirka += 52;
            }
            vyska += 52;
            sirka = puvodni_sirka;
        }

        Info.plocha = new char[Info.vyska][Info.sirka];
        for(int y = 0; y < Info.vyska; y++){
            for(int x = 0; x < Info.sirka; x++){
                Info.plocha[y][x] = ' ';
            }
        }
    }

    public void setPolicko(int x, int y, String s){
        plocha[y][x].setText(s);
        plocha[y][x].setEnabled(false);
    }

    public void quit(){
        if(Info.dohrano){
            for(int i = 0; i < Info.vyska; i++){
                for(int j = 0; j < Info.sirka; j++){
                    plocha[i][j].setEnabled(false);
                }
            }
        }
    }
}

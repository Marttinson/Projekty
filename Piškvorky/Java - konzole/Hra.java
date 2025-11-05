public class Hra {
    private boolean hra_s_botem;
    private int pocet_na_vyhru;
    private char[] znaky;
    private int pocet_kol;
    private boolean bot_vyhral;
    
    private Hraci_plocha hraci_plocha;

    Hra(){
        znaky = new char[2];
        znaky[0] = 'X';
        znaky[1] = 'O';
        pocet_kol = 0;
        bot_vyhral = false;

        hraci_plocha = new Hraci_plocha();
    }

    public void hrej(){
        zalozeni();
        if(hra_s_botem){
            if(znaky[0] == 'O'){
                hraci_plocha = Bot.zacinaHru(hraci_plocha);
            }

            while(!hraci_plocha.getDohrano()){
                //Když začíná bod, tak počet kol je ve skutečnosti o jedno větší než v proměnné, 
                //ale je to jednodušší kvůli podmínkám
                if(pocet_kol % 2 == 0){
                    hraci_plocha.vypisHraciPlochy();

                    interakceBot();
                }
                else{
                    //botovo kolo
                    if(pocet_kol == 1 && znaky[0] == 'X')
                        hraci_plocha = Bot.nezacinaHru(hraci_plocha);
                    else{
                        hraci_plocha = Bot.hraje(hraci_plocha, znaky, pocet_na_vyhru);

                        kontrolaVyhryBota();
                    }
                }

                if(pocet_kol + 1 == hraci_plocha.getSirka() * hraci_plocha.getVyska()){
                    System.out.println("Remíza");
                    break;
                }

                pocet_kol++;
            }
        }
        else{
            while(!hraci_plocha.getDohrano()){
                hraci_plocha.vypisHraciPlochy();

                interakce();

                if(pocet_kol + 1 == hraci_plocha.getSirka() * hraci_plocha.getVyska()){
                    System.out.println("Remíza");
                    break;
                }
                
                pocet_kol++;
            }
        }
        
        hraci_plocha.vypisHraciPlochy();
        if(bot_vyhral)
            System.out.println("Bot si tě namazal na chleba");

        System.out.println("Díky za hru.");
    }

    private void zalozeni(){
        System.out.println("Vítej ve hře piškvorky");

        int[] souradky = Komunikace.zalozeniPlochy();
        hraci_plocha.zalozeniPlochy(souradky[1], souradky[0]);

        hra_s_botem = Komunikace.volbaHry();

        if(hra_s_botem){
            znaky[0] = Komunikace.volbaZnaku();
            if(znaky[0] == 'O')
                znaky[1] = 'X';
        }

        if(hraci_plocha.getSirka() != 3 && hraci_plocha.getVyska() != 3)
            pocet_na_vyhru = Komunikace.volbaPoctu(hraci_plocha.getSirka(), hraci_plocha.getVyska());
        else
            pocet_na_vyhru = 3;
    }

    private void interakce(){
        System.out.println("Na řadě je hráč s " + znaky[pocet_kol % 2]);

        hraci_plocha = Komunikace.volbaSouradnic(hraci_plocha, znaky[pocet_kol % 2], pocet_na_vyhru);
    }

    private void interakceBot(){
        System.out.println("Hráči si na řadě, máš " + znaky[0]);

        hraci_plocha = Komunikace.volbaSouradnicBot(hraci_plocha, znaky[0], pocet_na_vyhru);
    }

    private void kontrolaVyhryBota(){
        for(int y = 0; y < hraci_plocha.getVyska(); y++){
            for(int x = 0; x < hraci_plocha.getSirka(); x++){
                hraci_plocha.setDohrano(Piskvorky.kontrolaVyhry(hraci_plocha, znaky[1], pocet_na_vyhru, x, y));
                
                if(hraci_plocha.getDohrano())
                    break;
            }
            if(hraci_plocha.getDohrano()){
                bot_vyhral = true;
                break;
            }
        }
    }
}

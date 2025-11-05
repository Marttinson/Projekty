import javax.swing.JButton;
import java.awt.Color;
import java.awt.Font;

public class Policko {
    private JButton tlacitko = new JButton();
    private int x;
    private int y;

    public void zalozeni(int x, int y, int width, int height, int i, int j){
        tlacitko.setBounds(x, y, width, height);
        tlacitko.setBackground(new Color(100, 100, 100));
        tlacitko.setFocusable(false);
        tlacitko.setFont(new Font("MV boli", Font.BOLD, 22));   
        tlacitko.setBorder(null);     
        this.x = j;
        this.y = i;
    }

    public void click(Okno okno){
        if(Info.hra_s_botem){
            if(Info.znaky[0] == 'X'){
                tlacitko.setText("X");
                Info.plocha[y][x] = 'X';
                Info.dohrano = Piskvorky.kontrolaVyhry('X', x, y);

                if(Info.pocet_kol == 0)
                    Bot.nezacinaHru(okno);
                else if(!Info.dohrano)
                    Bot.hraje(okno);
            }
            else{
                tlacitko.setText("O");
                Info.plocha[y][x] = 'O';
                Info.dohrano = Piskvorky.kontrolaVyhry('O', x, y);

                if(!Info.dohrano)
                    Bot.hraje(okno);
            }
        }
        else{
            if(Info.pocet_kol % 2 == 0){
                tlacitko.setText("X");
                Info.plocha[y][x] = 'X';
                Info.dohrano = Piskvorky.kontrolaVyhry('X', x, y);
            }
            else{
                tlacitko.setText("O");
                Info.plocha[y][x] = 'O';
                Info.dohrano = Piskvorky.kontrolaVyhry('O', x, y);
            }
        }

        if(Info.dohrano)
            okno.quit();
        tlacitko.setEnabled(false);
        Info.pocet_kol++;
    }

    public void setText(String s){
        tlacitko.setText(s);
    }

    public void setEnabled(boolean b){
        tlacitko.setEnabled(b);
    }

    public JButton gettlacitko(){
        return tlacitko;
    }

    public JButton getTlacitko(){
        return tlacitko;
    }
}

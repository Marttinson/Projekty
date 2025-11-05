-- uart_rx_fsm.vhd: UART controller - finite state machine controlling RX side
-- Author(s): Martin Rybnikář (xrybni10)

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;



entity UART_RX_FSM is
    port(
       CLK : in std_logic;
       RST : in std_logic;
       DIN : in std_logic;
       CNT : in std_logic_vector(3 downto 0);
       DOUT : out std_logic;
       DEC : out std_logic_vector(2 downto 0);
       D_VALID : out std_logic;
       CNT_EN : out std_logic;
       CNT_RST : out std_logic;
       WAITING : out std_logic
    );
end entity;



architecture behavioral of UART_RX_FSM is
    type t_state is (IDLE, START_BIT, WAITT, DOUT0, DOUT0_WAIT, DOUT1, DOUT1_WAIT, DOUT2, DOUT2_WAIT, DOUT3, DOUT3_WAIT, DOUT4, DOUT4_WAIT, DOUT5, DOUT5_WAIT, DOUT6, DOUT6_WAIT, DOUT7, DOUT7_WAIT, VALID, STOP_BIT);
    signal state : t_state;
    signal next_state : t_state;
    signal prev_state : t_state;

begin

    -- Present state register
    state_register: process(CLK)
    begin
        if rising_edge(CLK) then
            if RST = '1' then
                state <= IDLE;
            else
                state <= next_state;
            end if;
        end if;
    end process;

    -- Next state combinatorial logic
    next_state_logic: process(state, CNT, DIN)
    begin
        next_state <= state; -- default behaviour, FSM stay in the same state
        case state is
            when IDLE =>
                if DIN = '0' then
                    next_state <= START_BIT;
                end if;
            when START_BIT =>
                if CNT = "1111" then
                    next_state <= WAITT;
                end if;
            when WAITT =>
                if CNT = "0110" then
                    next_state <= DOUT0;
                end if;
            when DOUT0 =>
                next_state <= DOUT0_WAIT;
            when DOUT0_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT1;
                end if;
            when DOUT1 =>
                next_state <= DOUT1_WAIT;
            when DOUT1_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT2;
                end if;
            when DOUT2 =>
                next_state <= DOUT2_WAIT;
            when DOUT2_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT3;
                end if;
            when DOUT3 =>
                next_state <= DOUT3_WAIT;
            when DOUT3_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT4;
                end if;
            when DOUT4 =>
                next_state <= DOUT4_WAIT;
            when DOUT4_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT5;
                end if;
            when DOUT5 =>
                next_state <= DOUT5_WAIT;
            when DOUT5_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT6;
                end if;
            when DOUT6 =>
                next_state <= DOUT6_WAIT;
            when DOUT6_WAIT =>
                if CNT = "1110" then
                    next_state <= DOUT7;
                end if;
            when DOUT7 =>
                next_state <= DOUT7_WAIT;
            when DOUT7_WAIT =>
                if CNT = "1110" then
                    next_state <= VALID;
                end if;
            when VALID =>
                next_state <= STOP_BIT;
            when STOP_BIT =>
                if CNT = "1110" then
                    next_state <= IDLE;
                end if;
        end case;
    end process;

    -- Output combinatorial logic
    output_logic: process(state)
    begin
        CNT_RST <= '0'; -- default output values
        CNT_EN <= '1';
        DOUT <= '0';
        DEC <= "000";
        D_VALID <= '0';
        WAITING <= '0';

        case state is
            when IDLE =>
                CNT_RST <= '1';
                CNT_EN <= '0';
            when WAITT =>
                WAITING <= '1';
            when DOUT0 =>
                DOUT <= '1';
                DEC <= "000";
            when DOUT1 =>
                DOUT <= '1';
                DEC <= "001";
            when DOUT2 =>
                DOUT <= '1';
                DEC <= "010";
            when DOUT3 =>
                DOUT <= '1';
                DEC <= "011";
            when DOUT4 =>
                DOUT <= '1';
                DEC <= "100";
            when DOUT5 =>
                DOUT <= '1';
                DEC <= "101";
            when DOUT6 =>
                DOUT <= '1';
                DEC <= "110";
            when DOUT7 =>
                DOUT <= '1';
                DEC <= "111";
            when VALID =>
                D_VALID <= '1';
            when others =>
        end case;
    end process;

end architecture;

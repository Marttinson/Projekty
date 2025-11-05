-- uart_rx.vhd: UART controller - receiving (RX) side
-- Author(s): Martin Rybnikář (xrybni10)

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;



-- Entity declaration (DO NOT ALTER THIS PART!)
entity UART_RX is
    port(
        CLK      : in std_logic;
        RST      : in std_logic;
        DIN      : in std_logic;
        DOUT     : out std_logic_vector(7 downto 0);
        DOUT_VLD : out std_logic := '0'
    );
end entity;



-- Architecture implementation (INSERT YOUR IMPLEMENTATION HERE)
architecture behavioral of UART_RX is
    signal din_reg : std_logic;
    signal din_reg_ce : std_logic;
    signal cmp_eq : std_logic;
    signal cnt_en : std_logic;
    signal cnt_rst : std_logic;
    signal cnt_val : std_logic_vector(3 downto 0);
    signal dec_en : std_logic;
    signal dec_sel : std_logic_vector(2 downto 0);
    signal dec_res : std_logic;
    signal register_enable : std_logic_vector(7 downto 0);
    signal waiting : std_logic;

begin

    -- Input data register
    din_register: process(CLK)
    begin
        if rising_edge(CLK) then
            if din_reg_ce = '1' then
                din_reg <= DIN;
            end if;
        end if;
    end process;

    -- AND gate
    din_reg_ce <= cmp_eq AND cnt_en;

    -- Compare if counter is equal to zero
    cmp: process(cnt_val)
    begin
        if rising_edge(CLK) then
            if cnt_val = "0000" then
                cmp_eq <= '1';
            else
                cmp_eq <= '0';
            end if;
        end if;
    end process;

    -- Counters&comparators for clock cycles and data bits
    counter: process(CLK)
    begin
        if rising_edge(CLK) then
            if cnt_en = '1' then
                cnt_val <= cnt_val + 1;
            else
                cnt_val <= (others => '0');
            end if;

            if cnt_val = "0110" and waiting = '1' then
                cnt_val <= "0000";
            end if;
        end if;
    end process;
    
    -- Decoder for enable output registers
    decoder: process (dec_en, dec_sel)
    begin
        register_enable <= (others => '0');

        if dec_en = '1' then
            case dec_sel is
                when "000" =>
                    register_enable(0) <= '1';
                when "001" =>
                    register_enable(1) <= '1';
                when "010" =>
                    register_enable(2) <= '1';
                when "011" =>
                    register_enable(3) <= '1';
                when "100" =>
                    register_enable(4) <= '1';
                when "101" =>
                    register_enable(5) <= '1';
                when "110" =>
                    register_enable(6) <= '1';
                when "111" =>
                    register_enable(7) <= '1';
                when others =>
                    dec_res <= '0';
            end case;
        end if;
    end process;

    DOUT_registers: process(CLK)
    begin
        if rising_edge(CLK) then
            for i in 0 to 7 loop
                if register_enable(i) = '1' then
                    DOUT(i) <= DIN;
                end if;
            end loop;
        end if;
    end process;

    -- Instance of RX FSM
    fsm: entity work.UART_RX_FSM
    port map (
        CLK => CLK,
        RST => RST,
        DIN => DIN,
        CNT => cnt_val,
        DOUT => dec_en,
        DEC => dec_sel,
        D_VALID => DOUT_VLD,
        CNT_EN => cnt_en,
        CNT_RST => cnt_rst,
        WAITING => waiting
    );

end architecture;
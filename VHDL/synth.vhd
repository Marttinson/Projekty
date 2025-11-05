library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
entity UART_RX is
  port (
    CLK: in std_logic;
    RST: in std_logic;
    DIN: in std_logic;
    DOUT: out std_logic_vector (7 downto 0);
    DOUT_VLD: out std_logic := '0'
  );
end entity;
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity uart_rx_fsm is
  port (
    clk : in std_logic;
    rst : in std_logic;
    din : in std_logic;
    cnt : in std_logic_vector (3 downto 0);
    dout : out std_logic;
    dec : out std_logic_vector (2 downto 0);
    d_valid : out std_logic;
    cnt_en : out std_logic;
    cnt_rst : out std_logic;
    waiting : out std_logic);
end entity uart_rx_fsm;

architecture rtl of uart_rx_fsm is
  signal state : std_logic_vector (4 downto 0);
  signal next_state : std_logic_vector (4 downto 0);
  signal n129_o : std_logic;
  signal n131_o : std_logic_vector (4 downto 0);
  signal n134_q : std_logic_vector (4 downto 0);
  signal n136_o : std_logic;
  signal n138_o : std_logic_vector (4 downto 0);
  signal n140_o : std_logic;
  signal n142_o : std_logic;
  signal n144_o : std_logic_vector (4 downto 0);
  signal n146_o : std_logic;
  signal n148_o : std_logic;
  signal n150_o : std_logic_vector (4 downto 0);
  signal n152_o : std_logic;
  signal n154_o : std_logic;
  signal n156_o : std_logic;
  signal n158_o : std_logic_vector (4 downto 0);
  signal n160_o : std_logic;
  signal n162_o : std_logic;
  signal n164_o : std_logic;
  signal n166_o : std_logic_vector (4 downto 0);
  signal n168_o : std_logic;
  signal n170_o : std_logic;
  signal n172_o : std_logic;
  signal n174_o : std_logic_vector (4 downto 0);
  signal n176_o : std_logic;
  signal n178_o : std_logic;
  signal n180_o : std_logic;
  signal n182_o : std_logic_vector (4 downto 0);
  signal n184_o : std_logic;
  signal n186_o : std_logic;
  signal n188_o : std_logic;
  signal n190_o : std_logic_vector (4 downto 0);
  signal n192_o : std_logic;
  signal n194_o : std_logic;
  signal n196_o : std_logic;
  signal n198_o : std_logic_vector (4 downto 0);
  signal n200_o : std_logic;
  signal n202_o : std_logic;
  signal n204_o : std_logic;
  signal n206_o : std_logic_vector (4 downto 0);
  signal n208_o : std_logic;
  signal n210_o : std_logic;
  signal n212_o : std_logic;
  signal n214_o : std_logic_vector (4 downto 0);
  signal n216_o : std_logic;
  signal n218_o : std_logic;
  signal n220_o : std_logic;
  signal n222_o : std_logic_vector (4 downto 0);
  signal n224_o : std_logic;
  signal n225_o : std_logic_vector (20 downto 0);
  signal n236_o : std_logic_vector (4 downto 0);
  signal n240_o : std_logic;
  signal n242_o : std_logic;
  signal n244_o : std_logic;
  signal n246_o : std_logic;
  signal n248_o : std_logic;
  signal n250_o : std_logic;
  signal n252_o : std_logic;
  signal n254_o : std_logic;
  signal n256_o : std_logic;
  signal n258_o : std_logic;
  signal n260_o : std_logic;
  signal n261_o : std_logic_vector (10 downto 0);
  signal n271_o : std_logic;
  signal n282_o : std_logic_vector (2 downto 0);
  signal n286_o : std_logic;
  signal n290_o : std_logic;
  signal n294_o : std_logic;
  signal n298_o : std_logic;
begin
  dout <= n271_o;
  dec <= n282_o;
  d_valid <= n286_o;
  cnt_en <= n290_o;
  cnt_rst <= n294_o;
  waiting <= n298_o;
  -- uart_rx_fsm.vhd:29:12
  state <= n134_q; -- (signal)
  -- uart_rx_fsm.vhd:30:12
  next_state <= n236_o; -- (signal)
  -- uart_rx_fsm.vhd:38:12
  n129_o <= '1' when rising_edge (clk) else '0';
  -- uart_rx_fsm.vhd:39:13
  n131_o <= next_state when rst = '0' else "00000";
  -- uart_rx_fsm.vhd:38:9
  process (clk)
  begin
    if rising_edge (clk) then
      n134_q <= n131_o;
    end if;
  end process;
  -- uart_rx_fsm.vhd:53:24
  n136_o <= not din;
  -- uart_rx_fsm.vhd:53:17
  n138_o <= state when n136_o = '0' else "00001";
  -- uart_rx_fsm.vhd:52:13
  n140_o <= '1' when state = "00000" else '0';
  -- uart_rx_fsm.vhd:57:24
  n142_o <= '1' when cnt = "1111" else '0';
  -- uart_rx_fsm.vhd:57:17
  n144_o <= state when n142_o = '0' else "00010";
  -- uart_rx_fsm.vhd:56:13
  n146_o <= '1' when state = "00001" else '0';
  -- uart_rx_fsm.vhd:61:24
  n148_o <= '1' when cnt = "0110" else '0';
  -- uart_rx_fsm.vhd:61:17
  n150_o <= state when n148_o = '0' else "00011";
  -- uart_rx_fsm.vhd:60:13
  n152_o <= '1' when state = "00010" else '0';
  -- uart_rx_fsm.vhd:64:13
  n154_o <= '1' when state = "00011" else '0';
  -- uart_rx_fsm.vhd:67:24
  n156_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:67:17
  n158_o <= state when n156_o = '0' else "00101";
  -- uart_rx_fsm.vhd:66:13
  n160_o <= '1' when state = "00100" else '0';
  -- uart_rx_fsm.vhd:70:13
  n162_o <= '1' when state = "00101" else '0';
  -- uart_rx_fsm.vhd:73:24
  n164_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:73:17
  n166_o <= state when n164_o = '0' else "00111";
  -- uart_rx_fsm.vhd:72:13
  n168_o <= '1' when state = "00110" else '0';
  -- uart_rx_fsm.vhd:76:13
  n170_o <= '1' when state = "00111" else '0';
  -- uart_rx_fsm.vhd:79:24
  n172_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:79:17
  n174_o <= state when n172_o = '0' else "01001";
  -- uart_rx_fsm.vhd:78:13
  n176_o <= '1' when state = "01000" else '0';
  -- uart_rx_fsm.vhd:82:13
  n178_o <= '1' when state = "01001" else '0';
  -- uart_rx_fsm.vhd:85:24
  n180_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:85:17
  n182_o <= state when n180_o = '0' else "01011";
  -- uart_rx_fsm.vhd:84:13
  n184_o <= '1' when state = "01010" else '0';
  -- uart_rx_fsm.vhd:88:13
  n186_o <= '1' when state = "01011" else '0';
  -- uart_rx_fsm.vhd:91:24
  n188_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:91:17
  n190_o <= state when n188_o = '0' else "01101";
  -- uart_rx_fsm.vhd:90:13
  n192_o <= '1' when state = "01100" else '0';
  -- uart_rx_fsm.vhd:94:13
  n194_o <= '1' when state = "01101" else '0';
  -- uart_rx_fsm.vhd:97:24
  n196_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:97:17
  n198_o <= state when n196_o = '0' else "01111";
  -- uart_rx_fsm.vhd:96:13
  n200_o <= '1' when state = "01110" else '0';
  -- uart_rx_fsm.vhd:100:13
  n202_o <= '1' when state = "01111" else '0';
  -- uart_rx_fsm.vhd:103:24
  n204_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:103:17
  n206_o <= state when n204_o = '0' else "10001";
  -- uart_rx_fsm.vhd:102:13
  n208_o <= '1' when state = "10000" else '0';
  -- uart_rx_fsm.vhd:106:13
  n210_o <= '1' when state = "10001" else '0';
  -- uart_rx_fsm.vhd:109:24
  n212_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:109:17
  n214_o <= state when n212_o = '0' else "10011";
  -- uart_rx_fsm.vhd:108:13
  n216_o <= '1' when state = "10010" else '0';
  -- uart_rx_fsm.vhd:112:13
  n218_o <= '1' when state = "10011" else '0';
  -- uart_rx_fsm.vhd:115:24
  n220_o <= '1' when cnt = "1110" else '0';
  -- uart_rx_fsm.vhd:115:17
  n222_o <= state when n220_o = '0' else "00000";
  -- uart_rx_fsm.vhd:114:13
  n224_o <= '1' when state = "10100" else '0';
  n225_o <= n224_o & n218_o & n216_o & n210_o & n208_o & n202_o & n200_o & n194_o & n192_o & n186_o & n184_o & n178_o & n176_o & n170_o & n168_o & n162_o & n160_o & n154_o & n152_o & n146_o & n140_o;
  -- uart_rx_fsm.vhd:51:9
  with n225_o select n236_o <=
    n222_o when "100000000000000000000",
    "10100" when "010000000000000000000",
    n214_o when "001000000000000000000",
    "10010" when "000100000000000000000",
    n206_o when "000010000000000000000",
    "10000" when "000001000000000000000",
    n198_o when "000000100000000000000",
    "01110" when "000000010000000000000",
    n190_o when "000000001000000000000",
    "01100" when "000000000100000000000",
    n182_o when "000000000010000000000",
    "01010" when "000000000001000000000",
    n174_o when "000000000000100000000",
    "01000" when "000000000000010000000",
    n166_o when "000000000000001000000",
    "00110" when "000000000000000100000",
    n158_o when "000000000000000010000",
    "00100" when "000000000000000001000",
    n150_o when "000000000000000000100",
    n144_o when "000000000000000000010",
    n138_o when "000000000000000000001",
    "XXXXX" when others;
  -- uart_rx_fsm.vhd:132:13
  n240_o <= '1' when state = "00000" else '0';
  -- uart_rx_fsm.vhd:135:13
  n242_o <= '1' when state = "00010" else '0';
  -- uart_rx_fsm.vhd:137:13
  n244_o <= '1' when state = "00011" else '0';
  -- uart_rx_fsm.vhd:140:13
  n246_o <= '1' when state = "00101" else '0';
  -- uart_rx_fsm.vhd:143:13
  n248_o <= '1' when state = "00111" else '0';
  -- uart_rx_fsm.vhd:146:13
  n250_o <= '1' when state = "01001" else '0';
  -- uart_rx_fsm.vhd:149:13
  n252_o <= '1' when state = "01011" else '0';
  -- uart_rx_fsm.vhd:152:13
  n254_o <= '1' when state = "01101" else '0';
  -- uart_rx_fsm.vhd:155:13
  n256_o <= '1' when state = "01111" else '0';
  -- uart_rx_fsm.vhd:158:13
  n258_o <= '1' when state = "10001" else '0';
  -- uart_rx_fsm.vhd:161:13
  n260_o <= '1' when state = "10011" else '0';
  n261_o <= n260_o & n258_o & n256_o & n254_o & n252_o & n250_o & n248_o & n246_o & n244_o & n242_o & n240_o;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n271_o <=
    '0' when "10000000000",
    '1' when "01000000000",
    '1' when "00100000000",
    '1' when "00010000000",
    '1' when "00001000000",
    '1' when "00000100000",
    '1' when "00000010000",
    '1' when "00000001000",
    '1' when "00000000100",
    '0' when "00000000010",
    '0' when "00000000001",
    '0' when others;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n282_o <=
    "000" when "10000000000",
    "111" when "01000000000",
    "110" when "00100000000",
    "101" when "00010000000",
    "100" when "00001000000",
    "011" when "00000100000",
    "010" when "00000010000",
    "001" when "00000001000",
    "000" when "00000000100",
    "000" when "00000000010",
    "000" when "00000000001",
    "000" when others;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n286_o <=
    '1' when "10000000000",
    '0' when "01000000000",
    '0' when "00100000000",
    '0' when "00010000000",
    '0' when "00001000000",
    '0' when "00000100000",
    '0' when "00000010000",
    '0' when "00000001000",
    '0' when "00000000100",
    '0' when "00000000010",
    '0' when "00000000001",
    '0' when others;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n290_o <=
    '1' when "10000000000",
    '1' when "01000000000",
    '1' when "00100000000",
    '1' when "00010000000",
    '1' when "00001000000",
    '1' when "00000100000",
    '1' when "00000010000",
    '1' when "00000001000",
    '1' when "00000000100",
    '1' when "00000000010",
    '0' when "00000000001",
    '1' when others;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n294_o <=
    '0' when "10000000000",
    '0' when "01000000000",
    '0' when "00100000000",
    '0' when "00010000000",
    '0' when "00001000000",
    '0' when "00000100000",
    '0' when "00000010000",
    '0' when "00000001000",
    '0' when "00000000100",
    '0' when "00000000010",
    '1' when "00000000001",
    '0' when others;
  -- uart_rx_fsm.vhd:131:9
  with n261_o select n298_o <=
    '0' when "10000000000",
    '0' when "01000000000",
    '0' when "00100000000",
    '0' when "00010000000",
    '0' when "00001000000",
    '0' when "00000100000",
    '0' when "00000010000",
    '0' when "00000001000",
    '0' when "00000000100",
    '1' when "00000000010",
    '0' when "00000000001",
    '0' when others;
end rtl;


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

architecture rtl of uart_rx is
  signal wrap_CLK: std_logic;
  signal wrap_RST: std_logic;
  signal wrap_DIN: std_logic;
  subtype typwrap_DOUT is std_logic_vector (7 downto 0);
  signal wrap_DOUT: typwrap_DOUT;
  signal wrap_DOUT_VLD: std_logic;
  signal cnt_en : std_logic;
  signal cnt_val : std_logic_vector (3 downto 0);
  signal dec_en : std_logic;
  signal dec_sel : std_logic_vector (2 downto 0);
  signal register_enable : std_logic_vector (7 downto 0);
  signal waiting : std_logic;
  signal n22_o : std_logic;
  signal n24_o : std_logic_vector (3 downto 0);
  signal n26_o : std_logic_vector (3 downto 0);
  signal n28_o : std_logic;
  signal n29_o : std_logic;
  signal n31_o : std_logic_vector (3 downto 0);
  signal n34_q : std_logic_vector (3 downto 0);
  signal n38_o : std_logic;
  signal n41_o : std_logic;
  signal n44_o : std_logic;
  signal n47_o : std_logic;
  signal n50_o : std_logic;
  signal n53_o : std_logic;
  signal n56_o : std_logic;
  signal n59_o : std_logic;
  signal n60_o : std_logic_vector (7 downto 0);
  signal n64_o : std_logic;
  signal n66_o : std_logic;
  signal n68_o : std_logic;
  signal n70_o : std_logic;
  signal n72_o : std_logic;
  signal n74_o : std_logic;
  signal n76_o : std_logic;
  signal n78_o : std_logic;
  signal n80_o : std_logic_vector (7 downto 0);
  signal n82_o : std_logic_vector (7 downto 0);
  signal n87_o : std_logic;
  signal n88_o : std_logic;
  signal n89_o : std_logic;
  signal n90_o : std_logic;
  signal n91_o : std_logic;
  signal n92_o : std_logic;
  signal n93_o : std_logic;
  signal n94_o : std_logic;
  signal n95_o : std_logic;
  signal n96_o : std_logic;
  signal n97_o : std_logic;
  signal n98_o : std_logic;
  signal n99_o : std_logic;
  signal n100_o : std_logic;
  signal n101_o : std_logic;
  signal n102_o : std_logic;
  signal n103_o : std_logic;
  signal n104_o : std_logic;
  signal n105_o : std_logic;
  signal n106_o : std_logic;
  signal n107_o : std_logic;
  signal n108_o : std_logic;
  signal n109_o : std_logic;
  signal n110_o : std_logic;
  signal n111_o : std_logic;
  signal n112_o : std_logic_vector (7 downto 0);
  signal n115_q : std_logic_vector (7 downto 0);
  signal fsm_dout : std_logic;
  signal fsm_dec : std_logic_vector (2 downto 0);
  signal fsm_d_valid : std_logic;
  signal fsm_cnt_en : std_logic;
  signal fsm_cnt_rst : std_logic;
  signal fsm_waiting : std_logic;
begin
  wrap_clk <= clk;
  wrap_rst <= rst;
  wrap_din <= din;
  dout <= wrap_dout;
  dout_vld <= wrap_dout_vld;
  wrap_DOUT <= n115_q;
  wrap_DOUT_VLD <= fsm_d_valid;
  -- uart_rx.vhd:28:12
  cnt_en <= fsm_cnt_en; -- (signal)
  -- uart_rx.vhd:30:12
  cnt_val <= n34_q; -- (signal)
  -- uart_rx.vhd:31:12
  dec_en <= fsm_dout; -- (signal)
  -- uart_rx.vhd:32:12
  dec_sel <= fsm_dec; -- (signal)
  -- uart_rx.vhd:34:12
  register_enable <= n82_o; -- (signal)
  -- uart_rx.vhd:35:12
  waiting <= fsm_waiting; -- (signal)
  -- uart_rx.vhd:67:12
  n22_o <= '1' when rising_edge (wrap_CLK) else '0';
  -- uart_rx.vhd:69:36
  n24_o <= std_logic_vector (unsigned (cnt_val) + unsigned'("0001"));
  -- uart_rx.vhd:68:13
  n26_o <= "0000" when cnt_en = '0' else n24_o;
  -- uart_rx.vhd:74:24
  n28_o <= '1' when cnt_val = "0110" else '0';
  -- uart_rx.vhd:74:33
  n29_o <= n28_o and waiting;
  -- uart_rx.vhd:74:13
  n31_o <= n26_o when n29_o = '0' else "0000";
  -- uart_rx.vhd:67:9
  process (wrap_CLK)
  begin
    if rising_edge (wrap_CLK) then
      n34_q <= n31_o;
    end if;
  end process;
  -- uart_rx.vhd:87:17
  n38_o <= '1' when dec_sel = "000" else '0';
  -- uart_rx.vhd:89:17
  n41_o <= '1' when dec_sel = "001" else '0';
  -- uart_rx.vhd:91:17
  n44_o <= '1' when dec_sel = "010" else '0';
  -- uart_rx.vhd:93:17
  n47_o <= '1' when dec_sel = "011" else '0';
  -- uart_rx.vhd:95:17
  n50_o <= '1' when dec_sel = "100" else '0';
  -- uart_rx.vhd:97:17
  n53_o <= '1' when dec_sel = "101" else '0';
  -- uart_rx.vhd:99:17
  n56_o <= '1' when dec_sel = "110" else '0';
  -- uart_rx.vhd:101:17
  n59_o <= '1' when dec_sel = "111" else '0';
  n60_o <= n59_o & n56_o & n53_o & n50_o & n47_o & n44_o & n41_o & n38_o;
  -- uart_rx.vhd:86:13
  with n60_o select n64_o <=
    '0' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '1' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n66_o <=
    '0' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '1' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n68_o <=
    '0' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '1' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n70_o <=
    '0' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '1' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n72_o <=
    '0' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '1' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n74_o <=
    '0' when "10000000",
    '0' when "01000000",
    '1' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n76_o <=
    '0' when "10000000",
    '1' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  -- uart_rx.vhd:86:13
  with n60_o select n78_o <=
    '1' when "10000000",
    '0' when "01000000",
    '0' when "00100000",
    '0' when "00010000",
    '0' when "00001000",
    '0' when "00000100",
    '0' when "00000010",
    '0' when "00000001",
    '0' when others;
  n80_o <= n78_o & n76_o & n74_o & n72_o & n70_o & n68_o & n66_o & n64_o;
  -- uart_rx.vhd:85:9
  n82_o <= "00000000" when dec_en = '0' else n80_o;
  -- uart_rx.vhd:111:12
  n87_o <= '1' when rising_edge (wrap_CLK) else '0';
  -- uart_rx.vhd:113:35
  n88_o <= register_enable (0);
  n89_o <= n115_q (0);
  -- uart_rx.vhd:113:17
  n90_o <= n89_o when n88_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n91_o <= register_enable (1);
  n92_o <= n115_q (1);
  -- uart_rx.vhd:113:17
  n93_o <= n92_o when n91_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n94_o <= register_enable (2);
  n95_o <= n115_q (2);
  -- uart_rx.vhd:113:17
  n96_o <= n95_o when n94_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n97_o <= register_enable (3);
  n98_o <= n115_q (3);
  -- uart_rx.vhd:113:17
  n99_o <= n98_o when n97_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n100_o <= register_enable (4);
  n101_o <= n115_q (4);
  -- uart_rx.vhd:113:17
  n102_o <= n101_o when n100_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n103_o <= register_enable (5);
  n104_o <= n115_q (5);
  -- uart_rx.vhd:113:17
  n105_o <= n104_o when n103_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n106_o <= register_enable (6);
  n107_o <= n115_q (6);
  -- uart_rx.vhd:113:17
  n108_o <= n107_o when n106_o = '0' else wrap_DIN;
  -- uart_rx.vhd:113:35
  n109_o <= register_enable (7);
  n110_o <= n115_q (7);
  -- uart_rx.vhd:113:17
  n111_o <= n110_o when n109_o = '0' else wrap_DIN;
  n112_o <= n111_o & n108_o & n105_o & n102_o & n99_o & n96_o & n93_o & n90_o;
  -- uart_rx.vhd:111:9
  process (wrap_CLK)
  begin
    if rising_edge (wrap_CLK) then
      n115_q <= n112_o;
    end if;
  end process;
  -- uart_rx.vhd:121:5
  fsm : entity work.uart_rx_fsm port map (
    clk => wrap_CLK,
    rst => wrap_RST,
    din => wrap_DIN,
    cnt => cnt_val,
    dout => fsm_dout,
    dec => fsm_dec,
    d_valid => fsm_d_valid,
    cnt_en => fsm_cnt_en,
    cnt_rst => open,
    waiting => fsm_waiting);
end rtl;

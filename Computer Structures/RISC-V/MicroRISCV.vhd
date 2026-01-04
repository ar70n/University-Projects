----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores
-- Fichero: MicroRISCV.vhd
-- Descripción: Diseño del microprocesador RISC-V
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity MicroRISCV is	port (
	Clk : in std_logic; -- Reloj
	NRst : in std_logic; -- Reset activo a nivel bajo
	MemProgAddr : out unsigned(31 downto 0); -- Dirección para la memoria de programa
	MemProgData : in unsigned(31 downto 0); -- Código de operación
	MemDataAddr : out unsigned(31 downto 0); -- Dirección para la memoria de datos
	MemDataDataRead : in signed(31 downto 0); -- Dato a leer en la memoria de datos
	MemDataDataWrite : out signed(31 downto 0); -- Dato a guardar en la memoria de datos
	MemDataWE : out std_logic
	);
end MicroRISCV;
 
architecture Practica4 OF MicroRISCV is

  component UnidadControl is
    port(
		Op : in  std_logic_vector (6 downto 0); -- Op de la instrucción
		Funct3 : in std_logic_vector(2 downto 0); -- Funct3 de la instrucción
		Funct7_5 : in std_logic; -- Bit 5 de Funct7_5 de la instrucción
		
		-- Señales para el PC
		Zero : in std_logic;
		PCSrc : out  std_logic;
		Jalr : out std_logic;
		
		-- Señales para la memoria
		ResultSrc : out std_logic_vector(1 downto 0);
		MemWrite : out std_logic;
		
		-- Señales para la ALU
		ALUControl : out std_logic_vector (2 downto 0);
		ALUSrc : out std_logic;
		
		ImmSrc : out std_logic_vector(1 downto 0);
		
		-- Señales para el GPR
		RegWrite : out std_logic
        );
  end component;
 
  component RegsRISCV is
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Reset asíncrono a nivel bajo
		A1 : in unsigned(4 downto 0); -- Dirección para el puerto RD1
		RD1 : out signed(31 downto 0); -- Dato del puerto RD1
		A2 : in unsigned(4 downto 0); -- Dirección para el puerto RD2
		RD2 : out signed(31 downto 0); -- Dato del puerto RD2
		A3 : in unsigned(4 downto 0); -- Dirección para el puerto WD3
		WD3 : in signed(31 downto 0); -- Dato de entrada WD3
		WE3 : in std_logic -- Habilitación del banco de registros
	);
  end component;

  component ALURISCV is
    port (
        Op1 : in signed(31 downto 0);
        Op2 : in signed(31 downto 0);
        ALUControl : in std_logic_vector (2 downto 0);
        Res : out signed(31 downto 0);
        Z : out std_logic
    );
  end component;

  signal instr_sig, alua, alub, aluc, result : signed(31 downto 0);

  signal ext_signo, auipc : signed(31 downto 0);

  signal pc, pc_target, pc_plus4 : unsigned(31 downto 0);

  signal instr_full : std_logic_vector(31 downto 0);

  signal jalr, mem_write, alusrc, reg_write, z, pcsrc : std_logic;
  signal imm_src, result_src : std_logic_vector(1 downto 0);
  signal alu_control : std_logic_vector(2 downto 0);
  

begin
  instr_full <= std_logic_vector(MemProgData);
  instr_sig <= signed(MemProgData);

  control: UnidadControl port map (
		Op => instr_full(6 downto 0),
		Funct3 => instr_full(14 downto 12),
		Funct7_5 => instr_full(30),
		Zero => z,
		PCSrc => pcsrc,
		Jalr => jalr,
		ResultSrc => result_src,
		MemWrite => mem_write,
                ALUControl => alu_control,
		ALUSrc => alusrc,
		ImmSrc => imm_src,
		RegWrite => reg_write
        );

  GPR: RegsRISCV port map (
		Clk => Clk,
		NRst => NRst,
		A1 => MemProgData(19 downto 15),
		RD1 => alua,
		A2 => MemProgData(24 downto 20),
		RD2 => MemDataDataWrite,
		A3 => MemProgData(11 downto 7),
		WD3 => result,
		WE3 => reg_write
              );

  alu: ALURISCV port map (
        Op1 => alua,
        Op2 => alub,
        ALUControl => alu_control,
        Res => aluc,
        Z => z
      );

  with imm_src select ext_signo <=
    resize(instr_sig(31 downto 31), 20) & instr_sig(31 downto 20) when "00", -- I
    resize(instr_sig(31 downto 31), 20) & instr_sig(31 downto 25) & instr_sig(11 downto 7) when "01", -- S
    resize(instr_sig(31 downto 31), 19) & instr_sig(31) & instr_sig(7) & instr_sig(30 downto 25) & instr_sig(11 downto 8) & '0' when "10", -- B
    resize(instr_sig(31 downto 31), 12) & instr_sig(19 downto 12) & instr_sig(20) & instr_sig(30 downto 21) & '0' when others; -- jal

  alub <= memDataDataWrite when alusrc = '0' else ext_signo;

  with result_src select result <=
    aluc when "00",
    MemDataDataRead when "01",
    signed(pc_plus4) when "10",
    (auipc + signed(pc)) when others;

  auipc <= instr_sig(31 downto 12) & x"000";

  pc_target <= unsigned(signed(pc) + ext_signo);

  memDataAddr <= unsigned(aluc);
  memDataWe <= mem_write;

  process(all)
  begin
    if nRst = '0' then
      pc <= (others => '0');
    elsif rising_edge(clk) then
      pc <= unsigned(aluc) when jalr = '1' else
            pc_target when pcsrc = '1' else
            pc_plus4;
    end if;
  end process;

  pc_plus4 <= pc + 4;
  memProgAddr <= pc;

end Practica4;

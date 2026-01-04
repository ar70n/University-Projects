--------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores
-- Fichero: UnidadControl.vhd
-- Descripción: Unidad de Control para el microprocesador RISC-V
-- Fichero: Práctica: 4. Ejercicio: 2b
----------------------------------------------------------------------
----------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity UnidadControl is port(
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
end UnidadControl;
 
architecture behavior of UnidadControl is
	signal jump, branch : std_logic;
begin
  process(all) 
    begin 
      
    end process;
	
    ResultSrc <= "00" when (Op = "0110011" or Op = "0010011") else
                 "01" when Op = "0000011" else
                 "10" when (Op = "1101111" or Op = "1100111") else
                 "11" when Op = "0010111" else
                 "--";
    MemWrite <= '1' when Op = "0100011" else '0';

    branch <= '1' when Op = "1100011" else '0';

    PCSrc <= jump or (branch and Zero);

    ALUControl <= "000" when (Op = "0000011" or Op = "0100011" or Op = "1100111" or 
                             (Op = "0110011" and Funct3 = "000" and Funct7_5 = '0') or 
                             (Op = "0010011" and Funct3 = "000")) else
                  "001" when (Op = "1100011" or (Op = "0110011" and Funct3 = "000" and Funct7_5 = '1')) else
                  "010" when ((Op = "1100011" and Funct3 = "111") or (Op = "0010011" and Funct3 = "111")) else
                  "011" when ((Op = "1100011" and Funct3 = "110") or (Op = "0010011" and Funct3 = "110")) else
                  "101" when ((Op = "1100011" and Funct3 = "010") or (Op = "0010011" and Funct3 = "010")) else
                  "111" when ((Op = "1100011" and Funct3 = "100") or (Op = "0010011" and Funct3 = "100")) else
                  "---";

    ALUSrc <= '0' when (Op = "1100011" or Op = "0110011") else 
              '-' when (Op = "1101111" or Op = "0010111") else
              '1';

    ImmSrc <= "10" when Op = "1100011" else
              "01" when Op = "0100011" else 
              "11" when Op = "1101111" else 
              "--" when (Op = "0110011" or Op = "0010111") else
              "00";

    RegWrite <= '0' when (Op = "0100011" or Op = "1100011") else
                '1';

    jump <= '1' when Op = "1101111" else '0';

    Jalr <= '1' when Op = "1100111" else '0';


 

	
end behavior;


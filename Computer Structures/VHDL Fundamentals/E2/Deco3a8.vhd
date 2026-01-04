---------------------------------------------------------------------
----------------------------------------------------------------------
-- Fichero: Deco2a4.vhd
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Descripción: Decodificador 2 a 4
-- Fichero de apoyo para: Práctica: 1. Ejercicio: 2
----------------------------------------------------------------------
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;



entity Deco3a8 is
    port ( 
		D1 : in  std_logic_vector (2 downto 0);
		Q1 : out  std_logic_vector (7 downto 0)
	);
end Deco3a8;

architecture Practica of Deco3a8 is

begin

	process (all)
	begin
		case D1 is
			when "000" => Q1 <= "00000001";
			when "001" => Q1 <= "00000010";
			when "010" => Q1 <= "00000100";
			when "011" => Q1 <= "00001000";
			when "100" => Q1 <= "00010000";
			when "101" => Q1 <= "00100000";
			when "110" => Q1 <= "01000000";
			when "111" => Q1 <= "10000000";
			
			
			
			when others => Q1 <= "10000000";
		end case;
	end process;

end Practica;

----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Fichero: MemProgSuma.vhd
-- Descripción: Memoria de programa para el RISC-V. Contiene sumas entre un registro y un dato inmediato
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity MemProgSuma is
	port (
		MemProgAddr : in unsigned(31 downto 0); -- Dirección para la memoria de programa
		MemProgData : out unsigned(31 downto 0) -- Código de operación
	);
end MemProgSuma;

architecture Simple of MemProgSuma is

begin

	LecturaMemProg: process(MemProgAddr)
	begin
		-- La memoria devuelve un valor para cada dirección.
		-- Estos valores son los códigos de programa de cada instrucción,
		-- estando situado cada uno en su dirección.
		case MemProgAddr is
			when X"00000000" => MemProgData <= X"00A00093";		-- R1 = R0 + 10
			when X"00000004" => MemProgData <= X"00508113";		-- R2 = R1 + 5
			when X"00000008" => MemProgData <= X"01910193";		-- R3 = R2 + 25	
			when X"0000000C" => MemProgData <= X"00500013";		-- R0 = R0 + 5
			when X"00000010" => MemProgData <= X"FFB18213";		-- R4 = R3 - 5
			when others => MemProgData <= X"00000000"; 				-- Resto de memoria vacía
		end case;
	end process LecturaMemProg;

end Simple;

---------------------------------------------------------------------
----------------------------------------------------------------------
-- Fichero: Registro.vhd
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Descripción: Registro de 1 bit con Chip Enable
-- Fichero de apoyo para: Práctica: 1. Ejercicio: 2
----------------------------------------------------------------------
----------------------------------------------------------------------


library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;


--Definición de la entidad
--El registro tiene una entrada de datos (D), entrada de Reset, CLK y CE
--Como salida tiene un sólo bit (Q)

entity Registro is
    port ( 
		D2 : in  std_logic_vector(7 downto 0);
		Reset : in  std_logic;
		Clk : in  std_logic;
		Ce : in  std_logic;
		Q2 : out  std_logic_vector(7 downto 0)
	);
end Registro;

architecture Practica of Registro is
	
begin

	--El registro es sensible al Reset (asíncrono) y a la señal del reloj
	process (all)
	begin
		-- Si el reset está activo la salida vale 0
		if Reset = '1' then
			Q2 <=(others => '0');
		-- Si hay un flanco de subida del reloj
		elsif rising_edge (Clk) then
			-- Si el chip enable está activo
			if Ce = '1' then
				Q2 <= D2;
			end if;
		end if;
	end process;

end Practica;

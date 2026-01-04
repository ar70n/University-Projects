----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores.
-- Fichero: MemProgRISCV.vhd
-- Descripción: Memoria de programa para el RISC-V
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 1. Se utiliza en la validación del Ejercicio 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity MemProgRISCV is										
	port (
		MemProgAddr : in unsigned(31 downto 0);        		-- Dirección para la memoria de programa
		MemProgData : out unsigned(31 downto 0) 			-- Instrucción
	);
end MemProgRISCV;											

architecture Simple of MemProgRISCV is	

begin

	-- Proceso para la escritura inicial en la memoria de código o de programa. 
	-- La memoria de programa es de solo lectura, el proceso de escritura es único y se realiza antes de ejecutar la simulación.  
	EscrituraMemProg: process(all)
	begin
		-- La memoria devuelve un valor para cada dirección.
		-- Estos valores son los códigos de programa de cada instrucción, estando situado cada uno en su dirección.
		-- Código para la escritura de los datos iniciales quedeben ser cargados previamente en memoria antes de la ejecución del programa.
		
		-- Se cargan a partir de una dirección dada, en RARS por la directiva .text, que en el ejemplo es 0x00000000.
		-- Como cada instruccción ocupa 4 bytes, las direcciones se incrementan de 4 en 4. 
			
		case MemProgAddr is
-- *********************************************************************
			when x"00000000" => MemProgData <= x"00002097";		-- 
			when x"00000004" => MemProgData <= x"00008093";		-- 
			when x"00000008" => MemProgData <= x"00400113";		-- 
			when x"0000000C" => MemProgData <= x"00f06193";		-- 
			when x"00000010" => MemProgData <= x"0041f213";		-- 
			when x"00000014" => MemProgData <= x"fec20293";		-- 
			when x"00000018" => MemProgData <= x"7ff02313";		-- 
			when x"0000001C" => MemProgData <= x"fff02313"; 	-- 
			when x"00000020" => MemProgData <= x"0022a3b3";		-- 
			when x"00000024" => MemProgData <= x"0000a403";		-- 
			when x"00000028" => MemProgData <= x"0040a483";		-- 
			when x"0000002C" => MemProgData <= x"0080a503";		-- 
			when x"00000030" => MemProgData <= x"408385b3";		-- 
			when x"00000034" => MemProgData <= x"00510463";		-- 
			when x"00000038" => MemProgData <= x"00a48463";		-- 
			when x"0000003C" => MemProgData <= x"000005b3";		-- 
			when x"00000040" => MemProgData <= x"00258613";		-- 
			when x"00000044" => MemProgData <= x"002006b3";		-- 
			when x"00000048" => MemProgData <= x"00d0a623";		-- 
			when x"0000004C" => MemProgData <= x"00c0a703";		-- 
			when x"00000050" => MemProgData <= x"fff14793";		-- 
			when x"00000054" => MemProgData <= x"00e74133";		-- 
                        when x"00000058" => MemProgData <= x"0007f7b3";
                        when x"0000005C" => MemProgData <= x"0041e033";
                        when x"00000060" => MemProgData <= x"01384893";
                        when x"00000064" => MemProgData <= x"00c000ef";
                        when x"00000068" => MemProgData <= x"07400913";
                        when x"0000006C" => MemProgData <= x"00090067";
                        when x"00000070" => MemProgData <= x"00008067";
                        when x"00000074" => MemProgData <= x"0000006f";
			-- Completar el resto de instrucciones
-- *********************************************************************			
			when others => MemProgData <= x"00000000"; -- Resto de memoria vacía
		end case;
	end process EscrituraMemProg;

	
	
end Simple;


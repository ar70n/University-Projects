----------------------------------------------------------------------------------
----------------------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. GII. 1er curso.
-- Fichero: ALURISCV.vhd
-- Descripción: ALU del microprocesador RISC-V
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 2
----------------------------------------------------------------------------------
----------------------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity ALURISCV is
	port(
   		Op1 : in signed(31 downto 0);
		Op2 : in signed(31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out signed(31 downto 0);
		Z : out std_logic
		);
end ALURISCV;

architecture Practica of ALURISCV is

begin



process(all)
	begin
	
	
	if ALUControl="000" then
		res<=Op1+Op2;
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	elsif ALUControl="001" then
		res<=Op1-Op2;
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	
	elsif ALUControl="010" then
		res<=Op1 and Op2;
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	
	elsif ALUControl="011" then
		res<=Op1 or Op2;
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	
	elsif ALUControl="101" then
		
		if Op1<Op2 then
			res<=(31 downto 1 =>'0' , 0=>'1');
		else 
			res<=(others =>'0');
		end if;
		
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	
	elsif ALUControl="111" then
		res<=Op1 xor Op2;
		if res=0 then
			z<='1';
		else 
			z<='0';
		end if;
	else 
		
	end if;
	
	
	
	
end process;



end Practica;

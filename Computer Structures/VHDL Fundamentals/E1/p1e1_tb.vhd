library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity P1e1_tb is
end P1e1_tb;

architecture Practica of P1e1_tb is 
component P1e1

	port(A,B,C:in std_logic;
	Q: out std_logic);
	end component;
	
	signal sigA : std_logic:='0';
	signal sigB : std_logic:='0';
	signal sigC : std_logic:='0';
	signal q : std_logic;
	
	constant ESPERA : time := 10 ns;
	
	begin
	
	uut:P1e1 port map(
		A=>sigA,
		B=>sigB,
		C=>sigC,
		Q=>q
		);
		
	process
	
	begin
	
	sigA<='0'; sigB<='0';sigC<='0';
	wait for ESPERA;
	
	assert q='0'
	report "Error en el caso 000"
	severity failure;
	
	
	sigA<='0'; sigB<='0';sigC<='1';
	wait for ESPERA;
	
	assert q='0'
	report "Error en el caso 001"
	severity failure;
	
	sigA<='0'; sigB<='1';sigC<='0';
	wait for ESPERA;
	
	assert q='0'
	report "Error en el caso 010"
	severity failure;
	
	sigA<='0'; sigB<='1';sigC<='1';
	wait for ESPERA;
	
	assert q='1'
	report "Error en el caso 011"
	severity failure;
	
	sigA<='1'; sigB<='0';sigC<='0';
	wait for ESPERA;
	
	assert q='0'
	report "Error en el caso 100"
	severity failure;
	
	sigA<='1'; sigB<='0';sigC<='1';
	wait for ESPERA;
	
	assert q='1'
	report "Error en el caso 101"
	severity failure;
	
	sigA<='1'; sigB<='1';sigC<='0';
	wait for ESPERA;
	
	assert q='0'
	report "Error en el caso 110"
	severity failure;
	
	sigA<='1'; sigB<='1';sigC<='1';
	wait for ESPERA;
	
	assert q='1'
	report "Error en el caso 111"
	severity failure;
	
	
	report "Si aparece este mensaje, la simulacion es correcta.";
	wait;
	end process;
	
	end Practica;
	
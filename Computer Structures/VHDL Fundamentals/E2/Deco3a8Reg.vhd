library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;



entity Deco3a8Reg is port (
D : in std_logic_vector (2 downto 0);
CE : in std_logic;
Clk : in std_logic;
Reset : in std_logic;
Q : out std_logic_vector (7 downto 0)
);
end Deco3a8Reg;

architecture Practica of Deco3a8Reg is
	component Deco3a8
	port ( 
		D1 : in  std_logic_vector (2 downto 0);
		Q1 : out  std_logic_vector (7 downto 0)
	);
	end component;	
	
	component Registro
	port ( 
		D2 : in  std_logic_vector (7 downto 0);
		Reset : in  std_logic;
		Clk : in  std_logic;
		Ce : in  std_logic;
		Q2 : out  std_logic_vector (7 downto 0)
	);
	end component;

	signal SigD: std_logic_vector(7 downto 0);


	begin
	
	a1: Deco3a8 PORT MAP (D1=>D, Q1=>SigD);
	a2: Registro PORT MAP (D2=>SigD,Reset=>Reset,Clk=>Clk,Q2=>Q,Ce=>CE);
	
	end Practica;
	
library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity P1e1 is

port (a,b,c:in std_logic;
	q : out std_logic);
end P1e1;

architecture Practica of P1e1 is
begin

	q<=(a or b)and c;
end Practica;
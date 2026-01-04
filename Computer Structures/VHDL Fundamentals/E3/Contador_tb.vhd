
library IEEE;
use IEEE.std_logic_1164.ALL;
use IEEE.numeric_std.ALL;

entity Contador_tb is
end Contador_tb;

architecture Simulacion of Contador_tb is 

	component Contador
	Port (
		Clk : in  STD_LOGIC;
		Reset : in  STD_LOGIC;
		Ce : in  STD_LOGIC;
		Up : in  STD_LOGIC;
		Q : out  UNSIGNED (7 downto 0)
	);
	end component;
	
	signal clk: STD_LOGIC:='0';
	signal reset: STD_LOGIC:='0';
	signal ce: STD_LOGIC:='0';
	signal up: STD_LOGIC:='0';
	
	signal q: UNSIGNED(7 downto 0);
	
		-- Constantes del testbench
	constant CLKPERIOD : time := 10 ns;
	constant ESPERA : time := 10 ns;
	constant NINPUT: integer := 3;
	
begin 


	uut: Contador port map (
			Up=>up,
			Ce => ce,
			Clk => clk,
			Reset => reset,
			Q => q
		);
	
	-- Proceso que genera el reloj
	CLKPROCESS :process
	begin
		-- Inicialización
		clk <= '0';
		wait for CLKPERIOD/2;
		clk <= '1';
		wait for CLKPERIOD/2;
	end process;
	
	stim_proc: process
	begin
	
		up<='0';
		ce<='0';
		reset<='1';
		
		wait for ESPERA;
		assert q=x"00"
			report "Error de reset"
			severity failure;
		-- Chip enable conectado
		
	
		reset<='1';
		ce <= '1';
		up<='1';
		wait for ESPERA;
		
		reset <= '0';
		ce <= '1';
		up<='1';
		
		for i in 0 to 255 loop
			assert to_integer(q) = i
				report "Falla en up=1" & to_string(i)
					severity error; 
				wait for ESPERA;
		end loop;
		
		
		
		up<='0';
		
		for i in 0 to 255 loop
			assert to_integer(q) = 255-i
				report "Falla en up=0 " & to_string(i)
					severity error; 
				wait for ESPERA;
		end loop;
		
		
		ce<='0';
		
		for i in 0 to 255 loop
			assert to_integer(q) = 0
				report "Falla en ce=0 " & to_string(i)
					severity error; 
				wait for ESPERA;
		end loop;
		
		ce<='1';
		
		wait for ESPERA;
		assert to_integer(q) = 255
			report "Error de desbrodamiento con up=0"
			severity failure;
		
		up<='1';
		
		wait for ESPERA;
		assert to_integer(q) = 0
			report "Error de desbrodamiento con up=1"
			severity failure;
		
		
		
		report "Simulación correcta";
		wait;	
	end process;

end Simulacion;
		
		
		
		
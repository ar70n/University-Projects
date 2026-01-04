----------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Fichero: MicroSuma.vhd
-- Descripción: Micro RISC-V muy simplificado, sólo suma con dato inmediato
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 3
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity MicroSuma is
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Reset activo a nivel bajo
		MemProgAddr : out unsigned(31 downto 0); -- Dirección para la memoria de programa
		MemProgData : in unsigned(31 downto 0) -- Código de operación
	);
	end MicroSuma;

architecture Practica of MicroSuma is

	-- Declaración de RegsRISCV
	component RegsRISCV
	port (
		Clk : in std_logic; -- Reloj
		NRst : in std_logic; -- Reset asíncrono a nivel bajo
		A1 : in unsigned(4 downto 0); -- Dirección para el puerto RD1
		RD1 : out signed(31 downto 0); -- Dato del puerto RD1
		A2 : in unsigned(4 downto 0); -- Dirección para el puerto RD2
		RD2 : out signed(31 downto 0); -- Dato del puerto RD2
		A3 : in unsigned(4 downto 0); -- Dirección para el puerto WD3
		WD3 : in signed(31 downto 0); -- Dato de entrada WD3
		WE3 : in std_logic -- Habilitación del banco de registros
	);
	end component;
	
	
	
	-- Declaración de ALURISCV
	component ALURISCV
	port(
   		Op1 : in signed(31 downto 0);
		Op2 : in signed(31 downto 0);
		ALUControl : in std_logic_vector (2 downto 0);
		Res : out signed(31 downto 0);
		Z : out std_logic
		);
	end component;
	
	
	
	
	-- Declaración de señales auxiliares
	
	signal sop1,sop2,C: signed(31 downto 0);
	signal Dato: unsigned(11 downto 0);
	signal PC: unsigned(31 downto 0);


begin

	-- Instancia de RegRISCV
	Registro: RegsRISCV port map (Clk=>Clk, NRst=>NRst, A1=>MemProgData(19 downto 15), RD1=>sop1, A2=>(others =>'0'),RD2=>open, A3=>MemProgData(11 downto 7), WD3=>C, WE3=>'1');
	
	

	-- Instancia de ALURISCV
	ALU : ALURISCV port map (Op1=>sop1, Op2=>sop2, ALUControl=>(others=>'0'), Z=> open, Res=>C);


	
	-- Extensión de signo
	
	Dato<=MemProgData(31 downto 20);
	sop2<=resize(signed(Dato), 32);
	
	
	-- Ruta del PC
	MemProgAddr<=PC;

process(all)
	begin 
		
	if NRst='0' then
		PC<=(others =>'0');
		
			
	elsif Clk='1' and Clk'event then 

			PC<=PC+"100";

	else
		
		
		
	end if;
	
	end process;


end Practica;


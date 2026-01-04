--------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Fichero: UnidadControlTb.vhd
-- Descripción: Testbench para la unidad de Control para el microprocesador MIPS
-- Versión profesores. Indica nota.
-- Fichero de apoyo para: Práctica: 4. Ejercicio: 1
----------------------------------------------------------------------
----------------------------------------------------------------------


library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
 
entity UnidadControlTb is
end UnidadControlTb;
 
architecture behavior of UnidadControlTb is
 
   type CasosPruebaT is record
		instruccion_nombre : string(10 downto 1);
		instruccion : std_logic_vector(31 downto 0);
		sigControl :  std_logic_vector(8 downto 0);
		aluControl : std_logic_vector(2 downto 0);
		flag_z : std_logic;
	end record;

	component UnidadControl
	port(
		Op : in  std_logic_vector (6 downto 0); -- OPCode de la instrucción
		Funct3 : in std_logic_vector(2 downto 0); -- Funct3 de la instrucción
		Funct7_5 : in std_logic; -- Bit 5 de Funct7 de la instrucción
		
		-- Señales para el PC
		Zero : in std_logic;
		PCSrc : out  std_logic;
		Jalr : out std_logic;
		
		-- Señales para la memoria
		ResultSrc : out std_logic_vector(1 downto 0);
		MemWrite : out std_logic;
		
		-- Señales para la ALU
		ALUControl : out std_logic_vector (2 downto 0);
		ALUSrc : out std_logic;
		
		ImmSrc : out std_logic_vector(1 downto 0);
		
		-- Señales para el GPR
		RegWrite : out std_logic
    );
	end component;

	signal op_nombre : string(10 downto 1);
   --Inputs
   signal Op : std_logic_vector(6 downto 0) := (others => '0');
   signal funct3 : std_logic_vector(2 downto 0) := (others => '0');
   signal funct7_5 : std_logic := '0';
   signal zero : std_logic := '0';
   

 	--Outputs
	signal regWrite, ALUSrc, branch, memWrite, jump, PCSrc : std_logic;
	signal ALUControl : std_logic_vector(2 downto 0);
	signal ResultSrc, ImmSrc : std_logic_vector(1 downto 0);
	signal jalr : std_logic;
	
	signal controlFlags : std_logic_vector(8 downto 0);
	
	signal instruc : std_logic_vector(31 downto 0);
	
	-- numero de casos de prueba
	constant NUMCASOSPRUEBA : integer := 18;

	-- matriz de casos de prueba
	type CasosPruebaT2 is array (1 to NUMCASOSPRUEBA) of CasosPruebaT;

  
  constant casos_prueba : CasosPruebaT2 := (
	-- SENIALES_CTRL: PCSrc,Jalr,ResultSrc(1:0),MemWrite,ALUSrc,ImmSrc(1:0),RegWrite
	
	-- 1 INSTRUCCION: add
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"add       ", x"003100B3",	"000000--1",	"000", '1'),
	-- 2 INSTRUCCION: sub
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"sub       ", x"403100B3",	"000000--1",	"001", '1'),
	-- 3 INSTRUCCION: xor
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"xor       ", x"003140B3",	"000000--1",	"111", '1'),
	-- 4 INSTRUCCION: or
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"or        ", x"003160B3",	"000000--1",	"011", '1'),
	-- 5 INSTRUCCION: and
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"and       ", x"003170B3",	"000000--1",	"010", '1'),
	-- 6 INSTRUCCION: slt
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"slt       ", x"003120B3",	"000000--1",	"101", '1'),
	-- 7 INSTRUCCION: lw
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"lw        ", x"00512083",	"000101001",	"000", '1'),
	-- 8 INSTRUCCION: addi
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"addi      ", x"00510093",	"000001001",	"000", '1'),
	-- 9 INSTRUCCION: slti
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"slti      ", x"00512093",	"000001001",	"101", '1'),
	-- 10 INSTRUCCION: xori
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"xori      ", x"00514093",	"000001001",	"111", '1'),
	-- 11 INSTRUCCION: ori
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"ori       ", x"00516093",	"000001001",	"011", '1'),
	-- 12 INSTRUCCION: andi
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"andi      ", x"00517093",	"000001001",	"010", '1'),
	-- 13 INSTRUCCION: jalr
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"jalr      ", x"005100E7",	"-11001001",	"000", '1'),
	-- 14 INSTRUCCION: sw 
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"sw        ", x"001122A3",	"00--11010",	"000", '1'),
	-- 15 INSTRUCCION: beq con Z=0
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"beq Z=0   ", x"00208263",	"00--00100",	"001", '0'),
	-- 16 INSTRUCCION: beq con Z=1
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"beq Z=1   ", x"00208263",	"10--00100",	"001", '1'),
	-- 17 INSTRUCCION: auipc
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"auipc     ", x"12345097",	"00110---1",	"---", '1'),
	-- 18 INSTRUCCION: jal
	--	INSTRUCCION		SENIALES_CTRL	ALU_OP ZERO
	(	"jal       ", x"FFDFF0EF",	"10100---1",	"---", '1')	
	);
	
	 -- Tiempo que vamos a esperar a que conteste la UC  
  constant tdelay : time := 10 ns;
  
  signal fallos : integer := 0;
  
BEGIN
 

	uut: UnidadControl PORT MAP (
		Op => op,
		Funct3 => funct3,
		Funct7_5 => funct7_5,
		Zero => zero,
		PCSrc => pcSrc,
		Jalr => jalr,
		
		-- Señales para la memoria
		ResultSrc => resultSrc,
		MemWrite => memWrite,
		
		-- Señales para la ALU
		ALUControl => aluControl,
		ALUSrc => aluSrc,
		
		ImmSrc => immSrc,
		RegWrite => regWrite
	);
 
	controlFlags <= pcSrc & jalr & resultSrc & memWrite & aluSrc & immSrc & regWrite;

   -- Stimulus process
	stim_proc: process
   begin		
	     
		for i in 1 to NUMCASOSPRUEBA loop
			op_nombre <= casos_prueba(i).instruccion_nombre;
			op <= casos_prueba(i).INSTRUCCION(6 downto 0);
			funct3 <= casos_prueba(i).INSTRUCCION(14 downto 12);
			funct7_5 <= casos_prueba(i).INSTRUCCION(30);
			zero <= casos_prueba(i).flag_z;
			
			instruc <= casos_prueba(i).INSTRUCCION;
			
			wait for tdelay;
			
			assert std_match(controlFlags,casos_prueba(i).sigControl)
			report "fallo en seniales caso " & op_nombre & "(num " & integer'image(i) & " de " & integer'image(NUMCASOSPRUEBA) & " instrucciones) valor esperado: " & to_string(casos_prueba(i).sigControl) & " valor obtenido: " & to_string(controlFlags)
			severity warning;
			
			if not std_match(controlFlags,casos_prueba(i).sigControl) then
				fallos <= fallos + 1;
			end if;
			
			assert std_match(aluControl,casos_prueba(i).aluControl)
			report "fallo en ALUControl caso " & op_nombre & "(num " & integer'image(i) & " de " & integer'image(NUMCASOSPRUEBA) & " instrucciones)"
			severity warning;
			
			if not std_match(ALUControl,casos_prueba(i).aluControl) then
				fallos <= fallos + 1;
			end if;
			
			
		end loop;
		
		wait for tdelay;
		
		report "Simulación finalizada";
		report "Número de fallos: " & integer'image(fallos) severity note;
				
		wait;
	end process;

END;

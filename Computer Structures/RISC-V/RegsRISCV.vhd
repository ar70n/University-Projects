---------------------------------------------------------------------
----------------------------------------------------------------------
-- Asignatura: Estructura de Computadores. GII. 2º curso.
-- Fichero: RegsRISCV.vhd
-- Descripción: Banco completo de registros del microprocesador RISC-V
-- Fichero de apoyo para: Práctica: 2. Ejercicio: 1
----------------------------------------------------------------------
----------------------------------------------------------------------

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity RegsRISCV is
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
end RegsRISCV;

architecture Practica of RegsRISCV is

	-- Tipo para almacenar los registros
	type regs_t is array (0 to 31) of signed(31 downto 0);

	-- Esta es la señal que contiene los registros. El acceso es de la  siguiente manera: regs(i) acceso al registro i, donde i es  un entero. 
	-- Para convertir del tipo unsigned a entero se  hace de la siguiente manera: to_integer(us), donde us es un elemento de tipo unsigned

	signal regs : regs_t;

begin  -- PRACTICA

	------------------------------------------------------
	-- Escritura del registro WD
	------------------------------------------------------
	-- Escribe el contenido de WD3 en el registro indicado
	-- por A3 cuando hay flanco de subida de reloj y
	-- la señal de habilitación de escritura WE3 está activa.
	-- Tiene reset asíncrono. Si está habilitado el reset, 
	-- todos los registros se inicializan a valor 0
    process (all)
    begin
        if Nrst = '0' then
            for i in 0 to 31 loop
                regs(i) <= (others => '0');
            end loop;     

        elsif rising_edge (Clk) then
            if We3 = '1' then
                if A3 /= 0 then
                    regs(to_integer(A3)) <= Wd3;
                end if;
            end if; 
        end if;
        
    end process;


	------------------------------------------------------
	-- Lectura del registro RD1
	------------------------------------------------------
	-- Lee en RD1 el registro indicado por A1. 
	-- La lectura del registro R0 siempre devuelve 0.

    process (all)
    begin
        if A1 = 0 then
            Rd1 <= (others => '0');
        else
            Rd1 <= regs(to_integer(A1));
        end if;
    end process;
    

	------------------------------------------------------
	-- Lectura del registro RD2
	------------------------------------------------------
	-- Lee en RD2 el registro indicado por A2. 
	-- La lectura del registro R0 siempre devuelve 0.

    process (all)
    begin
        if A2 = 0 then
            Rd2 <= (others => '0');
        else
            Rd2 <= regs(to_integer(A2));
        end if;
    end process;

end Practica;


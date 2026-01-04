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
  process (all)
  begin
    case ALUControl is
      when "000" => Res <= Op1 + Op2;
      when "001" => Res <= Op1 - Op2;
      when "010" => Res <= Op1 and Op2;
      when "011" => Res <= Op1 or Op2;
      --when "100" => ;
      when "101" =>
        if Op1 < Op2 then
          Res <= (0 => '1', others => '0');
        else
          Res <= (others => '0');
        end if;
      --when "110" => ;
      when others => Res <= Op1 xor Op2;
      --when "111" => ;
    end case;
  end process;

  Z <= '1' when Res = 0 else '0';
end Practica;

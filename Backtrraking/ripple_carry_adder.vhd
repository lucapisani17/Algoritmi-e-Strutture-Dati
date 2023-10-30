----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 10.10.2023 13:58:42
-- Design Name: 
-- Module Name: ripple_carry_adder - structural
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity ripple_carry_adder is
    generic(
        N : positive := 4
    );
    Port(
        A : in std_logic_vector (N-1 downto 0); --vettore di ingressi da sommare
        B : in std_logic_vector (N-1 downto 0); --vettore di ingressi da sommare
        C_in : in std_logic; --Carry in -> riporto in ingresso
        S : out std_logic_vector (N-1 downto 0); --Vettore di somme
        C_out : out std_logic --Carry out -> riporto in uscita
        --overflow : out std_logic
    );
end ripple_carry_adder;

architecture structural of ripple_carry_adder is

    component full_adder is
        
        Port(
            a : in std_logic;
            b : in std_logic;
            c_in : in std_logic;
            s : out std_logic;
            c_out : out std_logic
        );   
    
    end component;
 
    signal cx : std_logic_vector(N-1 downto 0);

begin

    Gen: FOR i in 0 to N-1 generate
        gen_FA0: if i=0 generate
           FA_0: full_adder PORT MAP(
                a => A(i), --mappiamo l'ingresso a al segnale A(i)
                b => B(i),
                c_out => cx(i),
                c_in => C_in,
                s => S(i)
            );
        end generate;
    
        gen_FA_N_1: if i<N-1 and i>0 generate
            FA_N_1: full_adder PORT MAP(
                a => A(i),
                b => B(i),
                c_in => cx(i-1),
                c_out => cx(i),
                s => S(i)
            );
        end generate;
        
        gen_FA_N: if i=N-1 and i>0 generate
            FA_N: full_adder PORT MAP(
                a => A(i),
                b => B(i),
                c_in => cx(i-1),
                c_out => C_out,
                s => S(i)  
            );    
        end generate;   
    end generate;       

end structural;

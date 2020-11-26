Name | NetID | UIN
J Jesus Benitez-Gorostieta | jbenit5 | 661143747
Mariya Stefanova Pasheva | mpashe2  | 679604082

1. Compiling the program:
make clean
make cpath
2. Running the program:
./cpath <file> <s> <d> <budget>

SAMPLE RUN AND OUTPUT:

❯ ./cpath g1.g 0 6 100
PARETO TRADEOFF CURVE | NON-DOMINATED PATHS
-------------------------------------------
(Cost,Time)
(7  ,  9)
(10  ,  6)
(11  ,  5)

COST-FEASIBLE AND FASTEST PAIR(COST, TIME):
------------------------------------------
(11 , 5)

ACTUAL PATH:
------------------------
0 4 5 6

❯ ./cpath g1.g 6 0 100
PARETO TRADEOFF CURVE | NON-DOMINATED PATHS
-------------------------------------------
PATH NOT FEASIBLE!

COST-FEASIBLE AND FASTEST PAIR(COST, TIME):
------------------------------------------
PATH NOT FEASIBLE!
v 20130925 2
C 55800 57000 1 0 0 and2-1.sym
{
T 56200 56900 5 10 1 1 0 2 1
refdes=AND
}
C 55800 55800 1 0 0 nand2-1.sym
{
T 56200 55700 5 10 1 1 0 2 1
refdes=NAND
}
C 61100 56800 1 0 0 buf-1.sym
{
T 61600 57100 5 10 1 1 0 2 1
refdes=BUFOR
}
C 61100 53500 1 0 0 bufif0-1.sym
{
T 59400 54300 5 10 1 1 0 2 3
refdes=BUFOR 3 state
z zanegowanym
sygnałem aktywacji
}
C 56000 53500 1 0 0 bufif1-1.sym
{
T 57000 54300 5 10 1 1 0 2 1
refdes=BUFOR 3 state
}
C 57500 55800 1 0 0 nor2-1.sym
{
T 57900 55700 5 10 1 1 0 2 1
refdes=NOR
}
C 61100 55600 1 0 0 not-1.sym
{
T 61600 55900 5 10 1 1 0 2 1
refdes=NOT
}
C 57500 57000 1 0 0 or2-1.sym
{
T 57900 56900 5 10 1 1 0 2 1
refdes=OR
}
C 59200 55800 1 0 0 xnor2-1.sym
{
T 59600 55700 5 10 1 1 0 2 1
refdes=XNOR
}
C 59200 57000 1 0 0 xor2-1.sym
{
T 59600 56900 5 10 1 1 0 2 1
refdes=XOR
}
T 56100 54900 9 10 1 0 0 0 2
bramki (AND, OR, XOR, NAND, NOR, XNOR) mogą
występować także w wariantach wielo-wejściowych
T 55900 53300 9 10 1 0 0 0 1
w wariancie 3 stanowym mogą występować także wszystkie pozostałe elementy

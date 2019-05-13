v 20130925 2
N 30400 53000 30900 53000 4
C 31400 52000 1 0 0 net-gnd-1.sym
N 31500 52500 31500 52300 4
C 31400 54600 1 270 0 resistor-2.sym
{
T 31700 54400 5 10 1 1 270 0 1
refdes=R load
}
N 31500 53700 31500 53500 4
C 31400 55500 1 270 0 terminal-end_line.sym
{
T 31525 55250 5 10 1 1 0 3 1
refdes=V zasilania
T 32400 55190 5 10 0 0 270 0 1
footprint=CONNECTOR 1 1
}
N 31500 54800 31500 54600 4
C 30300 53800 1 270 0 terminal-end_line.sym
{
T 30425 53550 5 10 1 1 0 3 1
refdes=V ster
T 31300 53490 5 10 0 0 270 0 1
footprint=CONNECTOR 1 1
}
N 30400 53100 30400 53000 4
N 32900 54100 33400 54100 4
C 33900 52000 1 0 0 net-gnd-1.sym
N 34000 52500 34000 52300 4
C 33900 53400 1 270 0 resistor-2.sym
{
T 34200 53200 5 10 1 1 270 0 1
refdes=R load
}
C 33900 55500 1 270 0 terminal-end_line.sym
{
T 34900 55190 5 10 0 0 270 0 1
footprint=CONNECTOR 1 1
T 34025 55250 5 10 1 1 0 3 1
refdes=V zasilania
}
C 32800 54900 1 270 0 terminal-end_line.sym
{
T 33800 54590 5 10 0 0 270 0 1
footprint=CONNECTOR 1 1
T 32925 54650 5 10 1 1 0 3 1
refdes=V ster
}
N 32900 54200 32900 54100 4
N 34000 54800 34000 54600 4
N 34000 53600 34000 53400 4
C 30900 52500 1 0 0 transistor-nmosfet-1.sym
{
T 31750 52850 5 10 1 1 180 6 2
refdes=N-MOSFET
enhancement
}
C 33400 54600 1 180 1 transistor-pmosfet-1.sym
{
T 34250 53950 5 10 1 1 0 2 2
refdes=P-MOSFET
enhancement
}
C 36000 54000 1 0 0 transistor-nmosfet-deppletion-1.sym
{
T 36850 54350 5 10 1 1 180 6 2
refdes=N-MOSFET
depletion
}
C 36000 53300 1 180 1 transistor-pmosfet-deppletion-1.sym
{
T 36850 52650 5 10 1 1 0 2 2
refdes=P-MOSFET
depletion
}

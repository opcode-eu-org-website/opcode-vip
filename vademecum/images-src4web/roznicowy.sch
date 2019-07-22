v 20130925 2
C 43400 46100 1 0 0 transistor-npn-1.sym
{
T 43400 46100 5 10 1 1 0 0 1
refdes=T1
}
C 46400 46100 1 0 1 transistor-npn-1.sym
{
T 46400 46100 5 10 1 1 0 6 1
refdes=T2
}
C 44100 47100 1 90 0 terminal-in_line.sym
{
T 43500 47410 5 10 0 0 90 0 1
footprint=CONNECTOR 1 1
T 43550 47650 5 10 1 1 180 6 1
refdes=out1
}
C 45900 47100 1 90 0 terminal-in_line.sym
{
T 45300 47410 5 10 0 0 90 0 1
footprint=CONNECTOR 1 1
T 45950 47650 5 10 1 1 180 6 1
refdes=out2
}
N 44000 47200 44000 47100 4
N 45800 47200 45800 47100 4
C 45900 47800 1 90 0 resistor-2.sym
{
T 46300 48300 5 10 1 1 180 0 1
refdes=RC2
}
C 44100 47800 1 90 0 resistor-2.sym
{
T 44500 48300 5 10 1 1 180 0 1
refdes=RC1
}
C 43800 48700 1 0 0 net-pwr-1.sym
{
T 44000 49050 5 9 1 1 0 5 1
value=Vcc
}
C 45600 48700 1 0 0 net-pwr-1.sym
{
T 45800 49050 5 9 1 1 0 5 1
value=Vcc
}
C 42600 46500 1 0 0 terminal-end_line.sym
{
T 42910 47100 5 10 0 0 0 0 1
footprint=CONNECTOR 1 1
T 42950 46550 5 10 1 1 0 6 1
refdes=in1
}
N 43300 46600 43400 46600 4
C 47200 46500 1 0 1 terminal-end_line.sym
{
T 46850 46550 5 10 1 1 0 0 1
refdes=in2
T 46890 47100 5 10 0 0 0 6 1
footprint=CONNECTOR 1 1
}
N 46500 46600 46400 46600 4
N 44000 46100 44000 45900 4
N 44000 45900 45800 45900 4
N 45800 45900 45800 46100 4
N 44900 45700 44900 45900 4
N 44900 44700 44900 44800 4
C 45100 44700 1 180 0 net-pwr-1.sym
{
T 44900 44450 5 10 0 1 180 3 1
net=-Vee:1
T 44900 44350 5 9 1 1 180 5 1
value=-Vee
}
C 45000 44800 1 90 0 resistor-2.sym
{
T 44700 45300 5 10 1 1 180 0 1
refdes=Ree
}
v 20130925 2
C 34200 47000 1 90 0 bufif1-1.sym
{
T 33900 47500 5 10 0 1 90 2 1
refdes=U?
}
T 30400 47300 9 10 1 0 0 0 2
dekoder
adresu
N 28000 51100 37000 51100 4
{
T 28300 51200 5 10 1 1 0 0 1
netname=DANE/ADRES, n-bitów
}
N 28000 50400 37000 50400 4
{
T 28300 50500 5 10 1 1 0 0 1
netname=Adres / Not Dane
}
N 31000 50400 31000 47800 4
B 30300 47100 900 700 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
C 26900 49900 1 0 0 buf-1.sym
{
T 27400 50200 5 10 0 1 0 2 1
refdes=U?
}
N 28000 49700 37000 49700 4
{
T 28300 49800 5 10 1 1 0 0 1
netname=Read / Not Write
}
N 28000 49000 37000 49000 4
{
T 28300 49100 5 10 1 1 0 0 1
netname=Clock
}
C 26900 49200 1 0 0 buf-1.sym
{
T 27400 49500 5 10 0 1 0 2 1
refdes=U?
}
C 26900 48500 1 0 0 buf-1.sym
{
T 27400 48800 5 10 0 1 0 2 1
refdes=U?
}
T 26500 48400 9 10 1 0 90 0 1
kontroler magistrali / master
N 26900 50400 26800 50400 4
{
T 26900 50400 5 10 0 0 0 0 1
netname=1
}
N 26900 49700 26800 49700 4
{
T 26900 49700 5 10 0 0 0 0 1
netname=1
}
N 26900 49000 26800 49000 4
{
T 26900 49000 5 10 0 0 0 0 1
netname=1
}
N 34400 51100 34400 46800 4
C 31900 45100 1 0 0 and2-1.sym
{
T 32300 45000 5 10 0 1 0 2 1
refdes=U?
}
C 31400 47900 1 270 0 not-1.sym
{
T 31700 47400 5 10 0 1 270 2 1
refdes=U?
}
N 31000 45200 31000 47100 4
{
T 30900 45600 5 10 1 1 90 0 2
netname=1 (TRUE) gdy
adres zgodny
}
N 33700 51100 33700 48100 4
C 34900 46800 1 90 1 bufif1-1.sym
{
T 34600 46300 5 10 0 1 90 8 1
refdes=U?
}
C 31900 45900 1 0 0 and2-1.sym
{
T 32300 45800 5 10 0 1 0 2 1
refdes=U?
}
N 31000 46000 31900 46000 4
N 31900 45200 31000 45200 4
N 31500 45600 31500 49700 4
N 33700 47000 33700 44700 4
{
T 33900 44700 5 10 1 1 90 0 1
netname=Data OUT
}
N 31500 47900 31900 47900 4
N 31900 46800 31900 46400 4
N 31500 45600 31900 45600 4
N 33300 46200 33300 47000 4
{
T 33100 46400 5 10 1 1 90 2 1
netname=WR
}
N 34000 46800 33500 46800 4
N 33500 46800 33500 45400 4
{
T 33300 45500 5 10 1 1 90 2 1
netname=RD
}
N 33500 45400 33200 45400 4
T 25900 44600 9 10 1 0 0 0 12
sygnały read (RD) i write (WR) wyrażone
z punktu widzenia podłączonego urządzenia:
  WR = zapis na magistralę
  RD = odczyt z magistrali
(często przedstawiane sa z punktu widzenia magistrali)

w przypadku rozdzielonych linii danych i adresu:
  - zamiast sygnału "Adres / Not Data"
    jest m-bitowa szyna adresowa
  - dekoder adresu nie korzysta z linii danych
    tylko z szyny adresowej

N 34400 45700 34400 44700 4
{
T 34600 44700 5 10 1 1 90 0 1
netname=Data IN
}
N 28000 48300 37000 48300 4
{
T 28300 48400 5 10 1 1 0 0 1
netname=Żądanie obsługi, i-bitów
}
C 28000 47800 1 0 1 buf-1.sym
{
T 27500 48100 5 10 0 1 0 8 1
refdes=U?
}
C 27100 47600 1 0 0 resistor-1.sym
{
T 27300 47900 5 10 0 1 0 0 1
refdes=R?
}
N 28000 47700 28100 47700 4
N 28100 47700 28100 48300 4
C 26800 47700 1 0 0 net-pwr-1.sym
{
T 27000 48050 5 9 1 1 0 5 1
value=Vcc
}
N 27100 47700 27000 47700 4
N 26900 48300 26800 48300 4
{
T 26900 48300 5 10 0 0 0 0 1
netname=1
}
B 26000 47400 2200 4100 3 0 0 0 -1 -1 0 -1 -1 -1 -1 -1
C 35900 46200 1 0 0 transistor-npn-3.sym
N 35800 48300 35800 47200 4
N 35800 47200 36500 47200 4
C 36400 45800 1 0 0 net-gnd-1.sym
N 36500 46100 36500 46200 4
N 35800 45300 35800 44700 4
{
T 36200 44700 5 10 1 1 90 0 2
netname=sygnał
przerwania
}
T 35900 47300 9 10 1 0 0 0 3
wybrany
zestaw
bitów IRQ
C 36300 45300 1 90 0 buf-1.sym
{
T 36000 45800 5 10 0 1 90 2 1
refdes=U?
}
N 35800 46400 35800 46700 4
N 30500 51100 30500 47800 4
N 35800 46700 35900 46700 4
N 33200 46200 33300 46200 4
C 34600 48100 1 270 0 buf-1.sym
{
T 34900 47600 5 10 0 1 270 2 1
refdes=U?
}
N 35100 47000 35100 44700 4
{
T 35300 44700 5 10 1 1 90 0 1
netname=Clock IN
}
N 35100 48100 35100 49000 4

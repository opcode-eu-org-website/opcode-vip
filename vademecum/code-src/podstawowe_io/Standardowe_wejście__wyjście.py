
import sys

# wypisywanie na standardowe wyjście
print("ABC: " + str(12) + " = " + hex(12))

# bez nowej linii na końcu
print("abc", end='')

# wypisywanie na standardowe wyjście błędu
print("QWE", file=sys.stderr)

# odczyt z wejścia
li = iter(sys.stdin)
liniaA = next(li)
liniaB = next(li)
print("l1: " + liniaA + "l2: " + liniaB)

# można też z użyciem metody czytającej jedną linię
liniaA = sys.stdin.readline()
liniaB = sys.stdin.readline()
print("l1: " + liniaA + "l2: " + liniaB)

# należy zauważyć że dane wczytywane są
# liniami i zawierają znak końca linii

# można także w ramach:
#   for l in sys.stdin:
#
# lub skorzystać z metody wczytującej cały plik
# jako listę poszczególnych jego linii:
#   ll = sys.stdin.readlines()
# bądź po prostu jako jeden napis
#   napis = sys.stdin.read()

# jest też:
info = input("Wpisz coś: ")
print(info)

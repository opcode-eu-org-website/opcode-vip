
# Python pozwala na definiowanie funkcji wewnątrz funkcji oraz łatwe przechowywanie
# funkcji w zmiennych, także kolekcjach takich jak listy i słowniki.
# Warto zwrócić uwagę na sposób obsługi zmiennych globalnych,
# czy też zewnętrznych w takich przypadkach.

# W poniższym przykładzie widzimy, że funkcje tak zdefiniowane nie korzystają
# z wartości zmiennej x z miejsca definicji, tylko z miejsca wywołania.
# Jeżeli potrzebujemy aby funkcja używała wartości z chwili definicji to możemy
# użyć x jako wartości domyślnej któregoś z argumentów tej funkcji.

tablicaA = [None] * 4
tablicaB = [None] * 4

for x in [0, 1, 2, 3]:
	def tmpA(a):
		return x+a
	def tmpB(a, x=x): # x=x nakazuje przechwycić obecną wartość x
		return x+a
	tablicaA[x]=tmpA
	tablicaB[x]=tmpB

print (x, " + 3 =", tablicaA[1](3), "    1 + 3 = ", tablicaB[1](3))
x = 0
print (x, " + 3 =", tablicaA[1](3), "    1 + 3 = ",  tablicaB[1](3))


# Lambda jest innym sposobem lokalnego definiowania funkcji (często dostępnym także
# w językach nie pozwalających na tak swobodne definiowanie zwykłych funkcji)
# W tym przypadku definicja jest jeszcze bardziej lokalna,
# funkcja nawet nie posiada swojej nazwy.
# Lambda może być przypisana do jakiejś zmiennej lub przekazana w argumencie.
# Sposób traktowania zmiennych zewnętrznych jest analogiczny.

tablicaA = [None] * 4
tablicaB = [None] * 4

for x in [0, 1, 2, 3]:
	tablicaA[x] = lambda a: x+a
	tablicaB[x] = lambda a,x=x: x+a # x=x nakazuje przechwycić obecną wartość x

print (x, " + 3 =", tablicaA[1](3), "    1 + 3 = ", tablicaB[1](3))
x = 0
print (x, " + 3 =", tablicaA[1](3), "    1 + 3 = ",  tablicaB[1](3))

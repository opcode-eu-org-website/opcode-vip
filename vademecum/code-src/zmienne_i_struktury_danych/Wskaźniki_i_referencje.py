
a, b = 5, [1, 2, 3]

def pinfo(x, xx):
	print(
		"id(x) =", hex(id(x)),
		" == " if id(xb) == id(xx) else " != ",
		"id(xx) =", hex(id(xx))
	)

# utworzenie kopii zmiennej oznacza utworzenie
# nowej referencji wskazującej nadal na ten sam
# obiekt w pamięci
aa = a
pinfo(id(a), id(aa)
bb = b
pinfo(id(b), id(bb)

# przypisanie nowego obiektu pod zmienną
# powoduje zmianę (adresu) obiektu który
# wskazuje:
aa = 5
pinfo(id(a), id(aa)
bb = [9, 11, 13]
pinfo(id(b), id(bb)

# ale modyfikacja obiektów "immutable"
# (takich jak liczby, napisy) nie jest możliwa
# zatem zawsze tworzony jest nowy obiekt
aa=a
aa+=1
pinfo(id(a), id(aa)

# jeżeli do starego obiektu nie ma innych
# referencji może on zostać usunięty
# a nowy może być umieszczony w jego miejscu
# (w takim przypadku wynik id się nie zmieni)

# natomiast modyfikacja obiektów "mutable"
# (takich jak listy i słowniki)
# nie tworzy nowego obiektu tylko modyfikuje
# istniejący (wynik id się nie zmieni) zatem
# wszystkie referencje wskazują na zmodyfikowany
# obiekt:
bb = b
bb[0] = 17
print ("bb =", bb, "b=", b)
pinfo(id(b), id(bb)

# aby uzyskać kopię należy skorzystać
# z odpowiedniej metody
bb = b.copy()

print ("bb =", bb, "b=", b)

bb[0] = 99
print ("bb =", bb, "b=", b)
pinfo(id(b), id(bb)

# uwaga kopiowanie takie jest płytkie: jeżeli w
# liście mamy obiekty "mutable" obie (niezależne
# pod względem zbioru elementów) kopie listy
# będą wskazywać na te same obiekty


# usuwanie zmiennej
b = None
# mapowanie zmiennej "b" zostało zmienione
# nie wskazuje już na listę tylko na
# obiekt typu NoneType

bbb = bb
del bb
# nazwa "bb" została usunięta
# ale do danych możemy dostawać się przez "bbb"

# dopiero po usunięciu wszystkich referencji
# na dany obiekt to Python może go usunąć (ale
# nie musi wykonać tego natychmiast)


# python także umożliwia przekazywanie funkcji
# jako argumentu do innej funkcji
def a(z):
	print(z*3)

def b(x, y):
	x(y+2)

b(a, 1)

# ponadto funkcja może także zwracać funkcję:
def aa(y):
	def t(x):
		return y*x
	return t

b = aa(3)
b(2)

# można też:
aa(3)(4)

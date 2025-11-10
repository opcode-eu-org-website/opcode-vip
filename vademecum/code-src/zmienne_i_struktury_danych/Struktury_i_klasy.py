
class NazwaKlasy:
	# pola składowe
	a=0
	d="ala ma kota"
	
	# metody składowe
	def wypisz(self):
		print(self.a + self.b)
	# warto zauważyć jawny argument w postaci obiektu tej klasy
	# w innych językach (np. C++) także on występuje,
	# ale nie jest jawnie deklarowany, ani nie trzeba się nim jawnie posługiwać
	
	# metody statyczna
	@staticmethod
	def info():
		print("INFO")
	
	# konstruktor (z jednym argumentem)
	def __init__(self, x = 1):
		print("konstruktor", self.a , self.d)
		# i kolejny sposób na utworzenie pola składowego klasy
		self.b = 13 * x

# tworzenie obiektu klasy i używanie go
k = NazwaKlasy()
k.a = 67
k.wypisz()

# do metod można odwoływać się także tak:
# (jawne użycie argumentu w postaci obiektu klasy)
NazwaKlasy.wypisz(k)

# korzystanie z metod statycznych
NazwaKlasy.info()

print("k jest typu:", type(k))
print("natomiast k.a jest typu:", type(k.a))

# obiekty można rozszerzać o nowe składowe i funkcje:
k.b = k.a + 10
print(k.b)

# w ten sposób można też tworzyć całe struktury:
class Pusta():
  pass
x = Pusta()
x.a = 3
x.b = 4

# Od strony implementacyjnej są one trzymane w słowniku
# związanym z danym obiektem o nazwie `__dict__`:
print(k.__dict__, x.__dict__, sep='\n')

# w `k.__dict__` nie znajduje się wartość pola `d` jest tak dlatego,
# że nie uległa ona modyfikacji w stosunku co do domyślnej wartości dla klasy
# więc ma wartość wspólną dla wszystkich obiektów tej klasy
# może ona być zmieniona dla pojedynczego obiektu (jak było z `a`) lub dla wszystkich:

NazwaKlasy.d='abc'
print(k.d)

# lae nie będzie miało to efektu jeżeli w danym obiekcie została nadpisana:

NazwaKlasy.a = 13
print(k.a)

# Obiekty klas są obiektami modyfikowalnymi,
# zatem jak wiemy zwykłe przypisanie tworzy tylko inną referencję na ten sam obiekt.
# Celem utworzenia kopii naszego obiektu możemy zaimplementować własną metodę copy
# lub skorzystać z funckji copy dostarczanej przez moduł copy.

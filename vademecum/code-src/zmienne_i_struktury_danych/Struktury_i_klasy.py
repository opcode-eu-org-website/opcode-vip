
class NazwaKlasy:
	# pola składowe
	a=0
	d="ala ma kota"
	
	# metody składowe
	def wypisz(self):
		print(self.a + self.b)
	# warto zauważyć jawny argument
	# w postaci obiektu tej klasy
	# w C++ także występuje ale nie jest
	# jawnie deklarowany, ani nie trzeba
	# się nim jawnie posługiwać
	
	# metody statyczna
	def info():
		print("INFO")
	
	# konstruktor (z jednym argumentem)
	def __init__(self, x = 1):
		# i kolejny sposób na utworzenie
		# pola składowego klasy
		self.b = 13 * x

# korzystanie z klasy
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

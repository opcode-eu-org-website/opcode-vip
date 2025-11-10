
# klasa abstracyjna
from abc import ABC, abstractmethod
class Kształt(ABC):
	@abstractmethod
	def objetosc(self):
		return None
	
	@staticmethod
	@abstractmethod
	def typKształtu():
		return None

# jednak ze względu na dynamiczne typowanie klasy abstrakcyjne
# w Pythonie odgrywają mniejszą rolę niż w C++

# klasy dziedzicząca po klasie Kształt
class Kula(Kształt):
	def __init__(self, r):
		self.promien = r
		
	def objetosc(self):
		return 1.25 * 3.14 * self.promien ** 3
	
	@staticmethod
	def typKształtu():
		return 'Kula'

class Prostopadłościan(Kształt):
	def __init__(self, a, b, c):
		self.a = a
		self.b = b
		self.c = c
	
	def objetosc(self):
		return self.a * self.b * self.c
	
	@staticmethod
	def typKształtu():
		return 'Prostopadłościan'

# można dziedziczyć po klasach nie abstrakcyjnych
# oraz po klasach, które już dziedziczą po jakiejś
class Szescian(Prostopadłościan):
	def __init__(self, a):
		self.bok = a;
	
	def objetosc(self):
		return self.bok ** 3

k = Kula(1)
print(k.typKształtu(), k.objetosc())

s = Szescian(2)
print(s.typKształtu(), s.objetosc())
# tu wykonała się funkcja `typKształtu` z klasy `Prostopadłościan`
# bo nie została nadpisana w klasie `Szescian`

class Kolor:
	def __init__(self, r, g, b):
		self.r = r
		self.g = g
		self.b = b

# Możliwe jest także dziedziczenie po jednej lub kilku klasach bazowych:
class Opakowanie(Szescian, Kolor):
	def __init__(self, a):
		Szescian.__init__(self, a)
		Kolor.__init__(self, .5, .5, .5)

o = Opakowanie(1)
print(o.objetosc(), o.b)


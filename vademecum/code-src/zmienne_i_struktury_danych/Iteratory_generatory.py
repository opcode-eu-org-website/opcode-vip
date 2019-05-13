
# niekiedy zamiast tworzenia listy lepsze może być
# uzyskiwanie jej kolejnych elementów "na żywo"
# funkcjonalność taką w pythonie zapewniają generatory:

def f(l):
	a, b = 0, 1
	for i in range(l):
		r, a, b = a, b, a + b
		yield r

# użycie generatora w pętli for
for i in f(16):
	print(i)

# można także tworzyć generatory nieskończone
def ff():
	a, b = 0, 1
	while True:
		r, a, b = a, b, a + b
		yield r

# pobieranie kolejnych elementów
a = iter( ff() )
print( next(a) )
print( next(a) )

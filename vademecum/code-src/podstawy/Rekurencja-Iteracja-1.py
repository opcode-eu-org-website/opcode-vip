
# obliczanie silni z użyciem rekurencji
def silnia(n):
	# każda rekurencja musi mieć warunek końca
	if n == 1:
		return 1
	else:
		return n*silnia(n-1)

silnia(20)

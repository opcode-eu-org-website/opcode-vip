
# iteracyjne obliczanie silni
def silnia(n):
	s = 1
	for i in range(2,n+1):
		s = s*i
	return s

silnia(20)

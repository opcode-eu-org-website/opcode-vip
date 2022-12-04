
l = [ 3, 5, 8 ]

# wstawienie elementu na koniec
l.append(1)

# wstawienie elementu na pozycje 2
l.insert(2, 13)

print("liczba elementów =", len(l))
print("pierwszy =", l[0])
print("dwa kolejne =", l[1:3])

# wypisanie wszystkich elementów
for e in l:
	# możemy modyfikować zmienną "e",
	# ale nie będzie maiło to wplywu na listę
	print(e)

# alternatywne iterowanie po elementach
# (pozwala na ich modyfikowanie)
for i in range(len(l)):
	l[i] = l[i] + 1
	print(l[i])

# możemy też uzyskać listę w oparciu o wykonanie jakiś
# operacji na danej liście w formie jednolinijkowca:
l = [a * 2 for a in l]
# listę taką możemy przypisać do innej
# lub (jak wyżej) do tej samej zmiennej

# pobranie i usuniecie ostatniego elementu
print("ostatnim był:", l.pop())
print("ostatnim był:", l.pop())

# pobranie i usuniecie elementu na wskazanej pozycji
print("drugim elementem był:", l.pop(1))

# wypisanie całej listy
print(l)

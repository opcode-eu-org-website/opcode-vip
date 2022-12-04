
import sys, os, select

rdfd, _, _ = select.select([sys.stdin], [], [], 3.0)
# select() przyjmuje 3 listy deskryptorów plików
# (czyli numerycznego identyfikatora otwartego pliku,
# zwracanego np. przez funkcję open()) oraz ilość sekund,
# którą ma czekać na początek danych.

# Pierwsza lista związana jest z plikami z których chcemy
# czytać, druga pisać, a trzecia z plikami na których
# czekamy na wyjątkowe warunki. 

# Funkcja ta kończy działanie gdy pojawią się jakiekolwiek dane
# (nie czeka na koniec danych – EOF) i zwraca również 3 takie listy,
# ale zawierające jedynie deskryptory plików na których pożądana
# operacja jest możliwa (np. są dane do wczytania, można zapisać dane).

if not rdfd:
	print("czas minął")

for fd in rdfd:
	print("czytam z:", fd)
	a = os.read(fd.fileno(), 1024)
	# Do odczytu zastosowana została funkcja os.read() a nie metoda fd.read(),
	# wynika to z faktu, iż fd.read() czeka na EOF lub podaną ilość bajtów,
	# a os.read() wczytuje to co jest dostępne i ogranicza jedynie maksymalną
	# ilość wczytywanych danych (resztę możemy doczytać kolejnym wywołaniem).
	print("wczytałem:", a)

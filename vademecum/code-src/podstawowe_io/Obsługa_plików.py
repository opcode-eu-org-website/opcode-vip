
import os.path

# otwarcie pliku do odczytu
f=open("/etc/passwd", "r")
# funkcja pozwala na określenie kodowania pliku poprzez
# argument nazwany "encoding" (np. encoding='utf8'),
# domyślne kodowanie zależne jest od ustawień systemowych
# można je sprawdzić poprzez locale.getpreferredencoding()
#
# jeżeli plik ma być otwarty w trybie binarnym a nie
# tekstowym konieczne jest podanie flagi b w ramach
# drugiego argumentu

# odczyt po linii
l1 = f.readline()
l2 = f.readline()

# można także czytać z jawnym użyciem iteratorów:
li = iter(f)
l3 = next(li)
l4 = next(li)

print("l1: " + l1 + "l2: " + l2 + "l3: " + l3 + "l4: " + l4)

# albo w ramach pętli
i = 5
for l in f:
	print(str(i) + ": " + l)
	i += 1

# powrót na początek pliku
f.seek(0)

# odczyt jako tablica linii
ll = f.readlines()

print(ll)

f.close()

# jeżeli plik istnieje to:
if os.path.isfile("/tmp/plik3.txt"):
	# otwieramy w trybie do zapisu i odczytu
	# i ustawiamy się na końcu pliku celem dopisywania
	f=open("/tmp/plik3.txt", "r+")
	f.seek(0, 2)
else:
	f=open("/tmp/plik3.txt", "w")

# pobieramy aktualną pozycje w pliku
# (która w tym wypadku jest równa długości pliku)
pos = f.tell()

# jeżeli plik ma więcej niż 5 bajtów
if pos > 5:
	# to cofamy się o 3
	f.seek(pos-3)

f.write("0123456789")

f.close()

# obsługa plików binarnych
# wymagane jest dodanie flagi b w flagach funkcji open():
f=open("/tmp/plik1.txt", "rb")

# czytanie baj po bajcie
while True:
	b = f.read(1)
	if b == b"":
		break
	print(b)

f.close()

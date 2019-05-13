
import re

x = "abcdefg"
y = "aa bb cc bb dd bb ee"
z = "qw=rt"

# wypisanie długości napisu
print(len(x))

# wypisanie pod-napisu od 2 do końca
# i od 0 (początku)do 3
print (x[2:], x[0:3])

# wypisanie ostatniego i 3 ostatnich znaków
print (x[-1], x[-3:])

# wypisanie co 3ciego znaku z napisu oraz napisu od tyłu
print (y[::3], x[::-1])

# wyszukiwanie
# pod-napisu "bb" w y od pozycji 5
print (y.find("bb", 5))

# porównywanie
if x == "a":
	print("x == \"a\"")

if re.match(".*[dz]", x):
	print(x, "zawiera d lub z")

# sprawdzanie czy jest pod-napisem
if "ab" in x:
	print ("ab jest pod-napisem:", x)

# sprawdzanie czy jest pod-napisem
if "ba" in x:
	print ("ba jest pod-napisem:", x)

# zastępowanie
print (re.sub('[bc]+', "XX", y, 2))
print (re.sub('[bc]+', "XX", y))

# zastępowanie z użyciem podstawienia
# \\2 zostanie zastąpione wartością drugie pod-wyrażenia,
# czyli fragmentu ujętego w nawiasach
print (re.sub('([bc]+) ([bc]+)', "X-\\2-X", y))

# mamy też wpływ na zachłanność wyrażeń regularnych:

print (re.sub('bb (.*) bb', "X \\1 X", y))
# "bb (.*) bb" dopasowało najdłuższy możliwy fragment, czyli: cc bb dd

print (re.sub('.*bb (.*) bb.*', "\\1", y))
# "bb (.*) bb" dopasowało jedynie "dd", bo najdłuższy możliwy
# fragment został dopasowany przez poprzedzające ".*"

print (re.sub('.*?bb (.*) bb.*', "\\1", y))
# "bb (.*) bb" mogło i dopasowało najdłuższy możliwy fragment,
# gdyż było poprzedzone niezachłanną odmianą dopasowania
# dowolnego napisu, czyli: .*?

# Po każdym z operatorów powtórzeń (. ? + {n,m}) możemy dodać
# pytajnik (.? ?? +? {n,m}?) aby wskazać że ma on dopasowywać
# najmniejszy możliwy fragment, czyli ma działać nie zachłannie.


# nie da się modyfikować napisu z użyciem odwołań x[numer] np.
# x[2]="X"
# nie zadziała

# można (gdy dużo tego typu modyfikacji) przepisać do listy:
l=list(x)
# alternatywnie można manualnie:
#	l=[]
#	for c in x:
#		l.append(c)
# albo tak:
#	l=[c for c in x]

l[1]="X"
l[3]="qqq"
del l[5]
print("".join(l))

# albo tak (gdy mniej modyfikacji)
print(x[:2] + "XXX" + x[3:])

# można także modyfikować po kolei i dodawać do nowego napisu
s = ""
for c in x:
	if c == "a":
		s += "AA"
	else:
		s += c

print(s)

# przy pomocy metody split() napis możemy podzielić
# na listę napisów przy pomocy dowolnego separatora
print(y.split(" "))
print(y.split(" cc "))

# konwersja liczb na napis w systemach:
# dwójkowym, ósemkowym, dziesiętnym i szesnastkowym
print( bin(7), oct(0xf), str(0o10), hex(0b11) )

# liczby podawane do wypisywania są w odpowiednio systemach:
# dziesiętnym, szesnastkowym, ósemkowym i dwójkowym
# wskazane jest to przez brak prefixu i prefixy "0x" "0o" "0b"

# alternatywnie w stylu printf, ale bez dwójkowego
s = "0o%o %d 0x%x" % (0xf, 0o10, 0b11)
print(s)

# wypisywanie znaków z użyciem ich numeru w unikodzie
# - funkcja chr() zwraca napis złożony ze znaku o podanym numerze
# w ramach napisów można też użyć \uNNNN gdzie NNNN jest numerem znaku
# lub po prostu umieścić dany znak w pliku kodowanym UTF8
print(chr(0x21c4) + " == \u21c4 == ⇄")

# funkcja ord() umożliwia konwersję napis złożonego
# z pojedynczego znaku na numer unicodowy
print(hex(ord("⇄")), hex(ord("\u21c4")), hex(ord(chr(0x21c4))) )

# Python używa Unicode dla obsługi napisów, jednak przed
# przekazaniem napisu do świata zewnętrznego konieczne
# może być zastosowanie konwersji do określonej postaci
# bytowej (zastosowanie odpowiedniego kodowania)
# służy do tego metoda encode() np.
a = "aąbcć ... ⇄"
inUTF7 = a.encode('utf7')
inUTF8 =  a.encode() # lub a.encode('utf8')
print("'" + a + "' w UTF7 to: " + str(inUTF7))
print(" i jest typu: " + str(type(inUTF7)))

# obiekty typu 'bytes' mogą zostać zdekodowane do napisu
print("zdekodowany UTF7: " + inUTF7.decode('utf7'))

# lub zostać poddane dalszej konwersji np. kodowaniu base64:
import codecs
b64 = codecs.encode(inUTF8, 'base64')
print("napis w UTF8 po zakodowaniu base64 to: " + str(b64))

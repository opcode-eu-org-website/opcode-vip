
f1() {
	# wypisywanie na standardowe wyjście
	echo "Hello World"
	printf "%d %.3f\n" 123 13.15686
	
	# wypisywanie na standardowe wyjście błędu
	echo "Hello World 2" > /dev/stderr
	echo "ABC" > /dev/stderr
}

f2() {
	# odczyt ze standardowego wejścia
	# read wczytuje dane z stdin do podanych zamiennych
	# w taki sposób że do kolejnych zmiennych trafiają
	# kolejne słowa (napisy rozdzielane spacją lub
	# tabulatorem), a do ostatniej zmiennej reszta napisu
	# (do końca linii bez znaku końca linii)
	while read a b; do
		echo $(($a+$b))
	done
}

# przekierowania strumieni standardowych:

# wyjście z echo przekierowywane jest na wejście f2
echo -e "2 3\n1 6" | f2

# wyjścia f1 do odpowiednich plików
f1 > /tmp/out.txt 2> /tmp/err.txt

# użycie >> zamiast > spowoduje dopisywanie do pliku
# zamiast nadpisywania jego zawartości

# połączonych wyjść (normalnego i błędu) f1 do grep
f1 |& grep -v Hello

# standardowe wyjście może zostać przechwycone i
# podstawione w danym miejscu poprzez użycie
# `polecenie` lub $(polecenie)
echo XXX `ls -ld /tmp`
echo XXX $(ls -ld /tmp)

# często też chcemy zignorować standardowe wyjście i/lub
# standardowe wejście - możemy to uzyskać przekierowując
# je do /dev/null np:
grep '^root:' /etc/passwd > /dev/null

# przekierowanie wyjścia cat do pliku /tmp/liczby

# Operator << powoduje że tekst podawany po nim w kolejnych liniach
# będzie kierowany na standardowe wejście komendy po której wystąpił (w tym wypadku "cat"),
# aż do momentu napotkania linii zawierającej jedynie słowo podane po nim
# (w tym wypadku EOF, ale może to być dowolne inne słowo - np. KONIEC
# lub nawet ciąg znaków ze spacjami ujęty w cudzysłowa).

cat << EOF > /tmp/liczby
1 3
13 9
9 4
7 10
EOF

# Jeżeli słowo to jest ujęte w apostrofy bądź cudzysłowy to w przekazywanym tekście
# nie są dokonywane podstawienia shellowe (np. rozwijane zmienne):

cat << EOF
HOME: $HOME
EOF

cat << 'EOF'
HOME: $HOME
EOF

# przekierowanie pliku /tmp/liczby
# na standardowe wejście f2
f2 < /tmp/liczby


# Innym poleceniem przydatnym przy manipulacji strumieniami jest tee.
# Podobnie jak cat kopiuje on swoje standardowe wejście na standardowe wyjście.
# Natomiast jeżeli poda mu się ścieżkę do pliku będzie on zapisywał
# te dane także do wskazanego pliku.

echo ABC | tee /tmp/xxx
cat /tmp/xxx


# Wiele programów jeżeli w miejscu w którym oczekuje ścieżki do pliku otrzyma myślnik
# zinterpretuje to jako użycie w tym miejscu standardowego wejścia / wyjścia.
# Nawet jeżeli program nie wspiera tej konwencji możemy użyć specjalnych urządzeń
# reprezentujących te strumienie: /dev/stdin, /dev/stdout, /dev/stderr. Na przykład:

echo "ABC" > /dev/stderr

# spowoduje wypisanie komunikatu ABC na standardowym wyjściu błędu.


#
# standardowe wejście/wyjście w miejscu ścieżki do pliku
#

# Bash pozwala także na podstawienie standardowego wyjścia różnych komend
# w miejsce kilku plików bez potrzeby jawnego tworzenia plików tymaczasowych. Na przykład:

diff <(cat /etc/passwd) <(cat /etc/passwd-)

# które poleceniu diff jako jeden plik postawia standardowe wyjście pierwszego cat,
# a jako drugi plik drugiego cat.
# Oczywiście zaprezentowane zastosowanie tego z poleceniami cat
# jest bezsensowne (prościej podać ścieżki do plików),
# ale gdyby występował tam już np. jakiś grep mogłoby to być użyteczne.

# Możliwe jest też działanie w drugą stronę czyli przesłanie danych wpisywanych przez
# jeden proces do pliku jasko standardowego wejścia innego programu
# również trochę bezsensowny przykład:

echo "ABC" | tee >(grep A)

# <() i >() są rozszerzeniami bashowymi nie występującymi w czystym sh.

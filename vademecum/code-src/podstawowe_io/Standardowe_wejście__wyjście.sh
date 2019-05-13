
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
# << EOF powoduje że bash podaje na standardowe
# wejście komendy (w tym wypadku "cat") dane czytane
# z skryptu (lub swojego wejścia) dopóki nie wystąpi
# w nowej linii słowo podane po << (w tym
# wypadku EOF), jeżeli słowo to jest ujęte w '' to
# w przekazywanym tekście nie są dokonywane podstawienia
# shellowe (np. rozwijane zmienne)
cat << EOF > /tmp/liczby
1 3
13 9
9 4
7 10
EOF

# przekierowanie pliku /tmp/liczby
# na standardowe wejście f2
f2 < /tmp/liczby

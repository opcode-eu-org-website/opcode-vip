
# w bashu każda funkcja może przyjmować
# dowolną ilość parametrów pozycyjnych
# (w identyczny sposób obsługiwane są
#  argumenty linii poleceń dla całego skryptu)
f1() {
	echo "wywołano z $# parametrami"
	echo "parametry to: $@"
	
	[ $# -lt 2 ] && return;
	
	# można odwoływać się do pojedynczych parametrów
	echo "drugi: $2"
	echo "pierwszy: $1"
	
	# albo kolejnych w pętli
	for a in "$@"; do  echo $a;  done
	
	# lub z użyciem polecenia shift
	for i in `seq 1 $#`; do
		echo $1
		shift # powoduje zapomnienie $1
		      # i przenumerowanie pozostałych
		      # argumentów pozycyjnych o 1
		      # wpływa na wartości $@ $# itp
	done
	
	# funkcja może zwracać tylko wartość numeryczną
	# tzw kod powrotu
	return 83
}

# wywołanie - tak jak komendy, czyli bez nawiasów,
# a argumenty rozdzielane białym znakiem (spacją)
f1 aaa 3 t 56

# kod powrotu ostatnio wywołanej komendy lub funkcji
# uzyskuje się poprzez $?:
echo $?


# często funkcje (tak jak wiele komend) wynik swojego
# działania zwracają poprzez standardowe wyjście

f2() { echo "Uwolnić mrożone truskawki$1"; }

# pozyskać go można poprzez `` lub $()
# zapis z użyciem $() może być zagnieżdżony

a=`f2 '!!!'`
echo $a

b=$(f2 '!')
echo $b

# w jednolinijkowym zapisie definicji funkcji (jak
# miało to miejsce dla f2) spacje po { i przed } są
# obowiązkowe, podobnie jak średniki po instukcjach

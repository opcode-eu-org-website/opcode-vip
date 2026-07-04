
# W powłoce sh każda funkcja może przyjmować dowolną ilość parametrów pozycyjnych
# (w identyczny sposób obsługiwane są argumenty linii poleceń dla całego skryptu).

# Ilość parametrów znajduje się w zmiennej $#, lista wszystkich parametrów w $@,
# a do kolejnych parametrów możemy odwoływać się z użyciem $1, $2, itd.

f1() {
	# W nawiasach po nazwie funkcji nie podajemy przyjmowanych argumentów,
	# natomiast puste nawiasy te są elementem składniowym i muszą wystąpić.
	
	echo "wywołano z $# parametrami, parametry to: $@"
	
	[ $# -lt 2 ] && return;
	
	# można odwoływać się do pojedynczych parametrów
	echo "drugi: $2"
	echo "pierwszy: $1"
	
	# albo kolejnych w pętli
	echo "wypisane zostaną kolejne argumenty funkcji:"
	for a in "$@"; do  echo $a;  done
	
	# warto zwrócić uwagę na traktowanie spacji wewnątrz argumentów
	# gdy $@ w pętli jest lub nie jest w cudzysłowach
	echo "wypisane zostaną kolejne słowa z \$@:"
	for a in $@; do  echo $a;  done
	
	# lub z użyciem polecenia shift
	for i in `seq 1 $#`; do
		echo "z użyciem shift: $1"
		shift # powoduje zapomnienie $1
		      # i przenumerowanie pozostałych argumentów pozycyjnych o 1
		      # wpływa na wartości $@ $# itp
	done
	
	# funkcja może zwracać tylko wartość numeryczną - tzw kod powrotu
	return 83
}

# Wywołanie funkcji wygląda tak samo tak jak wywołania programów czy poleceń wbudowanych,
# czyli argumenty od nazwy funkcji i od siebie nawzajem rozdzielane są spacjami
# (nie występują tu nawiasy i przecinki znane z innych języków programowania).
f1 aaa 3 "t t" 56

# Kod powrotu ostatnio wywołanej funkcji uzyskuje się
# (tak samo jak innych poleceń) poprzez $?
echo $?

# Często funkcje (tak jak wiele komend) wynik swojego
# działania zwracają poprzez standardowe wyjście

f2() { echo "Uwolnić mrożone truskawki$1"; }

# Można użyć przekierowań strumieni aby przekazać go do innego programu lub funkcji
# i tak samo można pozyskać go do zmiennej poprzez `` lub $()
a=`f2 '!!!'`
echo $a

# Zapis z użyciem $() może być zagnieżdżony
b=$(f2 "! $(f2 '!!!')")
echo $b

# W jednolinijkowym zapisie definicji funkcji (jak
# miało to miejsce dla f2) spacje po { i przed } są
# obowiązkowe, podobnie jak średniki po instukcjach


#
# Grupowanie poleceń
#

# Funkcje są przykładem grupowania poleceń – funkcja stanowi nazwany blok kodu,
# czyli nazwaną grupę poleceń. Powłoka sh (i inne powłoki z nią zgodne)
# pozwalają na grupowanie bez definiowania funkcji. W tym celu możemy zastosować
# nawiasy klamrowe (tak jak w definicji funkcji) lub nawiasy okrągłe.

# Stosując nawiasy klamrowe należy pamiętać (tak samo jak było to w przypadku funkcji)
# o spacji po otwierającym nawiasie klamrowym i średniku (lub nowej linii) przed zamykającym.
# Instrukcje podane w nawiasach klamrowych będą wykonane w bieżącej powłoce,
# czyli mogą modyfikować zmienne (ale w pewnych sytuacjach może się to nie wydarzyć).

a=0;
{ echo abc; a=1; }
echo $a

# Polecenia podane w nawiasach okrągłych będą wykonane w podpowłoce,
# czyli ustawione lub zmodyfikowane w nich zmienne nie będą widoczne po zakończeniu bloku.
# Nawiasy okrągłe nie wymagają spacji i ostatniego średnika.

(echo abc; a=2)
echo $a

# Grupowanie poleceń jest przydatne na przykład w celu grupowania ich przy używaniu operatorów
# łączenia poleceń w oparciu o kod powrotu (`&&` i `||`),
# a także w celu przekazania standardowego wyjścia wielu poleceń w ramach jednego strumienia.


a=0;
{ echo AbC; echo abc; echo XyZ; a=1; } | grep b
echo $a

# W tym wypadku nawiasy klamrowe zachowały się jak nawiasy okrągłe – modyfikacja
# zmiennej `a` nie jest widoczna po zakończeniu bloku.
# Wynika to z użycia przekierowania strumienia podobnie jak w sytuacji omawianej przy pętli while.


a=12; b=3; x=5; y=6

# Aby wykonać działania arytmetyczne należy umieścić je wewnątrz $(( i ))

# Dodawanie, mnożenie, odejmowanie zapisuje się i działają one tak jak w normalnej matematyce:
e=$(( ($a + $b) * 4 - $y ))

# Dzielenie zapisuje się przy pomocy ukośnika i jest ono zawsze dzieleniem całkowitym:
c=$((  $x / $y ))

# wypisanie wyników
echo $e $c

# Do operacji arytmetycznych może być też jest wykorzystywane polecenie let.
# Najczęściej jest stosowane do inkrementacji podanej zmiennej, np.:

echo $a
let a++
echo $a

# Zarówno operator podwójnych nawiasów okrągłych jak i komenda `let`
# mogą obsługiwać wyrażenia logiczne. Mimo to operacje logiczne
# najczęściej obsługiwane są komendą `test` lub operatorem `[ ]`,
# w których wynik zwracany jest jako kod powrotu.

# Negację realizuje !, ale wynikiem negacją dowolnej liczby jest FALSE

# Należy zwrócić uwagę na escapowanie odwrotnym ukośnikiem
# nawiasów i na to że spacje mają znaczenie. Wynika to z faktu,
# nawiasy kwadratowe wraz z zawartością to argumenty dla komendy `[`.

[ \( $a -ge 0 -a $b -lt 2 \) -o $c -eq 5 ]; z=$?

# Wartość zmiennej `z` jest wynikiem warunku:
# `((a większe równe od zera) AND (b mniejsze od dwóch)) OR (c równe 5)`.
# Wynik ten został zwrócony jako *kod powrotu*,
# który jest dostępny (dla ostatnio wykonanego polecenia) poprzez `$?`.
# Wartość tej zmiennej została przypisana do zmiennej `z`.
# Kody powrotu stosują logikę odwróconą 0 oznacza prawdę, coś nie zerowego to fałsz.

echo $z


#
# wykonywanie innych programów
#

# Jako operacje podstawowe powinniśmy także traktować wykonanie innych
# programów i pobieranie ich standardowego wyjścia i/lub kodu powrotu.

# Pobieranie standardowego wyjścia możemy realizować za pomocą ujęcia
# polecenia w backquotes (`) lub operatora $( )
# (pozwala on na zagnieżdżanie takich operacji).

# Natomiast kod powrotu ostatniej komendy znajduje się w zmiennej `$?`.

a=`cat /etc/issuse`
b=$(cat /etc/issuse; cat /etc/resolv.conf)

echo  $a
echo  $b
echo "$b"

# Zwróć uwagę na różnicę w wypisaniu zmiennej zawierającej znaki nowej
# linii objętej cudzysłowami i nie objętej nimi.

# Bash nie obsługuje liczb zmiennoprzecinkowych ani operacji bitowych,
# nieobsługiwane operacje można wykonać za pomocą innego programu np:

a=`echo 'print(3/2)' | python3`
b=$(echo '3/2' | bc -l)
echo $a $b

# Programowanie w powłoce w dużej mierze polega na wywoływaniu innych programów
# (np. takich jak sed, grep, find, awk). Sama powłoka oferuje jedynie podstawowe
# konstrukcje składniowe, obsługę zmiennych i pewnych podstawowych operacji na nich.

# Na te zewnętrzne polecenia można patrzeć trochę jak na biblioteki w innych językach
# programowania – komendy gwarantowane przez standard stanowią „bibliotekę standardową” basha,
# a inne (np. użyty w powyższym przykładzie arytmetyki zmiennoprzecinkowej python)
# stanowią dodatkowe opcjonalne „biblioteki”, które pozwalają na łatwiejsze
# i szybsze rozwiązywanie problemów.

# W zasadzie podobnie można patrzeć na wywołania zewnętrznych programów w ramach kodu
# Pythona, C czy innych języków (niekiedy łatwiej jest zrobić
# np. `system("mv plik nowyplik")` niż zakodować to bezpośrednio w Pythonie czy w C).

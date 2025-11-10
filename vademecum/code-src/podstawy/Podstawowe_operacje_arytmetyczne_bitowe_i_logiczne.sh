
a=12; b=3; x=5; y=6

# aby wykonać działania arytmetyczne należy umieścić je wewnątrz $(( i ))

# dodawanie, mnożenie, odejmowanie zapisuje się i działają
# tak jak w normalnej matematyce:
e=$(( ($a + $b) * 4 - $y ))

# dzielenie całkowite
c=$((  $x / $y ))

# wypisanie wyników
echo $e $c

# Do operacji arytmetycznych może być też jest wykorzystywane polecenie let.
# Najczęściej jest stosowane do inkrementacji podanej zmiennej, np:

echo $a
let a++
echo $a

# Zarówno operator podwójnych nawiasów okrągłych jak i komenda `let`
# mogą obsługiwać wyrażenia logiczne. Mimo to operacje logiczne
# najczęściej obsługiwane są komendą `test` lub operatorem `[ ]`,
# w których wynik zwracany jest jako kod powrotu.
# Należy zwrócić uwagę na escapowanie odwrotnym ukośnikiem
# nawiasów i na to że spacje mają znaczenie.
# [ jest w istocie komendą, działającą jak test,
# tyle że wymaga ] jako ostatniego argumentu.

# ((a większe równe od zera) AND (b mniejsze od dwóch)) OR (c równe 5)
[ \( $a -ge 0 -a $b -lt 2 \) -o $c -eq 5 ]; z=$?

# negację realizuje !, ale wynikiem negacją dowolnej liczby jest FALSE
# więc nie da się zanegować z jak w pozostałych przykładach

echo $z
# bash stosuje logikę odwróconą 0 == TRUE, coś nie zerowego to FALSE

#
# wykonywanie innych programów
#

# Jako operacje podstawowe powinniśmy patrzyć także na wykonanie innych
# programów i pobieranie ich standardowego wyjścia i/lub kodu powrotu.

# Pobieranie standardowego wyjścia możemy realizować za pomocą ujęcia
# polecenia w backquotes (`) lub operatora $( ) (pozwala on na
# zagnieżdżanie takich operacji).
# Natomiast kod powrotu ostatniej komendy znajduje się w zmiennej $?
# (używaliśmy tego już przy obliczaniu wyrażeń logicznych).

a=`cat /etc/issuse`
b=$(cat /etc/issuse; cat /etc/resolv.conf)

echo  $a
echo  $b
echo "$b"

# Zwróć uwagę na różnicę w wypisaniu zmiennej zawierającej znaki nowej
# linii objętej cudzysłowami i nie objętej nimi.

# Bash nie obsługuje liczb zmiennoprzecinkowych ani operacji bitowych
# nieobsługiwane operacje można wykonać za pomocą innego programu np:

a=`echo 'print(3/2)' | python3`
b=$(echo '3/2' | bc -l)
echo $a $b

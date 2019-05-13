
a=12; b=3; x=5; y=6

# aby wykonać działania arytmetyczne należy
# umieścić je wewnątrz $(( i ))

# dodawanie, mnożenie, odejmowanie zapisuje się
# i działają one tak jak w normalnej matematyce:
e=$(( ($a + $b) * 4 - $y ))

# dzielenie całkowite
c=$((  $x / $y ))

# wypisanie wyników
# (zwróć uwagę na wynik wypisania niezainicjalizowanej zmiennej z)
echo $e $c $z


# operacje logiczne obsługiwane są komendą test
# lub operatorem [ ] wynik zwracany jest jako kod powrotu
# należy zwrócić uwagę na escapowanie odwrotnym ukośnikiem
# nawiasów i na to że spacje mają znaczenie

# ((a większe równe od zera) AND (b mniejsze od dwóch)) OR (z równe 5)
[ \( $a -ge 0 -a $b -lt 2 \) -o $z -eq 5 ]; z=$?

# negację realizuje !, ale wynikiem negacją dowolnej liczby jest FALSE
# więc nie da się zanegować z jak w pozostałych przykładach

echo $z
# bash stosuje logikę odwróconą 0 == TRUE, coś nie zerowego to FALSE

# bash nie obsługuje liczb zmiennoprzecinkowych ani operacji bitowych
# nieobsługiwane operacje można wykonać za pomocą innego programu np:
a=`echo 'print(3/2)' | python3`
b=$(echo '3/2' | bc -l)
echo $a $b

# ujęcie polecenia w znaki ` powoduje podstawienie w tym miejscu
# standardowego wyjścia tego polecenia (w tym wypadku zapisania go
# do zmiennej), alternatywną składnią jest $( polecenie )
# pokazany na przykładzie zmiennej b


###
### Pętla for
###

# W bashu możemy korzystać z kilku wariantów pętli for.
# Jednym z najczęściej używanych jest przypadek iterowania po liście elementów,
# najczęściej liście plików:

for nazwa in /tmp/* ; do
	echo $nazwa;
done

# Możliwe jest też iterowanie po wartościach całkowitych zarówno w stylu
# „shellowym” jak i w stylu C:

for i in `seq 0 20`; do
	echo $i;
done

for (( i=0 ; $i<=20 ; i++ )) ; do
	echo $i;
done


###
### Pętla while
###

# Pętla wile powtarzana jest dopóki podany w niej warunek jest prawdziwy:

x=0
while [ $x -le 2 ]; do
	echo $x;
	x=$(($x+1));
done

# Często używana jest pętla while w połączeniu z instrukcją `read`
# co umożliwia przetwarzanie jakiegoś wejścia (wyniku komendy lub pliku)
# linia po linii (także z podziałem linii na słowa):

cat /etc/fstab | while read slowo reszta; do
	echo $reszta;
done

# Powyższa pętla wypisze po kolei wszystkie wiersze pliku `/etc/fstab` przekazanego
# przez stdin (przy pomocy komendy `cat`) z pominięciem pierwszego słowa
# (które wczytywane było do zmiennej slowo).

# Polecenie `read` można także wykorzystać do wczytania do jakiejś zmiennej danych
# podawanych przez użytkownika – np. `read -p "wpisz coś >> " xyz` wczyta tekst
# ze standardowego wejścia do zmiennej `xyz`.
# `read` z opcją `-e` potrafi korzystać z biblioteki readline,
# jednak np. współdzieli historię z historią basha. Dlatego często wygodniejsze
# może być zainstalowanie i użycie `rlwrap`, np:
# `xyz=$(rlwrap -H historia.txt -S "wpisz coś >> " head -n1)`.

# Przekazanie danych do *while-read* poprzez strumień stdout → stdin z innego programu jest często
# stosowane np. w celu przefiltrowania lub posortowania danych przekazywanych do tej pętli.
# Jednak użycie w tym rozwiązaniu `cat` jest nadmiarowe (nazywane jest *martwym kotem*)
# i powinno się go unikać. Lepszym rozwiązaniem jest przekazywanie pliku przez przekierowanie
# strumienia wejściowego przy pomocy `< plik`, który w tym przypadku powinien znaleźć się za
# kończącym pętle słowem kluczowym `done`. Między innymi oszczędza ono zasoby (i czas wykonania)
# związany z tworzeniem dodatkowego procesu dla polecenia `cat`.

###
### Przekierowania strumieni a zmienne
###

# Przekierowanie standardowego wyjścia na standardowe wejście odbywa się między dwoma różnymi procesami.
# Zatem w konstrukcjach typu *while-read* pętla while uruchamiana może być w procesie potomnym
# obecnej powłoki. Efektem tego jest iż w niektórych przypadkach wykonywane modyfikacje
# zmiennych wewnątrz takiej pętli nie będą widoczne poza nią.

# Przykładem takiej sytuacji jest poniższy kod
# (polecenie ps dodano aby pokazać utworzenie procesu potomnego powłoki):

zm=0; ps -f
cat /etc/fstab | while read x; do
	[ $zm -lt 1 ] && ps -f
	zm=13
done
echo $zm

# Jednak analogiczny kod w którym następuje przekierowanie z pliku zadziała poprawnie:

zm=0; ps -f
while read x; do
	[ $zm -lt 1 ] && ps -f
	zm=13
done < /etc/fstab
echo $zm


# Jeżeli do pętli ma trafić wyjście jakiegoś polecenia możemy użyć składni bash'a pozwalającej
# na podstawienie wyniku polecenia jako pliku w postaci `<(polecenie)`
# wraz z przekierowaniem z pliku, na przykład:

zm=0; ps -f
while read x; do
	[ $zm -lt 1 ] && ps -f
	zm=13
done < <$(cat /etc/fstab)
echo $zm

# Zauważ spację pomiędzy dwoma znakami `<` i brak spacji pomiędzy drugim `<` i znakiem dolara).

# Inną możliwością jest użycie kodu powrotu do odebrania wartości z wnętrza pętli:

zm=0; ps -f
my_code() {
	while read x; do
		[ $zm -lt 1 ] && ps -f
		zm=13
	done;
	return $zm;
}
cat /etc/fstab | my_code
zm=$?
echo $zm

# Została tu zdefiniowana funkcja (`my_code`),
# o których więcej informacji znajduje się w odpowiednim rozdziale.


###
### Separator słów
###

# Słowa domyślnie rozdzielane są przy pomocy dowolnego ciągu spacji lub tabulatorów.
# Separator ten można zmienić za pomocą zmiennej `IFS`, np:

IFS=:
while read a b c d; do
	echo $c
done < /etc/passwd
unset IFS # przywracamy domyślne zachowanie read poprzez usunięcie zmiennej IFS

# Należy mieć na uwadze, że cudzysłów wokół wypisania zmiennej `c`
# są istotne – bez nich znak dwukropka mógłby być zmieniony na spacje.

# Zamiast modyfikowania wartości zmiennej IFS możemy ustawić wartość tej zmiennej
# środowiskowej dla pojedynczego wywołania programu (polecenia `read`):

while IFS=":" read a b c; do echo "$a -- $c"; done < /etc/passwd


###
### Instruikcja if
###

# Poznane wcześniej obliczanie wartości wyrażeń logicznych
# najczęściej stosowane jest w instrukcji warunkowej `if`:

if [ "$xx" = "kot" -o "$xx" = "pies" ]; then
	echo  "kot lub pies";
elif [ "$xx" = "ryba" ];  then
	echo  "ryba"
else
	echo  "coś innego"
fi

# Spacje wokół i wewnątrz nawiasów kwadratowych przy warunku są istotne składniowo.
# Wynika to z faktu, iż `[` jest w istocie komendą, działającą jak `test`,
# tyle że wymaga `]` jako ostatniego argumentu.
# Zatem wywołanie:
# `if [ "$xx" = "ryba" ]; then` jest równoważne `if test "$xx" = "ryba"; then`

# Oprócz typowych warunków logicznych możemy sprawdzać np. istnienie plików,
# czy też ich typ (link, katalog, etc). Szczegółowy opis dostępnych warunków,
# które mogą być użyte w tej konstrukcji znajduje się w `man test`.

# Jako warunek może wystąpić dowolne polecenie – wtedy sprawdzany jest jego kod powrotu:
# 0 oznacza prawdę / zakończenie sukcesem, wartość nie zerowa fałsz / błąd.
if grep '^root:' /etc/passwd > /dev/null; then
	echo /etc/passwd zawiera użytkownika root;
fi

# Istnieje możliwość skróconego zapisu warunków z użyciem łączenia instrukcji przy pomocy:
#  `&&` – wykonaj instrukcję występująca po prawej gdy poprzednia zwróciła zero (true)
#  `||` – wykonaj instrukcję występująca po prawej gdy poprzednia zwróciła nie zero (false)

[ -f /etc/issuse ] && echo "jest plik /etc/issuse"
grep '^root:' /etc/passwd > /dev/null && echo /etc/passwd zawiera użytkownika root;

###
### Instruikcja case
###

# Instrukcja `case` służy do rozważania wielu przypadków
# opartych na równości zmiennej z podanymi napisami.

case $xx in
	kot | pies)
		echo  "kot lub pies"
		;;
	ryba)
		echo  "ryba"
		;;
	*)
		echo  "cos innego"
		;;
esac


# pętla for
for (( i=0 ; $i<=20 ; i++ )) ; do
	echo $i;
done

# w bardziej "shellowym" stylu:
for i in `seq 0 20`; do
	echo $i;
done

# pętla for po liście rozdzielanej spacjami
# wypisanie nazw wszystkich plików z /tmp
for nazwa in /tmp/* ; do
	echo $nazwa;
done

# pętla while z read (po liniach pliku)
cat /etc/fstab | while read slowo reszta; do
	echo $reszta;
done
# powyższa pętla wypisze po kolei wszystkie
# wiersze pliku przekazanego przez stdin
# (cat nazwa_pliku |) z pominięciem
# pierwszego słowa (które wczytywane było do
# zmiennej slowo)
# domyślnym separatorem pól dla komendy read 
# jest dowolny ciąg białych znaków (spacji i
# tabulatorów) można go zmienić przy pomocy
# zmiennej IFS:
IFS=:
while read a b c d; do
	echo $c
done < /etc/passwd
unset IFS

# Należy mieć na uwadze, że w konstrukcjach typu
# while read, pętla while uruchamiana może być w
# procesie potomnym obecnej powłoki.
# Efektem tego jest iż w niektórych przypadkach
# wykonywane modyfikacje zmiennych wewnątrz
# takiej pętli nie będą widoczne poza nią.


# instruikcja if - else
if [ "$xx" = "kot" -o "$xx" = "pies" ]; then
	echo  "kot lub pies";
elif [ "$xx" = "ryba" ];  then
	echo  "ryba"
else
	echo  "coś innego"
fi

# spacje wokół i wewnątrz nawiasów kwadratowych
# przy warunku są istotne składniowo, zawartość
# nawiasów kwadratowych to tak naprawdę
# argumenty dla komendy test, zatem wywołanie:
#  if [ "$xx" = "ryba" ];  then
# jest równoważne:
#  if test "$xx" = "ryba";  then
# a więcej na temat warunków można znaleźć w:
#  man test

# jako warunek może wystąpić dowolne polecenie
# wtedy sprawdzany jest jego kod powrotu
# 0 oznacza prawdę / zakończenie sukcesem
# wartość nie zerowa fałsz / błąd
if grep '^root:' /etc/passwd > /dev/null; then
	echo /etc/passwd zawiera użytkownika root;
fi

# istnieje możliwość skróconego zapisu warunków
# z użyciem łączenia instrukcji przy pomocy:
#  && wykonaj instrukcję występująca po prawej
#     gdy poprzednia zwróciła zero (true)
#  || (wykonaj instrukcję występująca po prawej
#     gdy poprzednia zwróciła nie zero -- false
[ "$xx" = "ryba" ] && echo '$xx = to ryba'
grep '^root:' /etc/passwd > /dev/null && \
  echo /etc/passwd zawiera użytkownika root;

# instrukcja case
# (w odróżnieniu od switch z C obsługuje napisy)
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

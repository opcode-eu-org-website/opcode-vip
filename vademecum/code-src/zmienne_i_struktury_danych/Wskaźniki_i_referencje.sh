
# w Bashu nie ma operacji na wskaźnikach ale podobną funkcję w pewnych wypadkach
# może pełnić zmienna zawierająca nazwę innej zmiennej

A='tekst do wypisania, $SHELL, `ls -d`'
B="A"

# proste podejście typu echo ${$B} (działające np. w PHP) nie zadziała,
# ale można to zrobić na kilka innych sposobów:

C=${!B}; # ta metoda nie działa w czystym sh
echo $C

# Polecenie wbudowane `eval` pozwala na wykonanie przekazanych do niego argumentów jako
# polecenie shellowe. Zapewnia ono podstawienie występujących w tym napisie zmiennych, itd.

# Polecenia tego można użyć np. do z wartości zmiennej, której nazwę mamy w innej zmiennej
# (zamiast ${!x}, które nie jest dostępne w czystym sh):

C=$( eval "echo \$$B" )
echo $C

# lub prościej (bo istotne jest działanie eval na \$$B
eval C="\$$B"
echo $C


# Jeżeli chcielibyśmy aby kod znajdujący się w zmiennej `A` także został przetworzony
# (podstawiona wartość zmiennej oraz output komendy ls), możemy użyć eval dwukrotnie:
C=$( eval eval "echo \$$B" )
echo $C

# Jak widać `eval` powoduje wykonywanie poleceń zawartych w napisie zatem należy zachować
# ostrożność przy jego użyciu na napisach nieznanego pochodzenia/autorstwa.


# Innym poleceniem umożliwiającym podstawienie wartości zmiennych w jakimś napisie jest envsubst.
# W odróżnieniu od eval nie wykonuje on podanego kodu, a jedynie przetwarza napis
# podstawiając wartości zmiennych (zatem jest bezpieczniejsze przy przetwarzaniu danych
# niewiadomego pochodzenia). Jako że jest to zewnętrzny program używane zmienne
# muszą być dla niego dostępne, czyli muszą być wyeksportowane.

export A
C=$(echo "\$$B" | envsubst)
echo $C

# x jest eksportowane, zatem będzie podstawione
# y nie jest wyeksportowane więc będzie zastąpione napisem pustym
x=12
D='tekst, ${x}, $SHELL, $x, $y, `ls -d`'
C=`export x; echo $D | envsubst`
echo $C


# zmienna może przechowywać komendę / nazwę
# funkcji do wykonania
x=ls

$x /tmp

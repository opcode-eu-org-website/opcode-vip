
# w Bashu nie ma operacji na wskaźnikach
# ale podobną funkcję w pewnych wypadkach
# może pełnić zmienna zawierająca nazwę
# innej zmiennej

A='tekst do wypisania, $HOME, `ls`';
B="A";

# proste podejście typu echo ${$B}
# (działające np. w PHP) nie zadziała,
# ale można to zrobić na kilka innych sposobów:

C=${!B}; # ta metoda nie działa w czystym sh
echo $C

export A
C=$(echo "\$$B" | envsubst)
# ta metoda wymaga zewnętrznego polecenia
# envsubst i wyeksporotwania zmiennych
echo $C

C=$( eval "echo \$$B" )
echo $C

# z użyciem większej liczby poleceń eval możemy
# zapewnić także podstawienie kolejnego poziomu
# zmiennych lub wykonanie wpisanych w nich poleceń
C=$( eval eval "echo \$$B" )
echo $C


# zmienna może przechowywać komendę / nazwę
# funkcji do wykonania
x=ls

$x /tmp

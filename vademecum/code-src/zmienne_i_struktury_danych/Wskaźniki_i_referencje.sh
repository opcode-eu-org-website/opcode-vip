
# w Bashu nie ma operacji na wskaźnikach
# ale podobną funkcję w pewnych wypadkach
# może pełnić zmienna zawierająca nazwę
# innej zmiennej

A="tekst do wypisania";
B="A";

# proste podejście typu echo ${$B}
# (działające np. w PHP) nie zadziała,
# ale można to zrobić na kilka innych sposobów:

C=${!B};
echo $C

C='eval "echo \$$B"';
D=`eval "$C"`
echo $D

C=$(C='eval "echo \$$B"'; eval $C);
echo $C

# zmienna może przechowywać komendę / nazwę
# funkcji do wykonania
x=ls

$x /tmp

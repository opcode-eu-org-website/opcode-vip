
# Jeżeli mamy w zmiennej nazwę polecenia do wykonania
# to możemy je wykonać uruchamiając po prostu tą zmienną:

a="echo"
$a ABC

# Możemy nawet uruchamiać polecenia które mamy zapisane
# w zmiennej wraz z opcjami i argumentami:

a="echo -e abc\ndef ..."
$a ABC

# Metoda ta nie pozwala jednak na podstawianie wartości zmiennych występujących
# w napisie w momencie uruchamiania go, nie pozwala też na umieszczenie w napisie
# wielu poleceń rozdzielanych np. średnikami.

# Warto zauważyć że cudzysłowy wokół argumentów zachowują się w tym wypadku inaczej
# Są one wypisywane tak jakby były częścią argumentu

a='echo ppp; echo "xxx"'
$a

# To zachowanie można zmienić używając polecenia eval

eval $a

# używając eval kod zawarty w zmiennej może także odwoływać się do zmiennych
# oraz ustawiać wartości innych zmiennych

a='echo "ppp"; b="ooo"'
eval $a
echo $b

# eval jest także bardzo pomocny gdy w zmiennej mamy zapisany ciąg argumentów jakiegoś polecenia
# który zawiera znaki specjalne oraz zabezpieczające je cudzysłowy

wypisz_argumenty() { i=0; for x in "$@"; do i=$(($i+1)); echo $i: $x; done; echo; }

args="a1 'a2' \"a3\" b 1 'b 2' \"b 3\" 'c \"11\"' 'c \"2 2\"'"
wypisz_argumenty $args
eval wypisz_argumenty $args


# Dzięki użyciu eval możemy też budować kod bashowy (np. fragmenty konstrukcji case)
# w oparciu o zawartość zmiennych:

x=a

LISTA_WYBORU="a) echo AA;; b) echo BB;;"
INNE="e|f"

eval "case $x in
	$LISTA_WYBORU
	c) echo "CCC";;
	$INNE) echo inne;;
esac"


# Wykonywanie obliczeń wartości wyrażenia matematycznego zawartego w zmiennej
# realizowane jest z użyciem standardowego operatora $(( ))

a="13+17"
b=$(( $a ))
echo $b

# alternatywnie może być realizowane przez zewnętrzny kalkulator np.:

b=`echo $a | bc`
echo $b

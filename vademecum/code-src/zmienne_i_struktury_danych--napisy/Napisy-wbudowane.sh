
# Wbudowane przetwarzanie napisów w bashu
# opiera się na odwołaniach do zmiennych w postaci ${}:

# ${zmienna:-"napis"} zwróci napis gdy zmienna nie jest zdefiniowana lub jest pusta
# ${zmienna:="napis"} zwróci napis oraz wykona podstawienie zmienna="napis"
#                     gdy zmienna nie jest zdefiniowana lub jest pusta
# ${zmienna:+"napis"} zwróci napis gdy zmienna jest zdefiniowana i nie pusta
a=""; b=""; c=""
echo ${a:-"aa"} ${b:="bb"} ${c:+"cc"}
echo $a $b $c
a="x"; b="y"; c="z"
echo ${a:-"aa"} ${b:="bb"} ${c:+"cc"}
echo $a $b $c

# ${#str}    zwróci długość napisu w zmiennej str
# ${str:n}   zwróci pod-napis ze zmiennej str od pozycji n do końca
# ${str:n:m} zwróci pod-napis ze zmiennej str od pozycji n o długości m
x=abcdefg
echo ${#x} ${x:2} ${x:0:3} ${x:0:$((${#x}-2))}

# ${str#"ab"} zwróci wartość $str z obciętym "ab" z początku
# ${str%"fg"} zwróci wartość $str z obciętym "fg" z końca
echo ${x#"abc"} ${x%"efg"}
echo ${x#"ac"}  ${x%"eg"}
# w napisach do obcięcia możliwe jest stosowanie shellowych
# znaków uogólniających, czyli *, ?, [abc], itd
# operator # i % dopasowują minimalny napis do usunięcia
# operatory ## i %% dopasowują maksymalny napis do usunięcia
x=abcd.e.fg
echo ${x#*.} ${x##*.} ${x%.*} ${x%%.*}

# ${str/"n1"/"n2"}  zwróci wartość $str z zastąpionym pierwszym wystąpieniem n1 przez n2
# ${str//"n1"/"n2"}  zwróci wartość $str z zastąpionymi wszystkimi wystąpieniami n1 przez n2
y="aa bb cc bb dd bb ee"
echo ${y/"bb"/"XX"}
echo ${y//"bb"/"XX"}

# W napisach do obcięcia możliwe jest stosowanie shellowych znaków uogólniających,
# czyli `*`, `?`, ```[abc]```, itd operator `#` i `%` dopasowują minimalny napis do usunięcia,
# natomiast operatory `##` i `%%` dopasowują maksymalny napis do usunięcia.

# Należy pamiętać że wiele z powyższych zapisów jest rozszerzeniami basha
# niedostępnymi w podstawowej składni sh.

# Możliwe jest także korzystanie z wyrażeń regularnych.

# Polecenie expr match $x 'wr1\(wr2\)wr3' zwróci na stdout (wypisze)
# część $x pasującą do wyrażenia regularnego wr2
# wyrażenia regularne wr1 i wr2 pozwalają na określanie części napisu do odrzucenia.
# Alternatywną składnią jest expr $x : 'wr1\(wr2\)wr3'

# Przykład użycia jednego i drugiego wariantu składni
# do podziału napisu na część przed i po znaku równości:

z="ab=cd"
expr match $z '^\([^=]*\)='
expr $z : '^[^=]*=\(.*\)$'

# Możliwe jest też sprawdzanie dopasowań wyrażeń regularnych poprzez
# (uwaga na brak cudzysłowów wokół wyrażenia regularnego):
[[ "$z" =~ ^([^=]*)= ]] && echo "OK"

# Możliwe jest także zaawansowane formatowanie napisów, konwertowanie liczb na napisy,
# w tym wypisywanie w różnych systemach liczbowych przy pomocy `printf`
# (instrukcja `printf` ma składnię opartą na tej funkcji z C,
# interpretuje ona także liczby zmiennoprzecinkowe):

printf "0o%o %d 0x%x\n" 0xf 010 3

# do bardziej zaawansowanych operacji
# mogą być przydatne także polecenia:
#  grep  diff  sed  awk
#  join  comm  paste

# należy też pamiętać o różnicy w działaniu echo "$a" i
# echo $a w przypadku gdy zmienna a zawiera znaki nowej linii:
#  - w pierwszym wypadku będą traktowane jako znaki nowej linii
#  - w drugim jako spacje



# ${zmienna:-"napis"} zwróci napis gdy
#   zmienna nie jest zdefiniowana lub jest pusta
# ${zmienna:="napis"} zwróci napis
#   oraz wykona podstawienie zmienna="napis" gdy
#   zmienna nie jest zdefiniowana lub jest pusta
# ${zmienna:+"napis"} zwróci napis gdy
#   zmienna jest zdefiniowana i nie pusta
a=""; b=""; c=""
echo ${a:-"aa"} ${b:="bb"} ${c:+"cc"}
echo $a $b $c
a="x"; b="y"; c="z"
echo ${a:-"aa"} ${b:="bb"} ${c:+"cc"}
echo $a $b $c

# ${#str}    zwróci długość napisu w zmiennej str
# ${str:n}   zwróci pod-napis $str od n do końca
# ${str:n:m} zwróci pod-napis $str od n o długości m
x=abcdefg
echo ${#x} ${x:2} ${x:0:3} ${x:0:$((${#x}-2))}

# ${str#"ab"} zwróci $str z obciętym "ab" z początku
# ${str%"fg"} zwróci $str z obciętym "fg" z końca
echo ${x#"abc"} ${x%"efg"}
echo ${x#"ac"}  ${x%"eg"}
# w napisach do obcięcia możliwe jest stosowanie shellowych
# znaków uogólniających, czyli *, ?, [abc], itd
# operator # i % dopasowują minimalny napis do usunięcia
# operatory ## i %% dopasowują maksymalny napis do usunięcia
x=abcd.e.fg
echo ${x#*.} ${x##*.} ${x%.*} ${x%%.*}

# ${str/"n1"/"n2"}  zwróci $str z zastąpionym
#   pierwszym wystąpieniem n1 przez n2
# ${str//"n1"/"n2"}  zwróci $str z zastąpionymi
#   wszystkimi wystąpieniami n1 przez n2
y="aa bb cc bb dd bb ee"
echo ${y/"bb"/"XX"}
echo ${y//"bb"/"XX"}

# polecenie expr match $x 'wr1\(wr2\)wr3'
# zwróci część $x pasującą do wyrażenia regularnego wr2
# wyrażenia regularne wr1 i wr2 pozwalają na
# określanie części napisu do odrzucenia
# alternatywną składnią jest expr $x : 'wr1\(wr2\)wr3'
z="ab=cd"
expr match $z '^\([^=]*\)='
expr $z : '^[^=]*=\(.*\)$'

# możliwe jest też sprawdzanie dopasowań wyrażeń
# regularnych poprzez (uwaga na brak cytowania):
[[ "$z" =~ ^([^=]*)= ]] && echo "OK"

# wypisywanie w różnych systemach liczbowych
printf "0o%o %d 0x%x\n" 0xf 010 3

# do bardziej zaawansowanych operacji
# mogą być przydatne także polecenia:
#  grep  diff  sed  awk
#  join  comm  paste

# należy też pamiętać o różnicy w działaniu echo "$a" i
# echo $a w przypadku gdy zmienna a zawiera znaki nowej linii:
#  - w pierwszym wypadku będą traktowane jako znaki nowej linii
#  - w drugim jako spacje

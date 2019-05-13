
# obsługa napisów w bash'u przy pomocy standardowych komend POSIXa

# jako że większość operacji bashowych wiąże się z 
# uruchamianiem zewnętrznych programów to także
# przetwarzanie napisów może być realizowane w ten sposób

a="aąbcć 123"

# obliczanie długości napisu w znakach, w bajtach i ilości słów w napisie
echo -n $a | wc -m
echo -n $a | wc -c
echo -n $a | wc -w

# obliczanie ilości linii (dokładniej ilości znaków nowej linii)
wc -l < /etc/passwd

# wypisanie 5 pola (rozdzielanego :) z pliku /etc/passwd  z eliminacją
# pustych linii oraz linii złożonych tylko ze spacji i przecinków
cut -f5 -d: /etc/passwd | grep -v '^[ ,]*$'
# komenda cut wybiera wskazane pola, opcja -d określa separator

# alternatywne podejście z użyciem AWK
awk -F: '$5 !~ "^[ ,]*$" {print $5}' /etc/passwd

# awk daje duże możliwości przy przetwarzaniu tego typu tekstowych baz
# danych ... możemy np. wypisywać wypisywać pierwsze pole w oparciu
# o warunki nałożone na inne:
awk -F: '$5 !~ "^[ ,]*$" && $3 >= 1000 {print $1}' /etc/passwd

# jak widać w powyższych przykładach do poszczególnych pól odwołujemy
# się poprzez $n, gdzie n jest numerem pola, $0 oznacza cały rekord

# program dla każdego rekordu przetwarza kolejne instrukcje postaci
# "warunek { komendy }", instrukcji takich może być wiele w programie
# (przetwarzane są kolejno) komenda "next" kończy przetwarzanie danego rekordu

# separator pola ustawiamy opcją -F (lub zmienną FS) domyślnym separatorem
# pola jest dowolny ciąg spacji i tabulatorów (w odróżnieniu od cut
# separator może być wieloznakowym napisem lub wyrażeniem regularnym)
# domyślnym separatorem rekordu jest znak nowej linii
# (można go zmienić zmienną RS)

# awk jest prostym językiem programowania obsługującym podstawowe pętle
# i instrukcje warunkowe oraz funkcje wyszukujące i modyfikujące napisy
echo "aba aab bab baa bba bba" | awk '{
	for (i=1; i<=NF; ++i) {       # dla każdego pola w rekordzie
		if(i%2==0)                # jeżeli jego numer jest parzysty
			gsub("b+", "B", $i);  # zastąp wszystkie ciągi b pojedynczym B
		ii = index($i, "B")       # wyszukaj pozycję pod-napisu B
		if (ii)                   # jeżeli znalazł to wypisz pozycję i pod-napis
			printf("# %d %s\n", ii, substr($i, ii))  # od tej pozycji do końca
	}
	print $0
}'

# AWK obsługuje także tablice asocjacyjne pozwala to np. policzyć
# powtórzenia słów
echo "aa bb aa ee dd aa dd" | awk '
	BEGIN {RS="[ \t\n]+"; FS=""}
	{slowa[$0]++}
	{printf("rekord: %d done\n", NR)}
	END {for (s in slowa) printf("%s: %s\n", s, slowa[s])}
'
# podobny efekt możemy uzyskać stosując "uniq -c" (który wypisuje unikalne
# wiersze wraz z ich ilością) na odpowiednio przygotowanym napisie
# (spacje zastąpione nową linią, a linie posortowane)
echo "aa bb aa ee dd aa dd" | tr ' ' '\n' | sort | uniq -c
# jednak rozwiązanie awk można łatwo zmodyfikować aby wypisywało pierwsze
# wystąpienie linii bez sortowania pliku


# inną bardzo przydatną komendą jest sed pozwala ona m.in na zastępowanie
# wyszukiwanego na podstawie wyrażenia regularnego tekstu innym
echo "aa bb cc bb dd bb ee" | sed -e 's#\([bc]\+\) \([bc]\+\)#X-\2-X#g'

# sedowe polecenie s przyjmuje 3 argumenty (oddzielane mogą być dowolnym
# znakiem który wystąpi za s), pierwszy to wyszukiwane wyrażenie, drugi
# tekst którym ma zostać zastąpione, a trzeci gdy jest g to powoduje
# zastępowanie wszystkich wystąpień a nie tylko pierwszego

# należy zwrócić uwagę na różnicę w składni wyrażenia regularnego polegającą
# na poprzedzaniu (, ) i + odwrotnym ukośnikiem aby MIAŁY znaczenie specjalne

# sed z opcją -i i wskazaniem pliku modyfikuje zawartości tego pliku
# pozwala to na łatwe stworzenie funkcji rekurencyjnego zastępowania:
rreplace() {
	if [ $# -ne 2 ]; then
		echo USAGE: $1 str1 str2
		return
	fi
	grep -R "$1" . | cut -f 1 -d: | uniq | while read f; do
		[ -L $f ] || sed -e "s#$1#$2#g" -i $f;
	done;
}

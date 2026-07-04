
# obsługa napisów w bash'u przy pomocy standardowych komend POSIXa

# Jako że większość operacji wykonywanych w powłoce takiej jak bash
# wiąże się z uruchamianiem zewnętrznych programów,
# to także przetwarzanie napisów może być realizowane w ten sposób.
# Opiera się na tym jedno z podejść do obsługi napisów w bashu,
# którym jest korzystanie z standardowych komend POSIX,
# takich jak `grep`, `cut`, `sed`.

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

# Awk jest interpreterem prostego skryptowego języka umożliwiającym przetwarzanie
# tekstowych baz danych postaci *linia == rekord*, gdzie pola oddzielane ustalonym
# separatorem (można powiedzieć że łączy funkcjonalność komend takich jak
# grep, cut, sed z prostym językiem programowania).

# Awk daje duże możliwości przy przetwarzaniu tego typu tekstowych baz danych:
# możemy np. wypisywać pierwsze pole w oparciu o warunki nałożone na inne:

awk -F: '$5 !~ "^[ ,]*$" && $3 >= 1000 {print $1}' /etc/passwd

# Jak widać w powyższych przykładach do poszczególnych pól odwołujemy
# się poprzez $n, gdzie n jest numerem pola, $0 oznacza cały rekord

# Program dla każdego rekordu przetwarza kolejne instrukcje postaci
# `warunek { komendy }`, instrukcji takich może być wiele w programie
# (przetwarzane są kolejno), komenda `next` kończy przetwarzanie danego rekordu.

# Separator pola ustawiamy opcją -F (lub zmienną FS), domyślnym separatorem
# pola jest dowolny ciąg spacji i tabulatorów (w odróżnieniu od cut
# separator może być wieloznakowym napisem lub wyrażeniem regularnym).
# Domyślnym separatorem rekordu jest znak nowej linii (można go zmienić zmienną RS).

# Awk jest prostym językiem programowania obsługującym podstawowe pętle
# i instrukcje warunkowe oraz funkcje wyszukujące i modyfikujące napisy:
echo "aba aab bab baa bba bba" | awk '{
	for (i=1; i<=NF; ++i) {       # dla każdego pola w rekordzie
		if (i%2==0)               # jeżeli jego numer jest parzysty
			gsub("b+", "B", $i);  # zastąp wszystkie ciągi b pojedynczym B
		ii = index($i, "B")       # wyszukaj pozycję pod-napisu B
		if (ii)                   # jeżeli znalazł to wypisz pozycję i pod-napis
			printf("# %d %s\n", ii, substr($i, ii))  # od tej pozycji do końca
			# UWAGA: AWK liczy elementy w napisie od 1 a nie od 0
	}
	print $0
}'

# AWK obsługuje także tablice asocjacyjne pozwala to np. policzyć powtórzenia słów:
echo "aa bb aa ee dd aa dd" | awk '
	BEGIN {RS="[ \t\n]+"; FS=""}
	{slowa[$0]++}
	# może być kilka bloków {} pasujących do rekordu
	# jeżeli nie użyjemy next przetworzone zostaną wszystkie
	{printf("rekord: %d done\n", NR)}
	END {for (s in slowa) printf("%s: %s\n", s, slowa[s])}
'
# Podobny efekt możemy uzyskać stosując "uniq -c" (który wypisuje unikalne
# wiersze wraz z ich ilością) na odpowiednio przygotowanym napisie
# (spacje zastąpione nową linią, a linie posortowane):

echo "aa bb aa ee dd aa dd" | tr ' ' '\n' | sort | uniq -c

# Jednak rozwiązanie awk można łatwo zmodyfikować aby wypisywało pierwsze
# wystąpienie linii bez sortowania pliku.

# Innym użytecznym zastosowaniem AWK może być wypisanie pliku
# bez linii pasujących do wzorca oraz linii poprzednich:

echo -e "aa\nbb\nWZORZEC\ncc" | awk'{
	# dla linii pasującej do wzorca ustawiamy flagę print_last na zero
	# i przechodzimy do następnej linii
	/WZORZEC/ {print_last=0; next}
	
	# jeżeli flaga print_last jest nie zero wypisujemy zapamiętaną poprzednią linię
	print_last == 1 {print last}
	
	# zapamiętujemy bieżącą linię do wypisania przy przetwarzaniu kolejnej
	# (jeżeli nie będzie pasować do wzorca)
	{last=$0; print_last=1}
	
	# jeżeli osiągneliśmy koniec pliku i mamy linię do wypisania to ją wypisujemy
	END {if (print_last == 1) print last}
}'

# AWK pozwala także na definiowanie funkcji:

awk 'function f(x) {return 2*x} { print f($1+$2) }'


# Inną bardzo przydatną komendą jest sed pozwala ona m.in na zastępowanie
# wyszukiwanego na podstawie wyrażenia regularnego tekstu innym:
echo "aa bb cc bb dd bb ee" | sed -e 's#\([bc]\+\) \([bc]\+\)#X-\2-X#g'

# Sedowe polecenie s przyjmuje 3 argumenty (oddzielane mogą być dowolnym znakiem,
# który wystąpi za `s`), pierwszy to wyszukiwane wyrażenie, drugi to tekst
# którym ma zostać zastąpione, a trzeci to flagi, jeżeli podano tam `g`
# to zastępowane bądą wszystkie wystąpienia a nie tylko pierwsze.

# Należy zwrócić uwagę na różnicę w składni wyrażenia regularnego polegającą
# na poprzedzaniu `(`, `)` i `+` odwrotnym ukośnikiem aby miały znaczenie specjalne
# (aby tego uniknąć należy włączyć obsługę ERE w sed poprzez opcję `-E`).

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

# Innymi przydatnymi komendami przetwarzającymi (specyficznej postaci) napisy są
# polecenia `basename` i `dirname`. Służą one do uzyskania nazwy najgłębszego elementu
# ścieżki oraz ścieżki bez tego najgłębszego elementu. Zobacz wynik działania:

basename /proc/sys/net/core/
dirname /proc/sys/net/core/

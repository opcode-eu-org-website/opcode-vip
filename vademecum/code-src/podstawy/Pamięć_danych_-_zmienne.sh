
# Określanie typów zmiennych w bashu odbywa się na podstawie wartości znajdującej się w zmiennej.
# Zasadniczo wszystkie zmienne są napisami, a interpretacja typu ma miejsce przy ich użyciu
# (a nie przy tworzeniu). Obsługiwane są liczby całkowite oraz napisy,
# ale bash nie posiada wbudowanej obsługi liczb zmiennoprzecinkowych.

zmiennaA=-91
zmiennaB="qa   z"
zmiennaC=98.6234 # to będzie traktowane jako napis a nie liczba

# Brak spacji pomiędzy nazwą zmiennej a znakiem równości jest wymogiem składniowym.

# Wynika to ze znaczenia spacji w składni powłoki.
# Spacja oddziela nazwy poleceń i argumenty od siebie, czyli pełni istotną funkcję
# składniową, odpowiadającą nawiasom okrągłym i przecinkom, używanym do oddzielania
# nazwy funkcji i argumentów od siebie, z wielu innych języków programowania.

# Odwołanie do zmiennej odbywa się z użyciem znaku dolara ($), po którym występuje
# nazwa zmiennej. Nazwa może być ujęta w klamry, ale nie musi (jest to przydatne gdy
# nie chcemy dawać spacji pomiędzy nazwą zmiennej a np. fragmentem napisu). Rozwijaniu
# ulegają nazwy zmiennych znajdujące się w napisach umieszczonych w podwójnych cudzysłowach.

# Umieszczenie odwołania do zmiennej w cudzysłowach zabezpiecza białe znaki
# (spacje nowe linie) przy przekazywaniu do funkcji i programów (w tym przy
# przekazywaniu do echo, celem wypisywania).

# Użycie apostrofów wyłącza interpretację dolara jako znaku specjalnego (odwołania do zmiennej).

echo  $zmiennaA ${zmiennaA}AA
echo "$zmiennaA ${zmiennaA}AA"
echo '$zmiennaA ${zmiennaA}AA'

#
# Zmienna nie zdefiniowana
#

# Odwołaniu do nie zdefiniowanej zmiennej nie zgłaszane jako błąd,
# taka zmienna ma wartość napisu pustego.

echo "AAA $niezdefiniowana BBB"

# Należy jednak pamiętać że taki napis pusty będzie inaczej traktowany gdy znajduje się
# wewnątrz cudzysłowów a inaczej gdy nie (wtedy jest pomijany jako argument poleceń).

printf "> %s < %s\n" $niezdefiniowana BBB
printf "> %s < %s\n" "$niezdefiniowana" BBB

# Do wypisywania wartości zmiennych może być użyte także polecenie `printf`
# będące odpowiednikiem funkcji języka C o tej samej nazwie

printf "%.2f\n" $zmiennaC

#
# Zmienne środowiskowe
#

# Jeżeli chcemy aby zmienna była widoczna przez programy uruchamiane z danej powłoki
# (w tym przez kolejne instancje bash'a, odpowiedzialne np. za wykonywanie kodu skryptu
# uruchamianego z pliku) należy ją wyeksportować za pomocą polecenia:

export zmiennaA

# Do polecenia `export` przekazujemy nazwę zmiennej a nie jej wartość,
# więc nie używamy znaku dolara.

# Taka zmienna jest dostępna jako zmienna środowiskowa dla wszystkich potomków tej powłoki.

# Zmienne środowiskowe mogą być także ustawiane bez użycia
# `export` dla pojedynczego nowego programu poprzez podanie
# ich nazw i wartości przed nazwą polecenia:

ABCD=678 bash -c 'echo $ABCD'
ABCD=135 EFG=098 bash -c 'echo $ABCD $EFG'
echo $ABCD

# Są one jedynie widoczne w tak uruchomionym procesie potomnym
# (nie mogą być użyte w bieżącej powłoce, czy jako jako argumenty w linii poleceń).
# Dlatego w powyższych przykładach wywoływana jest nowa powłoka,
# która korzysta z tak ustawionych zmiennych.

# Takie ustawianie zmiennych jest szczególnie przydatne gdy
# chcemy uruchomić pojedyncze polecenie w zmienionym
# środowisku - np. polecenie date w innej strefie czasowej:

TZ=America/New_York date

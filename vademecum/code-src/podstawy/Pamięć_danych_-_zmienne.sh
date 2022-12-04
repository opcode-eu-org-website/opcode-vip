
# dynamiczne typowanie - typ określany jest
# na podstawie wartości znajdującej się w zmiennej
#
# zasadniczo wszystkie zmienne są napisami, a interpretacja
# ma miejsce przy ich użyciu a nie przy tworzeniu

# obsługiwane liczby całkowite oraz napisy
# brak obsługi liczb zmiennoprzecinkowych
#
# brak spacji pomiędzy nazwą zmiennej a znakiem równości
# w operacji przypisania jest wymogiem składniowym

zmiennaA=-91
zmiennaB="qa   z"
zmiennaC=98.6 # to będzie traktowane jako napis a nie liczba

# Odwołanie do zmiennej odbywa się z użyciem znaku dolara,
# po którym występuje nazwa zmiennej.  Nazwa może być ujęta
# w klamry. Rozwijaniu ulegają nazwy zmiennych znajdujące
# się w napisach umieszczonych w podwójnych cudzysłowach.

# Umieszczenie odwołania do zmiennej w podójnych
# cudzysłowach zabezpiecza białe znaki (spacje nowe linie)
# przy przekazywaniu do funkcji i programów (w tym przy 
# przekazywaniu do echo, celem wypisywania).

echo  $zmiennaA ${zmiennaA}AA
echo "$zmiennaA ${zmiennaA}AA"
echo '$zmiennaA ${zmiennaA}AA'

# Jeżeli chcemy aby zmienna była widoczna przez programy
# uruchamiane z naszej powłoki należy ją wyeksportować za
# pomocą polecenia `export zmienna` (nazwa bez znaku dolara).

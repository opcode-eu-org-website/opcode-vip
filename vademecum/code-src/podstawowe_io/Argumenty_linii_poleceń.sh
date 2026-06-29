# podstawowa obsługa argumentów linii poleceń dla skryptów shellowych
# jest identyczna jak obsługa argumentów dla funkcji:
# $1 - pierwszy argument, $2 - drugi, itd
# $@ - wszystkie, $# - liczba argumentów
# w $0 znajduje się nazwa/ścieżka poprzez jaką skrypt został wywołany

# przetwarzania opcji w stylu unixowym (z myślnikami)
# można zrealizować z użyciem narzędzia getopt

# przetworzenie argumentów określonych w wywołaniu getopt
# dalsze argumenty dostępne są w $1, $2, itd po zakończeniu pętli
# : -> poprzedzająca opcja wymaga argumentu
# :: -> poprzedzająca opcja może mieć argument
# uwaga o ile wymagane argumenty mogą być rozdzielane od opcji spacją
# o tyle opcjonalne nie (krótkie należy podawać zaraz po opcji,
# długie rozdzielając =)
eval set -- "`getopt -o xy:z:: -l opcja-x,opcja-y:,opcja-z:: -- "$@"`"
while true; do
  case $1 in
    -x|--opcja-x) echo "X"; shift 1;;
    -y|--opcja-y) echo "Y, argument \`$2'"; shift 2;;
    -z|--opcja-z) echo "Z, argument \`$2'"; shift 2;;
      # tuataj $2 może być pusty (gdy nie podano), ale jest zdefiniowany
    --) shift; break;;
  esac
done

# inną komendą mogącą służyć przetwarzaniu opcji skryptu jest getopts

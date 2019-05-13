
import argparse

# parser agumentów linii poleceń
# do argumentów można się też dostawać bezpośrednio poprzez sys.argv:
#   len(sys.argv) - ilość elementów tej tablicy
#   str(sys.argv[0]) - napis odpowiadający nazwie wywołania programu
#   str(sys.argv[1]) - napis odpowiadający pierwszemu argumentowi programu

parser = argparse.ArgumentParser(description='Opis programu')
parser.add_argument(
	'ARG', default='ABC', nargs='?',
	help='argument pozycyjny (opcjonalny z wartością domyślną)'
)
parser.add_argument(
	'-v', "--verbose", action="store_true",
	help='opcja typu przełącznik'
)
parser.add_argument(
	"--input", action="store",
	help='opcja z argumentem'
)

parser.add_argument(
	"--vector", action="store", metavar='V', nargs='*',
	help='opcja z wieloma argumentami'
)
args = parser.parse_args()

print(args)

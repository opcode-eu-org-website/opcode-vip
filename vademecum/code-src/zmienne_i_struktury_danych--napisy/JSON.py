
import json
from pprint import pprint

a='''{
"info": "bbb",
"ver": 31,
"d": [
	{"a": 21, "b": {"x": 1, "y": 2}, "c": [9, 8, 7]},
	{"a": 17, "b": {"x": 6, "y": 7}, "c": [6, 5, 4]}
]
}'''

# interpretacja napisu jako zbioru danych w formacie json
d = json.loads(a)

# wypisanie zbioru danych
pprint(d) # pprint ładnie formatuje złożone zbiory danych

# jak widać jest to zagnieżdżona struktura list i słowników
# odpowiadająca 1 do 1 temu co było w napisie

# dostęp do poszczególnych elementów: "po pythonowemu"
print(d["d"][1]["b"])
print(d["d"][1]["b"]["x"])
print(d["d"][1]["c"][1])

# przygotowaniem nowego zbioru danych
b={'aa': 'pp', 'b': [3,4,5], 'c':d}
b['e']="test"
b['f']={'a':1, 'b':2}

# wygenerowanie json-owego tekstu w oparciu o niego
c=json.dumps(b,indent=1,ensure_ascii=False)
print(c)

# dla porównania:
pprint(b)

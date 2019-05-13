
m = { "ab" : 11, "cd" : "xx" }
x = "e"
m[x] = True;

# pobranie samych kluczy
for k in m:
	print (k, "=>", m[k])

# sprawdzenie istnienia 
if "ab" in m:
	print ("jest ab")
	# usunięcie elementu
	del m['ab']

# modyfikacja wartosci
m["cd"] = "oi"

# pobranie par klucz wartosc
for k,v in m.items():
	print (k, "=>", v)

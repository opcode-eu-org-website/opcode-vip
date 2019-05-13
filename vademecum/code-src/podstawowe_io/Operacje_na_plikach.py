
import os

# sprawdzenie czy plik istnieje
if os.path.isfile("/tmp/abc.txt"):
	print("istnieje")
else:
	print("nie istnieje")

# listowanie katalogu i sprawdzanie typów
dl = os.listdir("/tmp/")
print (dl)

for f in dl:
	if os.path.isfile(f):
		print("\"" + f + "\" jest plikiem")
	elif os.path.isdir(f):
		print("\"" + f + "\" jest katalogiem")
	else:
		print("\"" + f + "\" jest czymś innym")

# można także rekurencyjnie wraz z podkatalogami
for currDir, dirs, files in os.walk('/tmp'):
	print("podkatalogi \"" + currDir + "\":")
	for d in dirs:
		print("  " + os.path.join(currDir, d))
	
	print("pliki w \"" + currDir + "\":")
	for f in files:
		print("  " + os.path.join(currDir, f))

# zmiana nazwy
os.rename("/tmp/a.txt" "/tmp/b.txt")

# usuwanie
os.remove("/tmp/b.txt")

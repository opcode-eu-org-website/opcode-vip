
# sprawdzenie czy plik istnieje
if [ -f "/tmp/abc.txt" ]; then
	echo "istnieje"
else
	echo "nie istnieje"
fi

# listowanie katalogu i sprawdzanie typów
for f in /tmp/*; do
	if [ -f "$f" ]; then
		echo "\"$f\" jest plikiem"
	elif [ -d "$f" ]; then
		echo "\"$f\" jest katalogiem"
	else
		echo "\"$f\" jest czymś innym"
		# np. kolejką lub urządzeniem ...
	fi
done

# alternatywne listowanie katalogu
ls /tmp | while read f; do
	echo "/tmp zawiera: $f"
done

# zmiana nazwy
mv /tmp/a.txt /tmp/b.txt

# usuwanie
rm /tmp/b.txt

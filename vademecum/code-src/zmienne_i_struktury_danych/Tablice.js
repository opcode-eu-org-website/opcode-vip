
var t = ['a b c', 8, 3, 2];

console.log(
	"pierwszy element: " + t[0] + "\n" +
	"długość tablicy: " + t.length + "\n"
);

// usuwamy 2 elementy od pozycji 1
t.splice(1, 2)

// dodajemy nowe elementy
t[5] = "pp";
t[7] = "ww";

// wypisanie wszystkich elementów
for (var i=0; i<t.length; ++i) {
	console.log("t["+ i +"]="+ t[i] +"\n");
}

// za pomocą for..in
for (var ii in t) {
	console.log("t["+ ii +"]="+ t[ii] +"\n");
}

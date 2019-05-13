
var x = "abcdefg";
var y = "aa bb cc bb dd bb ee";
var z = "qw=rt";

// podstawianie wartości zmiennych w napisie
console.log(`x=${x} y=${y} z=${z}\n`)

function echo(a) {
	// łączenie napisów (lub napisu i czegoś
	// co można skonwertować na napis)
	// z użyciem operatora +
	console.log(a + "\n");
}

// wypisanie długości napisu
echo(x.length);

// wypisanie pod-napisu od 2 do końca
echo(x.substr(2));
// i od 0 (początku) 3 kolejne znaki
echo(x.substr(0, 3));


//  wyszukiwanie
//  pod-napisu "bb" w $y od pozycji 5
echo(y.indexOf("bb", 5));

//  porównywanie
if (x == "abcdefg")
	echo("x == abcdefg");

if (x.search(/[dz]/) > 0) {
	echo("x zawiera d lub z");
}

//  zastępowanie
echo(y.replace("bb", "BB"));
echo(y.replace(/[bc]+/g, "XX"));

// zastępowanie z użyciem podstawienia
// $2 zostanie zastąpione wartością
// pierwszego pod-wyrażenia,
// czyli fragmentu ujętego w nawiasach
console.log(
	z.replace(/^([^=]*)=.*$/, '$1') +
	" = " +
	z.replace(/^[^=]*=(.*)$/, '$1') +
	"\n"
);

var a = 7, b = 0xf, c = 010, d = 0b11;

echo("0b" + a.toString(2))
echo("0o" + b.toString(8))
echo(c.toString())
echo("0x" + d.toString(16))


<?php

$x = "abcdefg";
$y = "aa bb cc bb dd bb ee";
$z = "qw=rt";

# wypisanie długości napisu
echo strlen($x) . "\n";

# wypisanie pod-napisu od 2 do końca
echo substr($x, 2);
# i od 0 (początku) 3 kolejne znaki
echo substr($x, 0, 3) . "\n";

# wyszukiwanie
# pod-napisu "bb" w $y od pozycji 5
echo strpos($y, "bb", 5) . "\n";

# porównywanie
if ($x == "a")
	echo "$x == a\n";

if (substr_compare($x, "de", 3, 2)) {
	echo "2 znakowy pod-napis od";
	echo "pozycji 3 w $x to \"de\"\n";
}

if (preg_match("/[dz]/", $x)) {
	echo "$x zawiera d lub z\n";
}

# zastępowanie
echo str_replace("bb", "BB", $y) . "\n";
echo preg_replace('/[bc]+/', "XX", $y, 2) . "\n";
echo preg_replace('/[bc]+/', "XX", $y) . "\n";

# zastępowanie z użyciem podstawienia
# $2 zostanie zastąpione wartością pierwszego pod-wyrażenia,
# czyli fragmentu ujętego w nawiasach
echo preg_replace('/^([^=]*)=.*$/', '$1', $z);
echo " = ";
echo preg_replace('/^[^=]*=(.*)$/', '$1', $z);
echo "\n";

# wypisywanie w różnych systemach liczbowych
printf("0b%b 0o%o %d 0x%x\n", 7, 0xf, 010, 0b11);

?>

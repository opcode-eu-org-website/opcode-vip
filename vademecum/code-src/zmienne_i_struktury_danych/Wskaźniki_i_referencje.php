
<?php

// w PHP korzystanie z nazwy zmiennej
// przechowywanej w innej zmiennej
// jest jeszcze prostsze:
$a="12";
$b="a";
$c="b";

echo "$a $b $c\n"
echo "${$b} ${$c}\n"
echo "${${$c}}\n"

// możliwe jest także używanie zmiennych
// zawierających nazwy funkcji oraz
// przekazywanie ich do innych funkcji
function fa($z) {
	print($z*3);
	print("\n");
}

$c="fa";
$c(2);

function fb($x, $y) {
	$x($y+2);
}

fb("fa", 1);

?>

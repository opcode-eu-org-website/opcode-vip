
<?php

# funkcja bezargumentowa, zwracająca wartość
function f1() {
	print("AA\n");
	return 5;
}

$a = f1();
print($a);
print("\n");

# funkcja przyjmująca jeden obowiązkowy
# argument oraz dwa opcjonalne
function f2($a, $b=2, $c=0) {
	print($a**$b+$c);
	print("\n");
}

f2(3);
f2(3, 3);


# nieokreślona ilość argumentów pozycyjnych
function f3() {
	$num = func_num_args();
	print("ilość argumentów:\n");
	print( $num );
	print("\n");
	for($i=0; $i<$num; ++$i) {
		print("argument $i: ");
		print(func_get_arg($i));
		print("\n");
	}
}

f3();
f3("a", 1, "c", 5);

# jeden wymagany, jeden opcjonalny
# i nieokreślona ilość dodatkowych
function f4($a, $b="16") {
	# tablica z wszystkimi argumentami
	# jest alternatywną metodą dostępu
	# do wszystkich argumentów w stosunku
	# co do pokazanej w f3()
	$args = func_get_args();
	print_r($args);
}

f4("a", 1, "c", 5);

?>

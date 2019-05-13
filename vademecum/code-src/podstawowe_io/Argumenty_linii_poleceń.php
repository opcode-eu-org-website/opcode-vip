
<?php
/*
możliwe jest używanie php w
trybie command-line jednak ze
względu na specyfikę i podstawowe
zastosowania tego języka jest
to przypadek dość egzotyczny

dlatego też zamiast obsługi opcji
przekazywanych z linii poleceń w
przypadku skryptów php większy
sens ma pokazanie obsługi opcji
przekazywanych w żądaniu HTTP
*/

// wysłanie ciasteczka
// musi być przed wysłaniem
// jakiejkolwiek treści
$val = time();
$val = "tmp $val";
setcookie("Ciasteczko", $val);

echo '<pre>';
echo "wysłałem ciasteczko: $val\n";

// tablica zawierajaca zmienne
// przekazane w adresie URL
echo '$_GET: ';
print_r($_GET);

// tablica zawierajaca zmienne
// przekazane wi treści żądania
echo '$_POST: ';
print_r($_POST);

// tablica zawierajaca zmienne
// przekazane w ciasteczkach
echo '$_COOKIE: ';
print_r($_COOKIE);

echo '</pre>';

?>

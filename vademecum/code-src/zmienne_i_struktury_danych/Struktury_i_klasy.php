
<?php

class NazwaKlasy {
	public $a;
	public $d = "tekst";
	
	# metody składowe
	public function wypisz() {
		echo "a=" . $this->a . " d=" . $this->d . "\n";
	}
	# warto zauważyć jawne odwołania do składowych
	# poprzez zmienną $this
	
	# metody statyczna
	public static function info() {
		echo "INFO\n";
	}
}

// korzystanie z klasy
$k = new NazwaKlasy;
$k->a = 87;
$k->wypisz();

// korzystanie z metod statycznych
NazwaKlasy::info();
// a także poprzez zmienną przechowującą nazwę klasy
$t="NazwaKlasy";
$t::info();

?>

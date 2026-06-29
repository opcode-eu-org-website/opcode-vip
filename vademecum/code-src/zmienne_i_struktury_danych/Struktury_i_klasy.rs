struct NazwaStruktury {
	a: i32,
	d: String,
}

// Definicja stałych i zmiennych statycznych
impl NazwaStruktury {
	const Y: i32 = 7;
	
	// Rust nie pozwala na statyczne zmienne w klasie - poniższe spowoduje błąd
	// static X: i32 = 13;
	
	fn new(aa: i32) -> Self {
		println!("konstruktor");
		return NazwaStruktury {
			a: aa,
			d: String::from("abc ..."),
		}
	}
	
	// Metoda składowa (przyjmuje &self)
	fn wypisz(&self) {
		println!(" a={} d={}", self.a, self.d);
	}
	
	// Metoda statyczna (brak &self w argumentach)
	fn info() {
		println!("info");
	}
}

// odpowiednik destruktora (trait Drop)
// jest to także przykład implementacji cechy (trait) dla danego typu
impl Drop for NazwaStruktury {
	fn drop(&mut self) {
		// wywołuje się automatycznie, gdy obiekt wychodzi poza zakres
		println!("destruktor");
	}
}

// możemy też definiować własne cechy (trait) i implementować
// je zarówno dla własnych jak i innych typów
trait Wypisz {
	fn wypisz1(&self) {
		println!("wypisz1");
	}
	fn wypisz2(&self) {
		println!("wypisz2");
	}
}

// dodanie trait "Wypisz" do "NazwaStruktury"
impl Wypisz for NazwaStruktury {
	// domyślną implementację funkcji z trait możemy zmieniać
	fn wypisz1(&self) {
		println!("wypisz1 NADPISANY");
	}
}

// jeżeli nie potrzebujemy modyfikować domyślnych implementacji funkcji wystarczy:
// impl Wypisz for NazwaStruktury {}

// można powiedzieć że "NazwaStruktury" dziedziczy po "Wypisz" i po "Drop"

// często dziedziczenie po trait może być też zapisywane poprzez "dekorację" samej definicji struktury:
#[derive(Debug)]
struct Struktura2 {
	a: i32,
}
// powoduje to dodanie implementacji trait z użyciem makro
// (które może generować kod implementacji specyficzny dla danego typu, czyli w sposób
// automatyczny generować dedykowane implementacje funkcji z trait dla danego typu)

// w tym wypadku zaimplementowana będzie funkcja 
//  fn fmt(&self, _: &mut Formatter<'_>) -> Result<(), std::fmt::Error>
// w trait Debug, pozwalajaca na wypisywanie typu z użyciem {:?}

fn main() {
	// korzystanie ze struktur
	let mut s = NazwaStruktury::new(0);
	s.a = 45;
	s.wypisz();

	// korzystanie z metod statycznych
	NazwaStruktury::info();

	// W Rust nie można wywołać metody statycznej bezpośrednio na obiekcie
	// poniższe spowoduje błąd
	// s.info();
	
	// ale można odwoływać się do nie statycznych poprzez nazwę struktury:
	NazwaStruktury::wypisz(&s);
	
	// odwołania do stałych przez nazwę typu a nie obiekt
	println!("{}", NazwaStruktury::Y);
	// to spowoduje błąd:
	// println!("{}", s.Y);
	
	s.wypisz1();
	s.wypisz2();
	
	// jako że różne trait mogą implementować tą samą funkcję to warto się odwoływać
	// do tych funkcji z użyciem przestrzeni nazw danego trait (patrz problem z `WypiszX`)
	Wypisz::wypisz1(&s);
	
	let x = Struktura2 {a: 2};
	println!("{:?} ... x.a={}", x, x.a);
}

trait WypiszX {
	fn wypisz2(&self) {
		println!("WypiszX::wypisz2");
	}
}
// poniższe spowoduje błąd ze względu na użycie `s.wypisz2()`
// które w tym momencie stałoby się niejednoznaczne
// gdyby w `main()` zamiast `s.wypisz2()` użyć `Wypisz::wypisz2(&s)`
// nie byłoby tego problemu
// impl WypiszX for NazwaStruktury {}

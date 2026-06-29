/*
Rust nie pozwala na wartości domyślne dla argumentów funkcji.
Coś podobnego można zaimplementować z użyciem Option.
Ale w przypadku prostych argumentów (jak w tym wypadku) nie ma to większego sensu
(gdyż jawne podanie domyślnej wartości takiego argumentu jest prostsze).
*/

fn funkcja0(a : Option<i32>) {
	println!("funkcja0: {}", a.unwrap_or(0));
}

/* 
Rust nie pozwala na tworzenie funkcji które przyjmują dowolną (zmienną) liczbę argumentów.
W  tym celu używane są makra.

Makra służą do generowania kodu i rozwijane są zanim kompilator zinterpretuje kod
(podobnie jak makra preprocesora w C). Wywołanie makra zawiera `!` po jego nazwie.
*/

macro_rules! print_per_line {
	( $( $x:expr ),* ) => {
	// $( $x:expr ),* jest wzorcem powtórzenia 
	// pod $x będą podstawiane kolejne wyrażenia (expr)
	// rozdzielane przecinkami (,) ... 
	// w ogólności możemy tego używać także z innymi syntaktycznie poprawnymi
	// separatorami (np. ; =>), ale nie z dowolnym znakiem/ciągiem znaków
		{
			let mut a = 0;
			// poniższe działa jak pętla generująca kod dla każdej wartości $x
			// jest to rozwijane na etapie generowania kodu - w kodzie programu nie będzie pętli
			// za to będzie odpowiednio duża ilość kopii kodu zawartego w $()*
			$(
				a += 1;
				println!("{}", $x);
			)*
			// możemy też zwrócić jakąś wartość (brak return nie jest błędem ...)
			a
		}
	};
}

macro_rules! macro1 {
	(0) => {
		println!("macro1 call with zero");
	};
	(1) => {
		nie_istniejąca_funkckja();
	};
}

fn funkcja1(a : i8) {
	match a {
		0 => println!("funkcja1 call with zero"),
		
		// w przypadku funkcji poniższe spowoduje błąd kompilacji
		// (nawet gdy funkcja nie jest nigdy użyta)
		// 1 => nie_istniejąca_funkckja(),
		
		// w przypadku match musimy obsłużyć wszytskie przypadki
		// (nie byłoby to konieczne gdyby match zastąpić przez if)
		_ => println!("funkcja1 call with {}", a),
	}
}

macro_rules! macro2 {
	(0) => {
		println!("macro2 call with zero");
	};
	($x:expr) => {
		println!("macro2 call with {}", $x);
	};
}

fn main() {
	funkcja0(None);
	funkcja0(Some(32));
	
	let y = 17;
	let x = print_per_line!(13, "abc", 0.5, y);
	println!("x={}", x);
	
	macro1!(0);
	
	// poniższe spowoduje błąd kompilacji gdyż
	// nie_istniejąca_funkckja nie jest zdefiniowana
	// macro1!(1);
	// gdy `macro1!(1);` nie jest użyte błąd nie występuje
	// gdyż kod dla tego przypadku nie jest generowany, czyli
	// `nie_istniejąca_funkckja` nie znajdzie się w kompilowanym kodzie
	
	// poniższe spowoduje błąd kompilacji gdyż zachowanie
	// macro1 dla argumentu 3 jest niezdefiniowane
	// macro1!(3);
	
	macro2!(3);
}

/*
Innym zastosowaniem makr jest generowanie implementacji trait
(czyli funkcji reprezentujących jakąś cechę) dla danego typu.
Tak działa np. `#[derive(Debug)]` który dodaje `std::fmt::Debug`
dla typu do dekoracji którego został użyty.
*/

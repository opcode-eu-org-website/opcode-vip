fn main() {
	let a = 1;  // typ zmiennej będzie ustalony na podstawie przypisanej wartości
	let b: f64; // zmienna typu zmiennoprzecinkowego podwójnej precyzji
	            // bez ustalonej wartości
	b = a as f64; // Rust wymaga jawnego rzutowania nawet int -> float
	
	println!("{a} {b}");
	
	// kolejne ustawienie wartości normalnej zmiennej nie jest możliwe
	// odkomentuj poniższą linię aby zobaczyć błąd kompilacji
	// a = 2;  b = 15.0;
	
	
	/* MUTABLE */
	
	// w tym celu konieczne jest ustawienie zmiennej jako mutowalną
	
	let mut c = 13;
	println!("{c}");
	
	c = 17;
	println!("{c}");
	
	// ale normalną zmienną można nadpisać (bez ostrzeżenia!) używając ponownie let
	let a = 15;
	println!("{a}");
	
	
	/* NAPISY */
	
	// `str` - niemodyfikowalny widok ciągu znaków
	let x = "abc";
	// dynamicznie rozszerzalny (i modyfikowalny) napis
	let y = String::from("xyz");
	// niemodyfikowalny widok ciągu znaków,który może być dynamicznie zaalokowany
	let z: Box<str> = Box::from("123");
	
	println!("{x} {y} {z}");
	
	
	/* MOVE */
	
	// w Rust domyślną polityką użycia (przypisania lub przekazania do funkcji)
	// "większych" zmiennych (czyli alokowanych na stercie) nie jest kopiowanie
	// ani referencja a `move`, co powoduje zużycie oryginalnej zmiennej:
	let q = y;
	
	// y nie jest już w tym miejscu poprawne i nie można się do niego odwołać
	// odkomentuj poniższą linię aby zobaczyć błąd kompilacji
	// println!("{q} {y}");
	println!("{q}");
	
	// zmiennej alokowane na sosie są domyślnie kopiowane
	let d = c;
	println!("{d} {c}");
	
	// aby jawnie użyć referencji stosuje się `&`
	let v1 = &q;
	
	// aby uzyskać kopię stosuje się odpowiednią metodę - taką jak `.clone()`
	let v2 = q.clone();
	println!("{v1} {v2} {q}");
	// nie każdy typ udostępnia clone(): ani x.clone() ani z.clone() nie zadziałają
	
	// zmienne globalne
	{
		let mut guard = GLOBALNA.lock().unwrap();
		println!("globalna: {}", guard);
		*guard += 2;
	}
	funkcja();
	{
		let guard = GLOBALNA.lock().unwrap();
		println!("globalna: {}", guard);
	}
}

use std::sync::Mutex;

static GLOBALNA: Mutex<i32> = Mutex::new(13);
// zmienne globalne muszą być bezpieczne wielowątkowo ... dlatego Mutex

fn funkcja() {
	let mut guard = GLOBALNA.lock().unwrap();
	println!("globalna: {}", guard);
	*guard += 2;
}

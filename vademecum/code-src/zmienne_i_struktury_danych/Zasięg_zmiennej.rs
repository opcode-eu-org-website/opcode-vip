use std::rc::Rc;

fn wypisz1(a: String) {
	println!("{a}")
}

fn wypisz2(a: &String) {
	println!("{a}")
}

fn wypisz3(a: &str) {
	println!("{a}")
}

fn main() {
	let a = String::from("xyz");
	{
		let b = &a;
		println!("{b}");
	}
	// b nie istnieje już w tym miejscu - wyszliśmy z bloku
	// odkomentuj poniższą linię aby zobaczyć błąd kompilacji
	// println!("{b}");
	
	let c;
	{
		let d = String::from("abc");
		c = &d;
		println!("{c}");
	}
	// c istnieje tutaj, ale wskazuje na b,
	// które nie żyje dostatecznie długo aby móc być tu użyte
	// odkomentuj poniższą linię aby zobaczyć błąd kompilacji
	// println!("{c}");
	
	let e = String::from("qwe");
	wypisz1(e);
	// własność e została przeniesiona do funkcji `wypisz1`
	// (dokładniej do zmiennej a w tej funkcji)
	// dlatego już nie możemy używać e
	// odkomentuj poniższą linię aby zobaczyć błąd kompilacji
	// println!("{e}");
	
	let f = String::from("qwe2");
	wypisz2(&f);
	wypisz3(&f);
	// funkcje wypisz2 i wypisz3 przyjmują referencje
	// więc własność pozostaje na zmiennej f
	// i można z niej dalej korzystać
	println!("{f}");
	
	let x;
	let y;
	{
		let z: String = String::from("123");
		x = z.clone(); // kopiowane są dane
		println!("{x} {z}");
		
		let q: Rc<str> = Rc::from("456");
		println!("licznik referencji: {}", Rc::strong_count(&q));
		y = q.clone(); // kopiowana jest jedynie referencja na dane
		println!("{y} {q}");
		println!("licznik referencji: {} == {}", Rc::strong_count(&q), Rc::strong_count(&y));
	}
	println!("{x} {y}");
	println!("licznik referencji: {}", Rc::strong_count(&y));
	
	// wielowątkowym odpowiednikiem Rc<> jest Arc<>,
	// jednak zabezpiecza on wielowątkowo sam licznik referencji a nie dane
	// do ich zabezpieczenia potrzebny jest Mutex<> umieszczony wewnątrz Arc<>
	
	println!("{}", zwroc_dluzszy1(&x, &f));
	println!("{}", zwroc_dluzszy2(&x, &f));
}

// jeżeli chcemy aby funkcja zwracała referencję musimy zapewnić
// aby czas życia otrzymanych referencji był odpowiednio długi
// w tym wypadku specyfikujemy że czas życia obu argumentów musi
// być nie krótszy niż czas życia wyniku
// (`'a: 'c` -> 'a jest conajmniej tak długi jak 'c, podobnie z 'b w `'b: 'c`)
fn zwroc_dluzszy1<'c, 'a: 'c, 'b: 'c>(a: &'a str, b: &'b str) -> &'c str {
	if b.len() > a.len() {
		return b;
	}
	return a;
}

// zapis ten można uprościć do
fn zwroc_dluzszy2<'a>(a: &'a str, b: &'a str) -> &'a str {
	if b.len() > a.len() {
		return b;
	}
	return a;
}

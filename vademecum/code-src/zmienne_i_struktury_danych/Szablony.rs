// Rust nie ma przeciążania funkcji

fn dodaj(x: i32, y: i32) -> i32 { return x+y; }
// poniższe spowoduje błąd
// fn dodaj(x: f32, y: f32) -> f32 { return x+y; }

// Rust wspiera tworzenie szablonów funkcji (nazywanych w tym języku generic-ami)

fn dodaj1<T: std::ops::Add<Output = T>>(x: T, y: T) -> T {
	// wymagamy od typu T aby miał zdefiniowaną operację dodawania
	// której wynikiem jest typ T
	return x+y;
}

fn dodaj2<A: std::ops::Add<B, Output = C>, B, C>(x: A, y: B) -> C {
	// wymagamy od typu A aby miał zdefiniowaną operację dodawania z typem B
	// której wynikiem jest typ C
	return x+y;
}

// możemy tworzyć typy generyczne

struct Struktura<T> {
    x: T,
}

impl<T> Struktura<T> { // domyślna implementacja
    fn get(&self) -> &T {
        &self.x
    }
}

// możemy:

impl<T> Wypisz for Struktura<T> {}

impl<T: std::fmt::Display> Wypisz2 for Struktura<T> {
	fn wypisz1(&self) {
		println!("wypisz2 {}", self.x);
	}
}

impl Wypisz3 for Struktura<Arc<str>> {
	fn wypisz1(&self) {
		println!("wypisz3 {}", self.x);
	}
}

impl Wypisz3 for Struktura<i32> {
	fn wypisz1(&self) {
		println!("wypisz3 (int) {}", self.x);
	}
}

// ale nie możemy (w stabilnej wersji Rust) wykonać
// specjalizacji generic-a dla konkretnego typu:
/*
impl Wypisz for Struktura<i64> {
	fn wypisz1(&self) {
		println!("wypisz1 INT {}", self.x);
	}
}
*/

// możemy co najwyżej symulować coś takiego z użyciem Any

use std::any::Any;

impl<T: std::fmt::Display + 'static> Wypisz4 for Struktura<T> {
	fn wypisz1(&self) {
		let a = self as &dyn Any;
		if let Some(b) = a.downcast_ref::<Struktura<i32>>() {
			println!("wypisz4 (int): {}", b.x);
		} else if let Some(b) = a.downcast_ref::<Struktura<Arc<str>>>() {
			println!("wypisz4 (str): {}", b.x);
		} else {
			println!("wypisz4 {}", self.x);
			
		}
	}
	fn zmodyfikuj(&mut self, v: f32) {
		let a = self as &mut dyn Any;
		if let Some(b) = a.downcast_mut::<Struktura<f32>>() {
			println!("zmodyfikuj {} -> {}", b.x, v);
			b.x = v;
		}
	}
}

// downcast z Any będzie zawsze dawał opcje na referencję,
// jeżeli potrzebujemy możliwości przejęcia własności obiektu
// należy skorzystać z Box<dyn Any>

impl<T> Przejmij for Struktura<T> {
	fn przejmij(a: Box<dyn Any>) {
		if a.downcast_ref::<Struktura<f32>>().is_some() {
			let b : Box<Struktura<f32>> = a.downcast::<Struktura<f32>>().unwrap();
			let c = *b; // mapowanie Box<T> na T
			println!("przejęto {}", c.x);
		} else {
			println!("to nie Struktura<f32>");
		}
	}
}

/* bardziej użyteczny przykład dla implementacji błędów złożonych (zamiast Any mamy Error)

use std::error::Error;

#[derive(Debug)]
enum MojeBłędy {
	Zero,
	NieDodatnie,
}

#[derive(Debug)]
enum WszystkieBłędy {
	WłasneBłedy(MojeBłędy),
	Inny(Box<dyn Error>), 
}

impl<E: Into<Box<dyn Error>>> From<E> for WszystkieBłędy {
	fn from(err: E) -> Self {
		let e = err.into();
		if e.downcast_ref::<MojeBłędy>().is_some() {
			let moj_blad : Box<MojeBłędy> = e.downcast::<MojeBłędy>().unwrap();
			return Self::WłasneBłedy(*moj_blad);
		} else {
			return Self::Inny(e);
		}
	}
}
*/

use std::sync::Arc;

fn main() {
	println!("{}", dodaj1(1, 2));
	println!("{}", dodaj1(1.0, 2.0));
	
	// ale nie:
	// println!("{}", dodaj1(1, 2.0));
	// ani
	// println!("{}", dodaj1(String::from("abc"), "def"));
	// ale za to
	println!("{}", dodaj2(String::from("abc"), "def"));
	
	let a = Struktura { x: 15 };
	let b : Struktura<Arc<str>> = Struktura { x: Arc::from("abc") };
	let mut c : Struktura<f32> = Struktura { x: 13.17 };
	
	println!("{} {}", a.x, b.x);
	println!("{} {}", a.get(), b.get());
	
	Wypisz::wypisz1(&a);
	Wypisz::wypisz1(&b);
	
	Wypisz2::wypisz1(&a);
	Wypisz2::wypisz1(&b);
	
	Wypisz3::wypisz1(&a);
	Wypisz3::wypisz1(&b);
	
	Wypisz4::wypisz1(&a);
	Wypisz4::wypisz1(&b);
	Wypisz4::wypisz1(&c);
	
	Wypisz4::zmodyfikuj(&mut c, 13.13);
	println!("{}", c.x);
	
	<Struktura<f32> as Przejmij>::przejmij(Box::new(c));
	// to spowoduje błąd: println!("{}", c.x);
}

trait Wypisz {
	fn wypisz1(&self) {
		println!("wypisz1");
	}
}

trait Wypisz2 {
	fn wypisz1(&self);
}

trait Wypisz3 {
	fn wypisz1(&self);
}

trait Wypisz4 {
	fn wypisz1(&self);
	fn zmodyfikuj(&mut self, v: f32);
}

trait Przejmij {
	fn przejmij(a: Box<dyn Any>);
}

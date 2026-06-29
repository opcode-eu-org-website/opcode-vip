use std::process::ExitCode;
use std::env;

fn main() -> ExitCode {
	let argumenty : Vec<String> = env::args().collect();
	
	if argumenty.len() < 2 {
		// wypisanie komunikatu na standardowe wyjście błędu
		eprintln!("Program wymaga argumentu będącego liczbą");
		
		// zwrócenie 101 jako kodu powrotu programu
		return ExitCode::from(101);
	}
	
	let x = argumenty[1].parse::<i32>().unwrap();
	// unwrap() zwraca wartość opakowaną w Result (i32 w tym wypadku) jeżeli nie ma błędu
	// a w przypadku gdy jako Result zwrócony został błąd to przerywa działanie programu
	// wypisując domyślny komunikat dla danego błędu
	
	let y = funkcja1(x);
	
	println!("{:?}", y.ok());
	// ok() powoduje konwersję Result<T> w Option<T>,
	// czyli dowolny błąd zostanie zastąpiony None
	
	let z = funkcja3(x);
	println!("is_err = {} err = {:?}", z.is_err(), z.err());
	
	let q = funkcja4(x);
	let w = sprawdz_bledy(q);
	println!("{}", w);
	
	// zwrócenie 0 jako kodu powrotu programu
	return ExitCode::from(0);
}


//////////////////
//              //
// proste błędy //
//              //
//////////////////

#[derive(Debug)]
enum MojeBłędy {
	Zero,
	NieDodatnie,
}

// pozwala na wypisywanie własnych błędów (używane przez z.err())
impl std::fmt::Display for MojeBłędy {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{self:?}")
    }
}

// implementacja trait Error dla własnego typu błędów
// (nie jest to wymagane, ale użyteczne)
impl Error for MojeBłędy {}


fn funkcja1(a: i32) -> Result<i32, MojeBłędy> {
	if a == 0 {
		return Err(MojeBłędy::Zero);
	} else {
		return Ok(a);
	}
}

fn funkcja2(a: i32) -> Option<i32> {
	if a > 0 {
		return Some(a);
	} else {
		return None;
	}
}

fn funkcja3(a: i32) -> Result<i32, MojeBłędy> {
	return funkcja2(a).ok_or(MojeBłędy::NieDodatnie);
	// ok_or() konwertuje Option<T> w Result<T, E>
}


///////////////////
//               //
// błędy złożone //
//               //
///////////////////

use std::error::Error;

// Box<dyn Error> pozwala na opakowanie dowolnego typu implementującego trait Error
// (dokładny typ nie musi być znany w czasie kompilacji)

fn funkcja4(a: i32) -> Result<i32, Box<dyn Error>> {
	let b = funkcja1(a)?;
	println!("funkcja4 b={b}");
	if b == 1 {
		use std::fs::File;
		use std::io::Read;
		
		let mut c = File::open("plik")?;
		let mut d = String::new();
		c.read_to_string(&mut d)?;
		return Ok(d.parse::<i32>()?);
	} 
	return Ok(funkcja3(a)?);
}

// własna identyfikacja błędu (odpowiednik `.unwrap()`)
// wraz z rozpoznaniem typu tego błędu
fn sprawdz_bledy(a: Result<i32, Box<dyn Error>>) -> i32 {
	let c = match a {
		Ok(x) => x,
		Err(e) => {
			if let Some(io_err) = e.downcast_ref::<std::io::Error>() {
				println!("Błąd IO: {}", io_err);
				// rozróżnianie różnych typów błędów IO w oparciu o ErrorKind
				use std::io::ErrorKind;
				match io_err.kind() {
					ErrorKind::NotFound => {
						panic!("Nie ma pliku");
					},
					_ => {
						panic!("Inny błąd");
					}
				}
			} else if let Some(parse_err) = e.downcast_ref::<std::num::ParseIntError>() {
				panic!("Błąd Parsowania: {} / {:?}", parse_err, parse_err);
				// warto zwrócić uwagę na różnicę między wypisywaniem
				// {} używającym Display a wypisywaniem {:?} używającym Debug
			} else if let Some(my_err) = e.downcast_ref::<MojeBłędy>() {
				panic!("Mój błąd: {}", my_err);
			} else {
				panic!("Inny błąd");
			}
		},
	};
	return c
}

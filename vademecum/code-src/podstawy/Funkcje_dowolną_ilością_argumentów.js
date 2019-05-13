
function f1() {
	console.log("ABC\n");
}

// funkcja dwuargumentowa zwracająca wartość
function f2(a, b) {
	return a*2.5 + b;
}

// funkcja z jednym argumentem obowiązkowym
// i jednym opcjonalnym
function f3(a, b=1) {
	console.log("F3\n");
	return a*2.5 + b;
}

// funkcja z dowolną ilością argumentów
function f4() {
	var ret = 0;
	
	for(var i=0; i<arguments.length; i++) {
		ret += arguments[i];
	}
	
	return ret;
}

f1();
// zwracaną wartość można wykorzystać:
var a = f2(3, 6);
// lub zignorować:
f3(0);
var b = f4(2, 1, 2.8, 3.5);

console.log("a=" + a +" b=" + b + "\n");

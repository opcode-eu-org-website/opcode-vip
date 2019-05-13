
// pseudo odpowiednik
// tablicy asocjacyjnej

var o = {a: 1, b: 2, c: 3};

// dodanie elementu
o.ab = "pp";

// usunięcie elementu
delete o.b; 

for (var k in o) {
	console.log(
		`o.${k} = ${o[k]} \n`
	);
}

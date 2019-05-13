
var a = 12.7, b = 3, c = 13, d, e;

// dodawanie, mnożenie, odejmowanie zapisuje się
// i działają one tak jak w normalnej matematyce:
e = (a + b) * 4 - c;

// dzielenie zawsze jest zmiennoprzecinkowe
d = a / b;
c = b / c;

// wypisanie wyników
console.log(
	"e=" + e + "\n" +
	"d=" + d + "\n" +
	"c=" + c + "\n"
);

// operacje logiczne:
// ((a większe równe od 0) AND (b mniejsze od 2)) OR (c równe 5)
var z = (a>=0 && b<2) || c == 5;
// negacja logiczna z
a = !z;

console.log(
	"z=" + z + "\n" +
	"a=" + a + "\n"
);

	// operacje binarne:
	// bitowy OR 0x0f z 0x11 i przesunięcie wyniku o 1 w lewo
	a = (0x0f | 0x11) << 1;
	// bitowy XOR 0x0f z 0x11
	b = (0x0f ^ 0x11);
	// negacja bitowa wyniku bitowego AND 0xfff i 0x0f0
	c = ~(0xfff & 0x0f0);
	
console.log(
	"a=0x" + a.toString(16) + "\n" +
	"b=0x" + b.toString(16) + "\n" +
	"c=0x" + (c & 0xffff).toString(16) + "\n"
);

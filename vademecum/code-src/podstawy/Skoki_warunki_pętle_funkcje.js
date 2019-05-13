
var i, j, k;

// instrukcja waunkowa if - else
if (i<j) {
	console.log("i<j\n");
} else if (j<k) {
	console.log("i>=j AND j<k\n");
} else {
	console.log("i>=j AND j>=k\n");
}

// podstawowe operatory logiczne
if (i<j || j<k)
	console.log("i<j OR j<k\n");
// innymi operatorami logicznymi są && (AND), ! (NOT)

// pętla for
for (i=2; i<=9; ++i) {
	if (i==3) {
		// pominięcie tego kroku pętli
		continue;
	}
	if (i==7) {
		// wyjście z pętli
		break;
	}
	console.log(" a: ", + i + "\n");
}

// pętla while
while (i>0) {
	console.log(" b: " + --i + "\n");
}

// pętla do - while
do {
	console.log(" c: " + ++i + "\n");
} while (i<2);

// instrukcja wyboru switch
switch(i) {
	case 1:
		console.log("i==1\n");
		break;
	default:
		console.log("i!=1\n");
		break;
}

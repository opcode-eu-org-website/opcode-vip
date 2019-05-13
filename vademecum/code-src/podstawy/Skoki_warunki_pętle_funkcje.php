
<?php

$i=$j=$k=0;

// instrukcja waunkowa if - else
if ($i<$j) {
	echo("i<j\n");
} else if ($j<$k) {
	echo("i>=j AND j<k\n");
} else {
	echo("i>=j AND j>=k\n");
}

// pętla for
for ($i=2; $i<7; ++$i) {
	if ($i==$j) {
		// pominięcie tego kroku pętli
		continue;
	}
	printf(" a: %d\n", $i);
}

// pętla while
while ($i>0) {
	if ($i==$k) {
		// wyjście z pętli
		break;
	}
	printf(" b: %d\n", --$i);
}

// pętla do - while
do {
	printf(" c: %d\n", ++$i);
} while ($i<2);

// instrukcja wyboru switch
switch($i) {
	case 1:
		echo("i==1\n");
		break;
	default:
		echo("i!=1\n");
		break;
}

?>

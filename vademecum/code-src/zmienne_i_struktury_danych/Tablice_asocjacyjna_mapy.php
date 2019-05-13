
<?php

$a = array('ab' => True, 'cd' => 'xx');
$a['efg'] = 15;
$a['cd']="yu";

# sprawdzenie istnienia 
if (isset($a['ab'])) {
	// uwaga: gdy $a['ab'] = null
	// to isset zwróci FALSE
	// patrz array_key_exists()
	echo "jest ab";
	
	# usunięcie elementu
	unset($a['ab']);
}

while ( list($k, $v) = each($a) ) {
	echo "a[$k] = $v\n";
}

?>

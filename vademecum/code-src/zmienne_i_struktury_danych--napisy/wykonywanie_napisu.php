
<?php
$a='echo "aaa"; $b="cc";';
eval($a);
echo "\n" . $b . "\n";

$a='2+6';
eval('$b='. $a .';');
echo $b . "\n";
?>

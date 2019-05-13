
a[0]="a b c"
a[1]=123
a[2]=zz
a[3]=qq

x=1
echo "wybrane elementy tablicy: " ${a[$x]} ${a[0]}
echo "cała tablica: " ${a[@]}
echo "ilość elementów w tablicy tablica: " ${#a[@]}


# dla kodu bashowego
a='echo "ppp"; b="ooo"'
eval $a
echo $b

# dla obliczeń arytmetycznych
a="13+17"
b=$(( $a ))
echo $b

# alternatywnie przez
# zewnętrzny kalkulator np.:
b=`echo $a | bc`
echo $b


i=k=j=0

# instrukcja waunkowa if - else
if i<j :
	print("i<j")
elif j<k :
	print("i>=j AND j<k")
else:
	print("i>=j AND j>=k")

# podstawowe operatory logiczne
if (i<j or j<k)
	puts("i<j OR j<k");
# innymi operatorami logicznymi są and oraz not


# pętla for
for i in range(2, 9):
	if i==3:
		# pominięcie tego kroku pętli
		continue;
	if i==7:
		# wyjście z pętli
		break;
	print(" a:", i);
else:
	# nie wejdzie tutaj bo pętla kończy
	# się z użyciem break
	print("else w pętli");

# pętla while
while i>0 :
	i = i - 1;
	print(" b:", i);
else:
	# wejdzie tu gdy warunek i>0
	# nie będzie spełniony
	# zarówno przy pierwszym
	# jak i kolejnych sprawdzeniach
	print("else w pętli");

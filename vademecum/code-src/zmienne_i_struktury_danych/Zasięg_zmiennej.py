
a, b, d = 5, 12, [1, 2, 3]

def f1(c):
	return c+b

def f2(c):
	b=2
	return c+b

# f1 korzysta z zmiennej globalnej b
# f2 przysłania sobie zmienną globalną b poprzez swoją zmienną lokalną
print("f1(a) =", f1(a), "f2(a) =", f2(a), "ale b nadaj wynosi:", b)

def f3(c):
	global b
	b=16
	return c+b

# f3 dzięki temu że jawnie deklaruje iż używa globalnego b
#    może modyfikować zmienną globalną
print("f3(a) =", f3(a), "teraz b wynosi:", b)

def f4(c):
	c = 2*c
	return c

# argumenty funkcji są zmiennymi lokalnymi
print("f4(a) =", f4(a), "ale a nadaj wynosi:", a)

def f5(c):
	c[0]="xx"
	return c

print("f5(d) =", f5(d), "tym razem d uległo modyfikacji:", d)

if d[1] == 2:
	x = "ABC"
else:
	x = 22

print("zmienna x jest widoczna poza blokiem w którym została utworzona", x)

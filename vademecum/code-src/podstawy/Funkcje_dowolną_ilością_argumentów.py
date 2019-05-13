
# funkcja bezargumentowa, zwracająca wartość
def f1():
	print("AA")
	return 5

a = f1()
print(a)

# funkcja przyjmująca jeden obowiązkowy
# argument oraz dwa opcjonalne
def f2(a, b=2, c=0):
	print(a**b+c)

f2(3)
f2(3, 3)
# można pominąć dowolne z argumentów z wartością
# domyślną odwołując się do pozostałych nazwami
f2(2, c=1)
# można podawać argumenty w dowolnej kolejności
# odwołując się do nich nazwami
f2(b=3, a=2)


# nieokreślona ilość argumentów pozycyjnych
def f(*a):
	for aa in a:
		print(aa)

f(1, "y", 6)
# ale nie: f(1, "y", u="p")

# nieokreślona ilość argumentów nazwanych
def f(**a):
	for aa in a:
		print(aa, "=", a[aa])

f(a="y", u="p")
# ale nie: f(1, u="p")

# nieokreślona ilość argumentów pozycyjnych i nazwanych
def f(*a1, **a2):
	print(a1)
	print(a2)

f(1, "y", 6)
f(a="y", u="p")
f(1, "y", u="p")

# można też wymusić ileś argumentów jawnych
def f(x, *a1, y="8", **a2):
	print(x, y)
	print(a1)
	print(a2)

f(1, "y", 6)
f(1, "y", u="p")
f(1, "z", y="y", u="p")
# ale nie: f(a="y", u="p")

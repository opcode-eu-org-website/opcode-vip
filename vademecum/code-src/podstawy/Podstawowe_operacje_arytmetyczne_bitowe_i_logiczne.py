
a = 12.7
b = 3
x = 5
y = 6

# dodawanie, mnożenie, odejmowanie zapisuje się i działają
# tak jak w normalnej matematyce:
e = (a + b) * 4 - y

# dzielenie zmiennoprzecinkowe
c = x / y

# dzielenie całkowite
b = a // b

# reszta z dzielenia
z = x % y;

# wypisanie wyników
print(e, c, b, z)

# operacje logiczne:
# ((a większe równe od 0) AND (b mniejsze od 2)) OR (z równe 5)
z = (a>=0 and b<2) or z == 5;
# negacja logiczna z
x = not z;

print(z, x);

# operacje binarne:
# bitowy OR 0x0f z 0x11 i przesunięcie wyniku o 1 w lewo
x = (0x0f | 0x11) << 1;
# bitowy XOR 0x0f z 0x11
y = (0x0f ^ 0x11);
# negacja bitowa wyniku bitowego AND 0xfff i 0x0f0
z = ~(0xfff & 0x0f0);

print(hex(x), hex(y), hex(z & 0xffff));
# wypisując z musimy określić jego bitowość

# wieloargumentowa operacja przypisania
a, b, c = 1, 2, 3
# Najpierw oblicza wartości wyrażeń po prawej, a dopiero potem przypisuje.
# Pozwala to np. na:
a, b = b, a
# celem zamiany wartości zmiennych bez jawnego używania zmiennej tymczasowej
print(a, b)

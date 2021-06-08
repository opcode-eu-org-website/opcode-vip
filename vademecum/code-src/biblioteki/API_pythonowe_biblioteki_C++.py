
# skrypt wykorzystujący moduł
# MyPyAPI stworzony w C++

# dodajemy bierzący katalog do ścieżki w której python szuka bibliotek
import sys
sys.path.append('./')

# importujemy naszą bibliotekę (z pliku MyPyAPI.so)
import MyPyAPI

# uruchomienie funkcji f1 i odebranie wyniku
ret = MyPyAPI.f1(2)
print(ret)

# utworzenie obiektu klasy K1 (Klasa)
kk = MyPyAPI.Klasa()

# oraz jego używanie ...
kk.a = 3
print(kk.f1(2))

kk.f2(1)
MyPyAPI.f22(kk, 1)
print("kk.a =", kk.a)

print(MyPyAPI.f11(kk, 1))

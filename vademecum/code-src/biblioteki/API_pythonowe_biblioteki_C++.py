
# skrypt wykorzystujący moduł
# MyPyAPI stworzony w C++

import sys
sys.path.append('./')

import MyPyAPI

ret = MyPyAPI.f1(2)
print(ret)

kk = MyPyAPI.Klasa()

kk.a = 3
print(kk.f1(2))

kk.f2(1)
MyPyAPI.f22(kk, 1)
print("kk.a =", kk.a)

print(MyPyAPI.f11(kk, 1))


# PLIK: py_run.script.py
# uruchamiany przez kod C++ z py_api.cpp

print("początek pliku .py")

ck0 = MyPyAPI.Klasa.get()
print("ck0:", ck0.f1(0))
print("ck1:", ck1.f1(0))

ck0.a=4
print("ck0:", ck0.f1(0))
print("ck1:", ck1.f1(0))

def script1(arg):
	print("run script1")
	
	print("ck0:", ck0.f1(0))
	print("ck1:", ck1.f1(0))
	print("arg:", arg.f1(0))
	
	arg.a=13
	print("ck0:", ck0.f1(0))
	print("ck1:", ck1.f1(0))
	print("arg:", arg.f1(0))
	
	print("end script1")
	
	return arg.a + ck0.a;

print("koniec pliku .py")

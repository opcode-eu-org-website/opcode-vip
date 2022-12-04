
# napis który będzie podawany na standardowe wejście uruchamianego polecenia
inStr = "Ala ma kota\nKot ma psa\n..."

# Python pozwala na bezpośrednie stosowanie funkcji znanych z języka C
# takich jak system(), popen(), fork(), execl() itd poprzez moduł os.
# Odbywa się to w sposóba analogiczny do użycia w języku C. Na przykład:

import os
os.system('echo -en "' + inStr + '" | grep -v A')

# Python zapewnia jednak także wygodny, zunifikowany sposób uruchamiania innych
# programów / poleceń powłoki poprzez moduł subprocess oraz rozgałęziania
# własnego procesu poprzez moduł multiprocessing.

print("""
#
# podstawy subprocess
#
""")
import subprocess

# uruchamiamy subprocess z grep'em
res = subprocess.run(["grep", "-v", "A"], input=inStr.encode(), stdout=subprocess.PIPE)
print("Kod powrotu to: " + str(res.returncode))
print("Standardowe wyjście z komendy to: " + res.stdout.decode())
# warto zwrócić uwagę na kodowanie i dekodowanie napisów
# (przekazywanych/odbieranych przez stdin/stdout) do / z utf-8

# jeżeli chcemy korzystać np. z znaków uogólniających powłoki lub podać
# komendę jako pojedynczy napis (a nie listę argumentów) to można użyć
# opcji shell=True:
subprocess.run(["ls -ld /etc/pa*"], shell=True)
# jeżeli potrzebujemy tylko rozbicia napisu na listę argumentów można
# użyć shlex.split()

# run() pozwala także (obok subprocess.PIPE) na przekazywanie
# istniejących deskryptorów (lub subprocess.DEVNULL, co ignoruje wyjście)
# w ramach stdin, stdout, stderr

# moduł subprocess oferuje także funkcję Popen() dającą większą kontrolę
# nad uruchamianiem komendy


print("""
#
# podstawy multiprocessing
#
""")
import multiprocessing, os, time
def fun1(txt, st, cnt):
	for _ in range(cnt):
		print("Proces", os.getpid(), "z st =", st, " i argumentem:", txt)
		time.sleep(st)

def fun2(c, e):
	# obsługa rury i zdarzenia
	c.send("Uwolnić mrożone truskawki")
	time.sleep(1.3)
	c.send([12, 13, { "ab" : 11, "cd" : "xx" }])
	c.close()
	e.clear()

if __name__ == '__main__':
	# przygotowanie potomków
	p1 = multiprocessing.Process(target=fun1, args=('Ala ma psa',1.5,4,))
	p2 = multiprocessing.Process(target=fun1, args=('pies ma kota',1,3,))
	
	print("mój pid to", os.getpid(), "... uruchamiam procesy")
	# uruchomienie potomków
	p1.start()
	p2.start()
	
	# czekanie na zakończenie p2
	p2.join()
	print("p2 się zakończył")
	
	# wymuszenie zakończenia p1 jeżeli nadal żyje
	if p1.is_alive():
		print("p1 żyje")
		p1.terminate()
	p1.join()
	print("p1 się zakończył")
	
	# rura i event
	
	# Pipe() tworzy nam parę obiektów multiprocessing.Connection
	# jednego będziemy używać w procesie głównym, a drugiego w potomnym
	pConn, cConn = multiprocessing.Pipe()
	
	# tworzymy obiekt typu Event ... jest to prosty sygnalizator
	# z flagą binarną zapewniający atomowość wykonywanych operacji
	evt = multiprocessing.Event()
	evt.set()
	
	# tworzymy i uruchamiamy kolejny podproces
	p1 = multiprocessing.Process(target=fun2, args=(cConn,evt,))
	p1.start()
	
	# odbieramy dane z połączenia dopóki event jest ustawiony
	try:
		while evt.is_set():
			if pConn.poll(0.1):
				print("otrzymałem: ", pConn.recv())
	except EOFError: pass


print("""
#
# pool i bariera w multiprocessing
#
""")
import multiprocessing, queue, os, time
from threading import BrokenBarrierError

def fun5Init(b):
	global bariera
	bariera = b

def fun5(arg):
	for i in range(arg['n']):
		print("Wątek", arg['n'], " iter =", i)
		time.sleep(arg['ts'])
	
	try:
		print("Wątek", arg['n'], " czekam na innych")
		if bariera.wait() == 0:
			print("wątki zsynchronizowane")
			# więcej nie używaj tej bariery:
			bariera.abort()
	except BrokenBarrierError:
		print("czekanie anulowane")
	
	return arg['n'] + arg['ts']

if __name__ == '__main__':
	# tworzymy barierę i warunek
	b = multiprocessing.Barrier(3)
	
	# tworzymy pool'a ... w ramach inicjalizacji
	# przekazujemy barierę i warunek
	pool = multiprocessing.Pool(
		processes=3, initializer=fun5Init, initargs=(b,)
	)
	
	# tworzymy listę argumentów dla funkcji
	# uruchamianej w procesach potomuych
	args = [
		{ 'n': 3,  'ts': 0.44 },
		{ 'n': 13, 'ts': 0.17 },
		{ 'n': 2,  'ts': 0.33 },
		{ 'n': 7,  'ts': 0.69 },
		{ 'n': 4,  'ts': 0.49 },
	]
	
	# tworzymy pulę 3 procesów potomnych i uruchamiamy w nich wskazaną
	# funkcję z kolejnymi zbiorami argumentów z podanej listy
	# uwaga: funkcja wywoływana przez map wraz z ewentualnymi zmiennymi
	#         globalnymi musi być zdefiniowana przed wywołaniem Pool()
	results = pool.map(fun5, args)
	
	pool.close() 
	pool.join()


print("""
#
# współdzielenie danych w multiprocessing
#
""")
import multiprocessing, queue, os, time

def fun4(lock, l, c):
	# obsługa zmiennej warunkowej
	for i in range(6):
		# blokujemy dostęp do listy
		c.acquire()
		# modyfikujemy zmienną na której mamy warunek
		l[0] = i
		# powiadamiamy wszystkich o tym
		c.notify_all()
		# zwalniamy dostęp do listy
		c.release()
		time.sleep(0.13)
	
	# obsługa locka i listy
	while True:
		if lock.acquire(timeout=0.5):
			# jeżeli udało się założyć lock'a ...
			l[1] += 1
			print("podprocess:", l)
			time.sleep(0.77)
			# zdjęcie lock'a
			lock.release()
			time.sleep(0.33)
		else:
			print("podprocess: can't lock")

if __name__ == '__main__':
	# tworzymy locka'a, czyli blokadę wejścia do sekcji krytycznej
	# (zmieniającej dane współdzielone)
	lock = multiprocessing.Lock()
	# oprócz zwykłych Lock'ów Python oferuje także:
	# * RLock - Lock w którym wątek zakładający blokadę może ją zakładać
	#   kolejne razy bez jej uprzedniego zwalniania, tzn sekwencja:
	#     l = RLock();
	#     l.acquire(); l.acquire();
	#     cos();
	#     l.release(); l.release();
	#   jest poprawna (przy zwykłym Lock'u zatrzyma się na drugim
	#   l.acquire())
	# * Semaphore - Lock z licznikiem dozwolonych wejść do sekcji
	#   krytycznej np. l = Semaphore(value=3) pozwoli na 3 wywołania
	#   l.acquire() (bez l.release())
	
	# tworzymy współdzieloną listę ... na menagerze
	m = multiprocessing.Manager()
	l = m.list([0, 1, 2, 3])
	
	# tworzymy zmienną warunkową używającą lock'a lock
	c = multiprocessing.Condition(lock)
	
	# tworzymy i uruchamiamy kolejny podproces
	p1 = multiprocessing.Process(target=fun4, args=(lock,l,c,))
	p1.start()

	print("czekamy na spełnienie warunku ...");
	c.acquire()
	while l[0] < 4:
		print("czekamy ... l[0]=", l[0])
		c.wait()
	c.release()
	print("warunek spełniony ... l[0] = ", l[0]);
	
	time.sleep(0.17)
	# obsługa listy
	for i in range(3):
		# założenie lock'a
		print("process: czekam na lock ...")
		lock.acquire()
		
		# dodanie elementu do listy i wypisanie
		l.append(13 + i)
		print("process:", l)
		time.sleep(0.69)
		
		# zdjęcie lock'a
		lock.release()
		time.sleep(1.0)
	
	# zakończenie
	p1.terminate()
	p1.join()
	m.shutdown()

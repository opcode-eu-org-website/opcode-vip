
print("""
#
# kolejki w multiprocessing
#
""")
import multiprocessing, multiprocessing.managers, queue, os, time

def fun3(q):
	# obsługa kolejki ... zakończenie można także realizować
	# np. w oparciu o dane otrzymane w kolejce
	while True:
		if not q.empty():
			el = q.get(block=False)
			# można także uruchamiać blokujący get()
			# z timeoutem lub bez ...
			if el[1] == None:
				break;
			else:
				print("potomek otrzymał", el)
		time.sleep(0.77)

if __name__ == '__main__':
	# tworzymy kolejkę
	# moduł multiprocessing zawiera swoje implementacje kolejki FIFO
	# (Queue, SimpleQueue i JoinableQueue), których można bezpiecznie
	# używać pomiędzy procesami:
	# q = multiprocessing.Queue()
	#
	# chcemy jednak użyć kolejki priorytetowej z modułu queue
	# (oferuje także kolejki FIFO (Queue) i LIFO (LifoQueue))
	# aby móc z niej poprawnie korzystać w multiprocessing
	# musimy użyć jej poprzez SyncManager'a:
	class Manager(multiprocessing.managers.SyncManager):
		pass
	Manager.register("PrioQueue", queue.PriorityQueue)
	m = Manager()
	m.start()
	q = m.PrioQueue()
	
	# dodajemy elementy do kolejki
	q.put((100, "delfin ma psa ;-)"))
	q.put((70, [13, 17]))
	q.put((200, [15, { "ab" : 11, "cd" : "xx" }]))
	
	# tworzymy i uruchamiamy kolejny podproces
	p1 = multiprocessing.Process(target=fun3, args=(q,))
	p1.start()
	
	# wkładanie danych do kolejki
	time.sleep(0.404)
	print("dodaje nowe wiadomości do kolejki ...")
	q.put((13, "ABC ... i co dalej"))
	q.put((180, "bla bla bla ..."))
	
	# informacja dla potomka o zakończeniu obsługi kolejki
	print("czekam na opróżnienie kolejki ...")
	while q.qsize() > 0:
		time.sleep(0.333)
	
	# kończenie
	q.put((999, None))
	p1.join()
	m.shutdown()

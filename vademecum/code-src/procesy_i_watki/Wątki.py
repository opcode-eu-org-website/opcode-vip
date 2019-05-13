
import threading, time
# UWAGA: 
# w standardowej implementacji CPython w danym
# czasie tylko jeden wątek może wykonywać
# kod pythonowy
#
# w efekcie stosowanie wątków ma sens tylko dla
# wątków czekających na coś, a nie ma sensu dla
# wątków mających wykonywać się równolegle
# (na różnych rdzeniach)
#
# w takim przypadku należy używać pełnego
# rozgałęziania procesu (moduł multiprocessing)

def fun(txt, st):
	# używamy lokalnej pamięci dla danego wątku
	daneWatku = threading.local()
	for daneWatku.i in range(4):
		print(txt, daneWatku.i)
		time.sleep(st)

# uruchomienie wątku
t = threading.Thread(target=fun, args=("AA",2,))
t.start();

# można także zdefiniować timer który
# uruchomi wątek po zadanym czasie
tim = threading.Timer(3, fun, args=("BB",1.2,))
tim.start()

# dla wątków można stosować także mechanizmy
# synchronizacji takie jak dla multiprocessing
#
# ponadto wątki można także obsługiwać przez
# interfejs identyczny z multiprocessing
# poprzez multiprocessing.dummy

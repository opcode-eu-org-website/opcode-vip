
import time
import os

def time2str(t, tz=None, fmt="%Y-%m-%d %H:%M:%S %Z (%s)"):
	if tz:
		oldTZ = os.environ['TZ']
		os.environ['TZ'] = tz
		time.tzset()
	
	tm = time.localtime(t)
	s = time.strftime(fmt, tm)
	
	if tz:
		os.environ['TZ'] = oldTZ
		time.tzset()
	
	return [s, tz]


czas = time.time()
print("Od początku epoki upłynęło " + str(czas) + " sekund")
# początek epoki to: 1970-01-01 00:00:00 UTC
# wynik jest niezależny od lokalnej strefy czasowej
# (zawsze wyrażany jest w UTC)

tt = time2str(czas, tz="UTC")
print("Mamy teraz: " + tt[0]);

tt = time2str(czas)
print("Mamy teraz: " + tt[0]);


from datetime import datetime, timezone

dt = datetime.fromtimestamp(czas, tz=timezone.utc)
print("Mamy teraz: " + dt.strftime("%Y-%m-%d %H:%M:%S %Z (%s)"))

# w celu pobrania aktualnego czasu zamiast fromtimestamp()
# można skorzystać z metody now()

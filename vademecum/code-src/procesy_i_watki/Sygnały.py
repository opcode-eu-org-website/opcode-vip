
import os, signal

pid = os.getpid()
print("Mój PID:", pid);

# obsługa sygnału
def obslugaSygnalu(s, f):
	print("Otrzymałem sygnał numer:", s)
	
# SIGINT - pojawia się m.in. w efekcie Ctrl+C
signal.signal(signal.SIGINT, obslugaSygnalu)

# SIGTSTP - pojawia się m.in. w efekcie Ctrl+Z
signal.signal(signal.SIGTSTP, obslugaSygnalu)

print("Czekam na dowolny sygnał")
signal.pause()

print("Czekam na sygnał z podanego zbioru")
# w odróżnieniu od C inne będą obsługiwane dopiero po otrzymaniu
# sygnału ze zbioru (zostaną zakolejkowane)
sig = signal.sigwait([signal.SIGTERM, signal.SIGINT])
print("Czekanie zakończone po otrzymaniu sygnału:", sig)

print("Czekam przez 10.5s na sygnał z podanego zbioru")
# w odróżnieniu od C inny sygnał jest obsługiwany,
# ale nie przerywa czekania
sig = signal.sigtimedwait([signal.SIGTERM, signal.SIGINT], 10.5)
if sig == None:
	print("timeout");
else:
	print("Czekanie zakończone po otrzymaniu sygnału:",
		sig.si_signo, "od pid:", sig.si_pid
	)

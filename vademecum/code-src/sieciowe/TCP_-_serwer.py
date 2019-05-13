
import socket, select, signal, sys, os

MAX_CHILD = 5
QUERY_SIZE = 3
TIMEOUT = 13
BUF_SIZE = 4096

if len(sys.argv) != 2:
	print("USAGE: " + sys.argv[0] + " listenPort", file=sys.stderr)
	exit(1);

# obsługa sygnału o zakończeniu potomka
childNum = 0
def onChildEnd(s, f):
	print("odebrano sygnał o śmierci potomka")
	global childNum
	childNum -= 1
	os.waitpid(-1, os.WNOHANG);
signal.signal(signal.SIGCHLD, onChildEnd)

# utworzenie gniazd sieciowych ... SOCK_STREAM oznacza TCP
sfd_v4 = socket.socket(socket.AF_INET,  socket.SOCK_STREAM)
sfd_v6 = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)

# ustawienie opcji gniazda ... IPV6_V6ONLY=1 wyłącza korzystanie
# z tego samego socketu dla IPv4 i IPv6
sfd_v6.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 1)

# przypisanie adresów ...
# '0.0.0.0' oznacza dowolny adres IPv4 (czyli to samo co INADDR_ANY)
# '::' oznacza dowolny adres IPv6 (czyli to samo co in6addr_any)
sfd_v4.bind(('0.0.0.0', int(sys.argv[1])))
sfd_v6.bind(('::',      int(sys.argv[1])))

# określenie gniazd jako używanych do odbioru połączeń przychodzących
# (długość kolejki połączeń ustawiona na wartość QUERY_SIZE)
sfd_v4.listen(QUERY_SIZE)
sfd_v6.listen(QUERY_SIZE)

# funkcja zajmująca się odbieraniem połączeń i ich obsługą
def acceptConn(sfd):
	global childNum
	
	#  odebranie połączenia
	sfd_c, sAddr = sfd.accept()
	
	# weryfikacja ilości potomków
	if childNum >= MAX_CHILD:
		print("za dużo potomków - odrzucam połączenie od:", sAddr);
		sfd_c.send("Internal Server Error\r\n".encode())
		sfd_c.close()
		return
	
	# aby móc obsługiwać wiele połączeń rozgałęziamy proces
	pid = os.fork()
	if pid == 0:
		print("połączenie od:", sAddr)
		while True:
			# czekanie na dane z timeout'em
			# aby zabezpieczyć się przed atakiem DoS
			rd, _, _ = select.select([sfd_c], [], [], TIMEOUT)
			if sfd_c in rd:
				data = sfd_c.recv(BUF_SIZE)
				if not data:
					print("koniec połączenia od:", sAddr)
					break
				print("odebrano od", sAddr, ":", data.decode());
				sfd_c.send(data)
			else:
				print("timeout połączenia od:", sAddr)
				break
		# zamykanie połączenia
		sfd_c.shutdown(socket.SHUT_RDWR)
		sfd_c.close()
		sys.exit()
	else:
		childNum += 1

# czekanie na połączenia z użyciem select() w nieskończonej pętli
while True:
	sfd, _, _ = select.select([sfd_v4, sfd_v6], [], [])
	if sfd_v4 in sfd:
		acceptConn(sfd_v4)
	if sfd_v6 in sfd:
		acceptConn(sfd_v6)

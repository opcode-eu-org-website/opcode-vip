
import socket, select, sys

if len(sys.argv) != 3:
	print("USAGE: " + sys.argv[0] + " dstHost dstPort", file=sys.stderr)
	exit(1);

# struktura zawierająca adres na który wysyłamy
dstAddrInfo = socket.getaddrinfo(sys.argv[1], sys.argv[2], proto=socket.IPPROTO_TCP)

# mogliśmy uzyskać kilka adresów, więc próbujemy używać kolejnych do skutku
for aiIter in dstAddrInfo:
	try:
		print("try connect to:", aiIter[4])
		# utworzenie gniazda sieciowego ... SOCK_STREAM oznacza TCP
		sfd = socket.socket(aiIter[0], socket.SOCK_STREAM)
		# połączenie ze wskazanym adresem
		sfd.connect(aiIter[4])
	except:
		# jeżeli się nie udało ... zamykamy gniazdo
		if sfd:
			sfd.close()
		sfd = None
		# i próbujemy następny adres
		continue
	break;

if sfd == None:
	print("Can't connect", file=sys.stderr)
	exit(1);

# wysyłanie
sfd.sendall("Ala ma Kota\n".encode())

# czekanie na dane i odbiór danych
while True:
	rdfd, _, _ = select.select([sfd], [], [], 13.0)
	if sfd in rdfd:
		d = sfd.recv(4096)
		d = d.decode()
		print(d, end="")
		
		# odbiór pustego pakietu lub pakietu zawierającego
		# jedynie pustą linię kończy działanie
		if d == "" or d == "\n" or d == "\r\n":
			break
	else:
		# timeout kończy działanie
		break

# zamykanie połączenia
sfd.shutdown(socket.SHUT_RDWR)
sfd.close()

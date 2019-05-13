
import socket, sys, os, signal

if len(sys.argv) != 3 and len(sys.argv) != 4:
	print("USAGE: " + sys.argv[0] + " dstHost dstPort [listenPort]", file=sys.stderr)
	exit(1);

# struktura zawierająca adres na który wysyłamy
dstAddrInfo = socket.getaddrinfo(sys.argv[1], sys.argv[2])

# tutaj mogliśmy uzyskać kilka adresów,
# ale optymistycznie zakładamy że pierwszy będzie OK
dstAddrInfo = dstAddrInfo[0]

# utworzenie gniazda sieciowego ... SOCK_DGRAM oznacza UDP
# (na gnieździe z SOCK_DGRAM standardowo nie będzie widać błędów ICMP
#  związanych np. z niedostępnością docelowego hosta lub portu ...)
sfd = socket.socket(dstAddrInfo[0], socket.SOCK_DGRAM)

if len(sys.argv) == 4:
	# jeżeli podane opcjonalne argumentu to określamy na jakim porcie słuchamy
	if dstAddrInfo[0] == socket.AF_INET6:
		sfd.bind(('::', int(sys.argv[3])))
		# :: oznacza dowolny adres IPv6
	elif dstAddrInfo[0] == socket.AF_INET:
		sfd.bind(('0.0.0.0', int(sys.argv[3])))
		# 0.0.0.0 oznacza dowolny adres
	# określenie tego wraz z uruchomieniem recvfrom() pozwala na oczekiwanie na
	# pakiety UDP na wskazanym adresie i porcie, gdyby w ramach obsługi odebranej
	# wiadomości odsyłana byłaby odpowiedź do nadawcy to byłby to "serwer UDP"

while True:
	rdfd, _, _ = select.select([sfd, sys.stdin], [], [])
	if sfd in rdfd:
		# odbieramy i wypisujemy dane z UDP
		data, addr = sfd.recvfrom(4096)
		print("odebrano od", addr, ":", data.decode());
	if sys.stdin in rdfd:
		# wczytujemy stdin
		data = sys.stdin.readline()
		if not data:
			# konczymy
			sfd.close()
			sys.exit()
		else:
			# wysyłamy dane z stdin
			sfd.sendto(data.encode(), dstAddrInfo[4])

# alternatywnie można użyć fork():
# pid = os.fork()
# if pid == 0:
# 	# potomek odbiera odpowiedzi w nieskończonej pętli
# 	# zostanie zakończony sygnałem od rodzica
# 	while True:
# 		data, addr = sfd.recvfrom(4096)
# 		print("odebrano od", addr, ":", data.decode());
# else:
# 	# rodzic wysyła wiadomości
# 	while True:
# 		data = sys.stdin.readline()
# 		if not data:
# 			break
# 		else:
# 			sfd.sendto(data.encode(), dstAddrInfo[4])
# 	os.kill(pid, signal.SIGTERM)
# 	sfd.close()

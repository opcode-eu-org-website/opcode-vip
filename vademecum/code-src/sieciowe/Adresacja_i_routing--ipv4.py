
# adresacja IPv4

from ipaddress import *

a1  = IPv4Address("192.168.34.17")
aa1 = int(a1)
print("adress IPv4 jest 32 bitową liczbą całkowitą np.: " + str(a1) + " == " + hex(aa1))

n0  = IPv4Network("0.0.0.0/25");
m1  = n0.netmask
mm1 = int(m1)
p1  = n0.prefixlen

print("Maska podsieci IPv4 jest 32 bitową liczbą całkowitą np.: " + str(m1) + " == " + hex(mm1))
print("Jako że maska jest liczbą, która zapisana binarnie, zawsze zawiera ciągły ciąg bitów")
print("o wartości 1, a po nim ciągły ciąg bitów o wartości 0 (mogą być zerowej długości), to")
print("często stosowany jest zapis polegający na podawaniu długości prefiksu: /" + str(p1))
print("jest to ilość bitów o wartości 1 w masce, czyli im większy prefix tym mniejsza sieć.")

n1  = IPv4Network("192.168.34.17/25", strict=False);
nn1 = int(n1.network_address)

print("Aby obliczyć adres sieci (czyli wspólną dla wszystkich hostów w danej sieci część")
print("adresu IP) należy wykonać binarny AND pomiędzy adresem IP hosta a maską podsieci.")
print("Dla powyższego przykładu:")
print(hex(mm1 & aa1) + " == " + str(n1) + " == " + hex(nn1))

# aby sprawdzić czy adres IP należy do danej sieci trzeba obliczyć adres sieci tego hosta
# w oparciu o maskę sieci którą sprawdzamy
def sprawdzSiec(n, a):
	nn = int(a) & int(n.netmask)
	if nn == int(n.network_address):
		print(str(a) + " należy do sieci " + str(n))
	else:
		print(str(a) + " NIE należy do sieci " + str(n))

sprawdzSiec(n1, IPv4Address("192.168.34.13"))
sprawdzSiec(n1, IPv4Address("192.168.34.199"))

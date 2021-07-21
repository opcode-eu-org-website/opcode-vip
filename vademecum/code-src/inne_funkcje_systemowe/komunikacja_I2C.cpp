
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

extern "C" {
#include <linux/i2c-dev.h>
#ifndef I2C_FUNC_I2C
#include <i2c/smbus.h>
#endif
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// wymagany pakiet libi2c-dev, kompilacja:
//   dla libi2c-dev < 4:
//     gcc       komunikacja_I2C.c
//   dla libi2c-dev >= 4:
//     gcc -li2c komunikacja_I2C.c

int main(int argc, char *argv[]) {
	int fd, i2c_addr, res, d, i = 4;
	
	if (argc < 4 | (argv[3][0] == 'a' && argc < 5)) {
		fprintf(stderr, "USAGE (read):  %s i2c_dev addr r            len\n", argv[0]);
		fprintf(stderr, "USAGE (read):  %s i2c_dev addr ar reg_addr  len\n", argv[0]);
		fprintf(stderr, "USAGE (write): %s i2c_dev addr w            d0 [d1 [d2 ...]]\n", argv[0]);
		fprintf(stderr, "USAGE (write): %s i2c_dev addr aw reg_addr  d0 [d1 [d2 ...]]\n", argv[0]);
		return 1;
	}
	
	// otwarcie urządzenia
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "Error open I2C device file (%s): %s\n", argv[1], strerror(errno));
		return 2;
	}
	
	// ustawienie adresu slave
	i2c_addr = strtol(argv[2], NULL, 0);
	res = ioctl(fd, I2C_SLAVE, i2c_addr);
	if (res < 0) {
		fprintf(stderr, "ERROR set device addres to 0x%02x: %s\n", i2c_addr, strerror(errno));
		return 3;
	}
	
	// tryb działania – czy używamy adresowania rejestru
	if (argv[3][0] == 'a') {
		// ustawiamy adres rejestru
		d = strtol(argv[4], NULL, 0);
		res = i2c_smbus_write_byte(fd, d);
		if (res < 0) {
			fprintf(stderr, "ERROR write (register address) %d to i2c device 0x%02x on %s: %s\n", d, i2c_addr, argv[1], strerror(errno));
			return 4;
		}
		
		++i; // i przechowuje numer kolejnego argumentu po tryb / reg_addr ... był "dodatkowy" reg_addr więc zwiększamy o jeden
	}
	
	// tryb działania – odczyt vs zapis
	if (argv[3][0] == 'r' || argv[3][1] == 'r') {
		// odczyt danych
		d =  strtol(argv[i], NULL, 0);
		for (i=0; i<d; ++i) {
			res = i2c_smbus_read_byte(fd);
			if (res < 0) {
				fprintf(stderr, "ERROR read from i2c device 0x%02x on %s: %s\n", i2c_addr, argv[1], strerror(errno));
				return 5;
			}
		}
	} else if (argv[3][0] == 'w' || argv[3][1] == 'w') {
		for (; i<argc; ++i) {
			d =  strtol(argv[i], NULL, 0);
			res = i2c_smbus_write_byte(fd, d);
			if (res < 0) {
				fprintf(stderr, "ERROR write %d to i2c device 0x%02x on %s: %s\n", d, i2c_addr, argv[1], strerror(errno));
				return 5;
			}
		}
	} else {
		fprintf(stderr, "ERROR invalid mode %s (should be 'r', 'ar', 'w' or 'aw')\n", argv[3]);
		return 1;
	}
	
	close(fd);
}

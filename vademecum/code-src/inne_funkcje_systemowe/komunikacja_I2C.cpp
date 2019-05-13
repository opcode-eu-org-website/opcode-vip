
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd, i2c_addr, res, d, i;
	
	if (argc < 4) {
		fprintf(stderr, "USAGE (read):  %s i2c_dev addr len\n", argv[0]);
		fprintf(stderr, "USAGE (write): %s i2c_dev addr --- d0 [d1 [d2 ...]]\n", argv[0]);
		return -1;
	}
	
	// otwarcie urządzenia
	fd = open(argv[1], O_RDWR);
	if (fd < 0) {
		fprintf(stderr, "Error open I2C device file (%s): %s\n", argv[1], strerror(errno));
		return -1;
	}
	
	// ustawienie adresu slave
	i2c_addr = strtol(argv[2], NULL, 0);
	res = ioctl(fd, I2C_SLAVE, i2c_addr);
	if (res < 0) {
		fprintf(stderr, "ERROR set device addres to 0x%02x: %s\n", i2c_addr, strerror(errno));
		return -1;
	}
	
	if (strcmp("---", argv[3])) {
		// odczyt danych
		d =  strtol(argv[3], NULL, 0);
		for (i=0; i<d; ++i) {
			res = i2c_smbus_read_byte(fd);
			if (res < 0) {
				fprintf(stderr, "ERROR read from i2c device 0x%02x on %s: %s\n",
					i2c_addr, argv[1], strerror(errno)
				);
			}
		}
	} else {
		for (i=4; i<argc; ++i) {
			d =  strtol(argv[i], NULL, 0);
			res = i2c_smbus_write_byte(fd, d);
			if (res < 0) {
				fprintf(stderr, "ERROR write %d to i2c device 0x%02x on %s: %s\n",
					d, i2c_addr, argv[1], strerror(errno)
				);
				return -2;
			}
		}
	}
	
	close(fd);
}

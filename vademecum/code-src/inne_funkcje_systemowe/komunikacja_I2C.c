
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/i2c-dev.h>
#ifndef I2C_FUNC_I2C
#include <i2c/smbus.h>
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

// wymagany pakiet libi2c-dev, kompilacja:
//   dla libi2c-dev < 4:
//     gcc       komunikacja_I2C.c
//   dla libi2c-dev >= 4:
//     gcc -li2c komunikacja_I2C.c

void help(const char *prog_name) {
	fprintf(stderr, "USAGE (without on chip register addres):\n");
	fprintf(stderr, " - read:  %s i2c_dev addr r -\n", prog_name);
	fprintf(stderr, " - write: %s i2c_dev addr w - data\n", prog_name);
	fprintf(stderr, "USAGE (with on chip register addres):\n");
	fprintf(stderr, " - read:  %s i2c_dev addr r reg_addr\n", prog_name);
	fprintf(stderr, " - write: %s i2c_dev addr w reg_addr data\n", prog_name);
	fprintf(stderr, "\n");
	fprintf(stderr, "i2c_dev  = /dev/ic2... device path\n");
	fprintf(stderr, "addr     = I2C _devide_ address\n");
	fprintf(stderr, "reg_addr = register (data) address in I2C chip\n");
	fprintf(stderr, "data     = data to write to device\n");
}

int main(int argc, char *argv[]) {
	int fd, i2c_addr, reg_addr, res, d;
	
	if (argc < 4) {
		help(argv[0]);
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
		fprintf(stderr, "ERROR set device address to 0x%02x: %s\n", i2c_addr, strerror(errno));
		return 3;
	}
	
	if (argv[3][0] == 'r' && argc == 5) { // odczyt
		
		if (argv[4][0] != '-') {
			// jeżeli jest podany to ustawiamy adres rejestru do odczytu
			// warto zauważyć że jest to robione jako WRITE do urządzenia I2C
			reg_addr = strtol(argv[4], NULL, 0);
			res = i2c_smbus_write_byte(fd, reg_addr);
			if (res < 0) {
				fprintf(stderr, "ERROR write (register address) %d to i2c device 0x%02x on %s: %s\n", reg_addr, i2c_addr, argv[1], strerror(errno));
				return 4;
			}
		}
		
		// czytamy dane z urządzenia
		res = i2c_smbus_read_byte(fd);
		if (res < 0) {
			fprintf(stderr, "ERROR read from i2c device 0x%02x on %s: %s\n", i2c_addr, argv[1], strerror(errno));
			return 5;
		}
		printf("0x%02x\n", res);
		
	} else if (argv[3][0] == 'w' && argc == 6) { // zapis
		d =  strtol(argv[5], NULL, 0);
		
		if (argv[4][0] != '-') {
			// jeżeli jest podany adres rejestru do zapisu to go używamy i wykonujemy zapis
			reg_addr = strtol(argv[4], NULL, 0);
			res = i2c_smbus_write_byte_data(fd, reg_addr, d);
			if (res < 0) {
				fprintf(stderr, "ERROR write %d to i2c device 0x%02x, register 0x%02x on %s: %s\n", d, i2c_addr, reg_addr, argv[1], strerror(errno));
				return 5;
			}
		} else {
			// w przeciwnym razie po prostu zapisujemy dane do urządzenia
			res = i2c_smbus_write_byte(fd, d);
			if (res < 0) {
				fprintf(stderr, "ERROR write %d to i2c device 0x%02x on %s: %s\n", d, i2c_addr, argv[1], strerror(errno));
				return 5;
			}
		}
		
	} else if (argv[3][0] == 'R' && argc == 5 && argv[4][0] != '-') { // odczyt z rejestru jedną funkcją
		
		reg_addr = strtol(argv[4], NULL, 0);
		res = i2c_smbus_read_byte_data(fd, reg_addr); // odczyt z rejestru o danym adresie może być wykonany także jedną funkcją (analogicznie jak zapis)
		if (res < 0) {
			fprintf(stderr, "ERROR read from i2c device 0x%02x, register 0x%02x on %s: %s\n", i2c_addr, reg_addr, argv[1], strerror(errno));
			return 5;
		}
		printf("0x%02x\n", res);
		
	} else {
		help(argv[0]);
		return 1;
	}
	
	close(fd);
}

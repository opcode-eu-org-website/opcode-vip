
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t time2str(
	const time_t* time, const char* timeZone, const char *format,
	char *buf, size_t bufLen, struct tm *tmPtr
);

int main() {
	time_t czas1 = time(0);
	printf("Od początku epoki upłynęło %d sekund\n", czas1);
	// początek epoki to: 1970-01-01 00:00:00 UTC
	// wynik jest niezależny od lokalnej strefy czasowej
	// (zawsze wyrażany jest w UTC)
	
	// jeżeli potrzebna jest większa precyzja to można użyć np.:
	struct timespec czas2;
	clock_gettime(CLOCK_REALTIME, &czas2);
	printf("Od poczotku epoki upłyneło %d sekund i %d ns\n",
		   czas2.tv_sec, czas2.tv_nsec);
	// na niektórych platformach (np. Linux) w clock_gettime()
	// wspierane są także inne zegary niż czasu rzeczywistego
	// np. podające czas monotoniczny lub od uruchomienia systemu
	
	char buf[128];
	
	// korzystamy z własnej funkcji tworzącej napis w oparciu o
	// format zmiennej czasowej ... co prawda do UTC jest gmtime(),
	// ale w połączeniu z strftime potrafi dawać złe wyniki
	// (np. dla "%s") ponadto funkcja taka pozwala także na
	// obsługę innych stref czasowych
	time2str(
		&(czas2.tv_sec), "UTC", "%Y-%m-%d %H:%M:%S %Z (%s)",
		buf, sizeof(buf), NULL
	);
	printf("Mamy teraz: %s\n", buf);
	
	time2str(
		&(czas2.tv_sec), NULL, "%Y-%m-%d %H:%M:%S %Z (%s)",
		buf, sizeof(buf), NULL
	);
	printf("Mamy teraz: %s\n", buf);
}

size_t time2str(
	const time_t* time, const char* timeZone, const char *format,
	char *buf, size_t bufLen, struct tm *tmPtr
) {
	// jeżeli podano tmPtr != NULL użyj podanej struktury,
	// w przeciwnym razie użyj lokalnej
	struct tm tmTmp;
	if (!tmPtr) {
		tmPtr = &tmTmp;
	}
	
	// jeżeli podano strefę czasową to
	// zapamiętaj oryginalną strefę i ustaw nową
	char oldTZ[128];
	if (timeZone) {
		strncpy(oldTZ, getenv("TZ"), 128);
		setenv("TZ", timeZone, 1);
		tzset();
	}
	
	// pobierz rozłożony czas w ustawionej strefie czasowej
	localtime_r(time, tmPtr);
	// zapisz sformatowany napis do bufora
	bufLen = strftime(buf, bufLen, format, tmPtr);
	
	// przywróć oryginalną strefę czasową
	if (timeZone) {
		setenv("TZ", oldTZ, 1);
		tzset();
	}
	
	return bufLen;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/resource.h>

char buf[64], *bufS;

int fun() {
	int i, j, x[10000000];
	
	for (i=0; i<17; i+=2) {
		for (j=0; j<20000; ++j) x[i*10000+j] = j;
		sleep(1);
		system(buf);
	}
}

int main() {
	snprintf(buf, 64, "ps -o 'vsize,size,rss,cmd' -p %d", getpid());
	system(buf);
	
	puts("zwiększam rozmiar stosu");
	struct rlimit rl;
	rl.rlim_cur = 2000000000;
	rl.rlim_max = rl.rlim_cur;
	if(setrlimit(RLIMIT_STACK, &rl))
		perror("Error in setrlimit()");
	
	system(buf);
	bufS = buf + strlen(buf);
	snprintf(bufS, 64 - (bufS-buf), " --no-headers");
	
	fun();
	*bufS = '\0'; system(buf); *bufS = ' ';
	fun();
}

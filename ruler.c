/* ruler [cols] -- print a column-count ruler */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

int
main (int argc, char **argv)
{

	int cols, rows, i, j, skip;
	char *buf, *p;

	cols = -1;
	if (argc > 1) {
		cols = atoi(argv[1]);
		if (cols == 0)
			exit(1);
	}
	if (cols == -1) {
		struct winsize ws;
		if (ioctl(0, TIOCGWINSZ, &ws) == -1) {
			perror("TIOCGWINSZ");
			exit(1);
		}
		if (ws.ws_col > 0) {
			cols = ws.ws_col;
		}
	}
	if (cols <= 0) {
		cols = 80;
	}
		
	buf = malloc(cols + 1);
	if (buf == NULL) {
		fputs("out of memory", stderr);
		exit(1);
	}

	rows = log10(cols);
	for (i = rows; i >= 0 ; i--) {
		skip = pow(10, i);
		p = buf;
		for (j = 1; j <= cols; j++) {
			if (j % skip)
				*p++ = ' ';
			else
				sprintf(p++, "%d", (j / skip) % 10);
		}
		buf[cols] = '\0';
		printf("%s\n", buf);
	}
	exit(0);
}

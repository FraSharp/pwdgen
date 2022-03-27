#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "pwdgen.h"

const char CHARS[] = "1234567890!$%&=?!_@#<>^*abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ";

char *pwdgen(uint_fast8_t len) {

	/* to generate a completely random number and different from the latest */
	sleep(1);

	time_t t;
	uint_fast8_t chars_len = strlen(CHARS);
	char *pwd = malloc((char)sizeof(len));

	srand((unsigned)time(&t));

	/* assigns a char from a random position of CHARS to pwd[i] */
	for (size_t i = 0; i < len; i++) {
		pwd[i] = CHARS[rand() % chars_len];
	}

	/* return the password */
	return pwd;
}

int main(int argc, char *argv[]) {

	uint_fast8_t len; /* 16 */
	char *pwd;

	if (argc == 2) {
		len = (uint_fast8_t)strtol(argv[1], NULL, 10);
	} else {
		len = 16;
	}

	/* don't print pwdgen(len) directly to avoid memory leaks due malloc() */
	pwd = pwdgen(len);

	/* print the actual password */
	printf("\n%s\n", pwd);

	/* free pwd only if it exists */
	if (pwd) { free(pwd); }

	return 0;
}


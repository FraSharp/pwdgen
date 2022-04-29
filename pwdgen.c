#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "pwdgen.h"

#define MAX_LEN 255

const char chars[] = "1234567890!$%&=?!_@#<>^*abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ";

char *pwdgen(uint_fast8_t len) {

	/* to generate a completely random number and different from the latest */
	sleep(1);

	time_t t;
	uint_fast8_t chars_len = strlen(chars);
	char *pwd = malloc(sizeof(char) *len);

	srand((unsigned)time(&t));

	/* assigns a char from a random position of chars to pwd[i] */
	for (size_t i = 0; i < len; i++) {
		pwd[i] = chars[rand() % chars_len];
	}

	/* return the password */
	return pwd;
}

int main(int argc, char *argv[]) {

	uint_fast8_t len; /* 16 */
	char *pwd;

	if (argc == 2) {
		/* if len is > 255, set it to 255 */
		if ((uint_fast8_t *)argv[1] > (uint_fast8_t *)MAX_LEN) {
			len = MAX_LEN;
		} else {
			len = (uint_fast8_t)strtol(argv[1], NULL, 10);
		}
	} else {
		len = 16;
	}

	/* don't print pwdgen(len) directly to avoid memory leaks due malloc() */
	pwd = pwdgen(len);

	/* print the actual password */
	printf("\n%s\n", pwd);

	/* free pwd only if it exists */
	if (pwd) {
		free(pwd);
	}

	return 0;
}


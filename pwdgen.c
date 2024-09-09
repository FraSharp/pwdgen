#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "pwdgen.h"

#define MAX_LEN 255

const char chars[] = "1234567890!$%&=?_@#<>^*+-,.:;()[]{}/|abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ";

char *pwdgen(uint_fast8_t len)
{

	/* to generate a completely random number and different from the latest */
	sleep(1);

	time_t t;
	uint_fast8_t chars_len = strlen(chars);
	char *pwd = malloc(sizeof(char) *len);

	srand((unsigned)time(&t));

	/* assigns a char from a random position of chars to pwd[i] */
	for (size_t i = 0; i < len; i++)
	{
		do {
			pwd[i] = chars[arc4random() % chars_len];
		} while (pwd[i] == pwd[i - 1] && strlen(pwd) > 0);
	}

	/* return the password */
	return pwd;
}

float calc_entropy(uint_fast8_t byte_count, uint_fast8_t pw_len)
{
	return pw_len * log(byte_count)/log(2);
}

int main(int argc, char *argv[])
{

	uint_fast8_t len; /* default password length: 16 */
	char *pwd;

	if (argc == 2) {
		/* if len is > 255, set it to 255 */
		if (strtol(argv[1], NULL, 10) > MAX_LEN) {
			len = MAX_LEN; /* password length: 255 */
		} else {
			len = (uint_fast8_t)strtol(argv[1], NULL, 10);
		}
	} else {
		len = 21;
	}

	/* don't print pwdgen(len) directly to avoid memory leaks due malloc() */
	pwd = pwdgen(len);

	/* print the actual password */
	printf("\nthe generated password is: %s\n", pwd);
	printf("\nthe entropy of the generated password is: %.2f bits\n\n", calc_entropy(strlen(chars), len));

	/* free pwd only if it isn't NULL */
	if (pwd) {
		free(pwd);
	}

	return 0;
}


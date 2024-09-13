#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include "pwdgen.h"

#define MAX_LEN 255
#define MAX_PWDS 16

const char chars[] = "1234567890!$%&=?_@#<>^*+-,.:;()[]{}/|abcdefghjklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWXYZ";

int pwd_len(uint_fast8_t len)
{
	return (len > MAX_LEN) ? MAX_LEN : len;
}

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

	uint_fast8_t len = 20; /* default password length: 20 */
	uint_fast8_t pwds_cnt = 1;
	float e_bits;
	char *pwd;

	switch (argc) {
		case 2:
			if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
				printf("pwdgen: version 1.0\n");
				exit(0);
			}

			if (strtol(argv[1], NULL, 10) > 0) {
				len = pwd_len(strtol(argv[1], NULL, 10));
			}
			break;
		case 3:
			len = pwd_len(strtol(argv[1], NULL, 10));
			pwds_cnt = (strtol(argv[2], NULL, 10) > MAX_PWDS) ? MAX_PWDS : (uint_fast8_t)strtol(argv[2], NULL, 10);
			break;
	}

	for (int i = 0; i < pwds_cnt; i++) {
		pwd = pwdgen(len);

		printf("\npassword #%d: \t%s", i + 1, pwd);
		free(pwd);
	}

	e_bits = calc_entropy(strlen(chars), len);
	printf("\n\nthe entropy of the generated password(s) is: %.2f bits. roughly %.1f guesses. \n\n", e_bits, pow(2, e_bits));

	return 0;
}


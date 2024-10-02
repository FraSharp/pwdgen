#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <getopt.h>
#include <math.h>
#include "pwdgen.h"

#define MAX_LEN 255
#define MAX_PWDS 16

const char lowercase[] = "abcdefghjklmnopqrstuvwxyz";
const char uppercase[] = "ABCDEFGHJKLMNOPQRSTUVWXYZ";
const char digits[] = "1234567890";
const char specials[] = "!$%&=?_@#^*+-,.:;";

char available_chars[MAX_LEN] = "";

int pwd_len(uint_fast8_t len)
{
	return (len > MAX_LEN) ? MAX_LEN : len;
}

uint_fast8_t rrand(uint_fast8_t bound) {
#if defined(__linux__)
	int seed;
	FILE *urandom = fopen("/dev/urandom", "r");
	fread(&seed, sizeof(seed), 1, urandom);
	fclose(urandom);
	srand(seed);
	return rand() % bound;
#endif
#if __has_include(<bsd/stdlib.h>) || __has_include(<stdlib.h>)
	return arc4random_uniform(bound);
#endif
	fputs("Your environment is not supported.\n", stderr);
	exit(EXIT_FAILURE);
}

char *pwdgen(uint_fast8_t len)
{
	uint_fast8_t chars_len = strlen(available_chars);
	char *pwd = malloc(sizeof(char) * (len + 1));

	if (chars_len == 0) {
		fputs("No characteres selected.\n", stderr);
		exit(EXIT_FAILURE);
	}

	if (pwd == NULL) {
		perror("Memory allocation failed:");
		exit(EXIT_FAILURE);
	}

	/* assigns a char from a random position of chars to pwd[i] */
	for (size_t i = 0; i < len; i++)
	{
		do {
			pwd[i] = available_chars[rrand(chars_len)];
		} while (i > 0 && pwd[i] == pwd[i - 1]);
	}

	/* shuffle password */
	for (size_t i = len - 1; i > 0; i--) {
		size_t j = rrand(i + 1);
		char temp = pwd[i];
		pwd[i] = pwd[j];
		pwd[j] = temp;
	}

	/* null terminate password */
	pwd[len] = '\0';

	/* return the password */
	return pwd;
}

float calc_entropy(uint_fast8_t byte_count, uint_fast8_t pw_len)
{
	return pw_len * log(byte_count) / log(2);
}

int main(int argc, char *argv[])
{

	uint_fast8_t len = 20;	   /* default password length: 20 */
	uint_fast8_t pwds_cnt = 3; /* default generated passwords: 1 */
	uint_fast8_t lower = 1, upper = 1, digit = 1, special = 1;
	int_fast8_t c;
	float e_bits;
	char *pwd;

	static struct option long_options[] = {
		 {0, 0, 0, 0}
	};

	while ((c = getopt_long(argc, argv, "vl:p:uLdsh", long_options, NULL)) != -1) {
	switch (c) {
		case 'h':
			printf("Usage: %s [-v] [-l length of password] [-p number of passwords] [-u no uppercase] [-L no lowercase] -[d no digits] [-s no specials]\n", argv[0]);
			printf("Options:\n");
			printf("  -v              Show version information.\n");
			printf("  -l length       Specify password length (default: %d).\n", len);
			printf("  -p count        Number of passwords to generate (default: %d, max: %d).\n", pwds_cnt, MAX_PWDS);
			printf("  -u              Exclude uppercase characters.\n");
			printf("  -L              Exclude lowercase characters.\n");
			printf("  -d              Exclude digits.\n");
			printf("  -s              Exclude special characters.\n");
			exit(EXIT_SUCCESS);
			break;

		case 'v':
			printf("pwdgen: version 1.c\n");
			exit(0);
			break;
		case 'l':
			if (strtol(optarg, NULL, 10) > 0) {
				len = pwd_len(strtol(optarg, NULL, 10));
			}
			break;
		case 'p':
			pwds_cnt = (strtol(optarg, NULL, 10) > MAX_PWDS) ? MAX_PWDS : (uint_fast8_t)strtol(optarg, NULL, 10);
			break;
		case 'u':
			upper = 0;
			break;
		case 'L':
			lower = 0;
			break;
		case 'd':
			digit = 0;
			break;
		case 's':
			special = 0;
			break;
		default:
			break;
	}
	}

	if (lower) strncat(available_chars, lowercase, MAX_LEN - strlen(available_chars) - 1);
	if (upper) strncat(available_chars, uppercase, MAX_LEN - strlen(available_chars) - 1);
	if (digit) strncat(available_chars, digits, MAX_LEN - strlen(available_chars) - 1);
	if (special) strncat(available_chars, specials, MAX_LEN - strlen(available_chars) - 1);

	for (int i = 0; i < pwds_cnt; i++) {
		pwd = pwdgen(len);

		printf("\npassword #%d: \t%s", i + 1, pwd);
		free(pwd);
	}

	e_bits = calc_entropy(strlen(available_chars), len);
	printf("\n\nthe entropy of the generated password(s) is: %.2f bits. roughly %.1f guesses. \n\n", e_bits, pow(2, e_bits));

	return 0;
}


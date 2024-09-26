#include <stdint.h>

extern const char lowercase[];
extern const char uppercase[];
extern const char digits[];
extern const char specials[];

int pwd_len(uint_fast8_t len);
uint_fast8_t rrand(uint_fast8_t bound);
char *pwdgen(uint_fast8_t len);
int main(int argc, char *argv[]);


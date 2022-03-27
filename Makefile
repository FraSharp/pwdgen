CC := clang
LD := ld.lld

pwdgen: pwdgen.c
	$(CC) pwdgen.c -o pwdgen -pedantic -W{error,all,extra,abi} --std=c11 -xc -lpthread \
		-Ofast -flto -march=native -pipe


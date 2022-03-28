CC 	:= clang
LD 	:= lld
OUTPUT 	:= pwdgen
BIN	:= /usr/local/bin

pwdgen: pwdgen.c
	$(CC) -fuse-ld=$(LD) pwdgen.c -o $(OUTPUT) -pedantic -W{error,all,extra,abi} --std=c11 -xc \
		-lpthread -Ofast -march=native -pipe

clean:
	-rm $(OUTPUT)

install: $(OUTPUT)
	mkdir -p $(BIN)
	sudo install -Dm755 $(OUTPUT) $(BIN)

uninstall: $(OUTPUT)
	sudo rm $(BIN)/$(OUTPUT)

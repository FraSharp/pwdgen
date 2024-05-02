CC 	:= clang
LD 	:= lld
INPUT   := pwdgen.c
OUTPUT 	:= pwdgen
BIN	:= /usr/local/bin

pwdgen: pwdgen.c
	$(CC) -fuse-ld=$(LD) $(INPUT) -o $(OUTPUT)

debug: pwdgen.c
	$(CC) -fuse-ld=$(LD) $(INPUT) -o $(OUTPUT) -pedantic -W{error,all,extra,abi} --std=c11

clean:
	-rm $(OUTPUT)

install: $(OUTPUT)
	mkdir -p $(BIN)
	sudo install -m755 $(OUTPUT) $(BIN)

uninstall: $(OUTPUT)
	sudo rm $(BIN)/$(OUTPUT)

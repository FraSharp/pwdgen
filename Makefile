LLVM := $(shell command -v llvm-config >/dev/null 2>&1 && echo "1" || echo "0")
ifeq ($(LLVM), 1)
	CC := clang
	LD := lld
else
	CC := gcc
	LD := ld
endif

INPUT   := pwdgen.c
OUTPUT 	:= pwdgen
ifeq ($(shell uname -s),Darwin)
	DBG_PKG := $(OUTPUT).dSYM
endif
BIN	:= /usr/local/bin

pwdgen: pwdgen.c
	$(CC) -fuse-ld=$(LD) $(INPUT) -o $(OUTPUT) --std=c11

debug: pwdgen.c
	$(CC) -fuse-ld=$(LD) $(INPUT) -o $(OUTPUT) -g -pedantic -W{error,all,extra,abi} --std=c11

clean:
	-rm -f $(OUTPUT)
ifeq ($(shell uname -s),Darwin)
	-rm -rf $(DBG_PKG)
endif

install: $(OUTPUT)
	mkdir -p $(BIN)
	sudo install -m755 $(OUTPUT) $(BIN)

uninstall: $(OUTPUT)
	sudo rm -f $(BIN)/$(OUTPUT)

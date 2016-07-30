OUT=gen_decathlon_input
SRC=$(wildcard *c)

RXVM_INC=/usr/local/include/librxvm
RXVM_LIB=/usr/local/lib

CFLAGS=-I$(RXVM_INC) -L$(RXVM_LIB) -lrxvm

all: $(SRC)
	$(CC) $^ -o $(OUT) $(CFLAGS)

clean:
	$(RM) $(OUT)


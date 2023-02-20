# Project: shrivastava
# Makefile created by ouzdeville
CC       = gcc
OBJ      = realmatrix.o main.o
LINKOBJ  = realmatrix.o main.o
#LIBS     = -L/usr/lib -lssl -lcrypto
INCS     = 
CXXINCS  = 
BIN      = Matrix.exe

LFLAGS=
CFLAGS= -c -Wall -I. 
RM       = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CC) -O3 $(LINKOBJ) -o $(BIN) $(LIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
gen: clean-custom
	$(CC) main_genparams.c -o main_genparams
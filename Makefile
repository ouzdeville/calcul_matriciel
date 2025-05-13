# Project: L2TDSI
# Makefile created by ouzdeville
CC       = gcc   #utilise le compilateur gcc
OBJ      = realmatrix.o main.o    #fichiers objets a lier ensemble.
LINKOBJ  = realmatrix.o main.o 
#LIBS     = -L/usr/lib -lssl -lcrypto
INCS     = 
CXXINCS  = 
BIN      = Matrix         #le nom de ton executable final sera matrix

LFLAGS=
CFLAGS= -c -Wall -I. 
RM       = rm -f    

.PHONY: all all-before all-after clean clean-custom
#la cible principale make va appeler la regle qui genere Matrix

all: all-before $(BIN) all-after   
#nettoie les fichiers compiler
clean: clean-custom
	${RM} $(OBJ) $(BIN)
	#compile tous les .o pour creer l'executable Matrix avec optimisations -03

$(BIN): $(OBJ)
	$(CC) -O3 $(LINKOBJ) -o $(BIN) $(LIBS)
#compilation de chaque.c en .o .Le $< c'est le .c,le $@ c'est le .o
%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
	
gen: clean-custom
	$(CC) main_genparams.c -o main_genparams

####################################################
# A remplir par vous
# Repertoire GMP
GMPDIR=/usr/local
# Vos sources C, par exemple : SRC=source.c
SRC=
# Vos sources C++, par exemple : SRCXX=source2.cxx
SRCXX=gencle.cpp main.cpp chiffre.cpp
# Vos executables C, par exemple : EXEC=progc
EXEC=
# Vos executables C++, par exemple : EXECXX=progcxx
EXECXX=gencle main chiffre dechiffre
####################################################
# ne pas toucher
INCDIR=-I${GMPDIR}/include
LIBDIR=-L${GMPDIR}/lib
RUNTIMELIB=
LIBS=-lgmp
LIBSXX=-lgmp
CC=gcc -g -c
CXX=g++ -g -c
LD=gcc -Xlinker -rpath -Xlinker ${RUNTIMELIB}
LDXX=g++ -Xlinker -rpath -Xlinker ${RUNTIMELIB}
OBJ=${SRC:.c=.o}
OBJXX=${SRCXX:.cpp=.o}
all: $(EXECXX)
%.o: %.c
		$(CC) $(INCDIR) $<
%.o: %.cxx
		$(CXX) $(INCDIR) $<
# A dupliquer éventuellement si autres executables
gencle: $(OBJXX) gencle.cpp
		$(CXX) -c $(INCDIR) $@.cpp
		$(LDXX) $@.o $@.o $(LIBDIR) $(LIBSXX) -o $@

main: $(OBJXX) main.cpp
		$(CXX) -c $(INCDIR) $@.cpp
		$(LDXX) $@.o $@.o $(LIBDIR) $(LIBSXX) -o $@

chiffre: $(OBJXX) chiffre.cpp
		$(CXX) -c $(INCDIR) $@.cpp
		$(LDXX) $@.o $@.o $(LIBDIR) $(LIBSXX) -o $@

dechiffre: $(OBJXX) dechiffre.cpp
		$(CXX) -c $(INCDIR) $@.cpp
		$(LDXX) $@.o $@.o $(LIBDIR) $(LIBSXX) -o $@

clean:
		rm -f $(EXEC:=.o) $(EXECXX) $(EXECXX:=.o) $(OBJ)
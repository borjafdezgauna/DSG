INC=/opt/local/include
LIB=/opt/local/lib
CC=/opt/local/bin/gcc-mp-4.8

LD=-l GL -l glut -l SOIL -l stdc++

test_escenario: src/Escenario.cpp src/TestEscenario.cpp
	$(CC) -o test_escenario src/TestEscenario.cpp src/Escenario.cpp \
-I $(INC) -L $(LIB) $(LD) -framework CoreFoundation 

clean:
	rm test_escenario

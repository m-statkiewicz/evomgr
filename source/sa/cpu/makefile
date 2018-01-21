all: clean sa.out

clean:
	rm -rf *.o 

symulate.o: symulate.cpp symulate.h
	g++ -c -g symulate.cpp -o symulate.o

timer.o: timer.cpp 
	g++ -c -g timer.cpp -o timer.o

point.o: point.cpp point.h
	g++ -c -g point.cpp -o point.o

method.o: method.cpp method.h
	g++ -c -g method.cpp -o method.o

sa.o: sa.cpp sa.h
	g++ -c -g sa.cpp 

sa.out: method.o point.o sa.o timer.o symulate.o 
	g++ method.o point.o sa.o timer.o symulate.o sa_main.cpp -o sa.out


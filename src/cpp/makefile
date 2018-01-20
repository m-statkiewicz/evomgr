all: clean sa.out db.out

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

sa.out: method.o point.o sa.o timer.o symulate.o dbwrapper.o
	g++ method.o point.o sa.o timer.o symulate.o dbwrapper.o sa_main.cpp -o sa.out -l sqlite3

dbwrapper.o: dbwrapper.cpp dbwrapper.h
	g++ -c -g dbwrapper.cpp  -o dbwrapper.o

db.out: dbwrapper.o
	g++ dbwrapper.o db_main.cpp -o db.out -l sqlite3
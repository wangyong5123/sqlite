CC = gcc

sqlite : sqlite3_db.o main.o
	$(CC) -lsqlite3 sqlite3_db.o main.o -o sqlite -lsqlite3

sqlite3_db.o : sqlite3_db.c sqlite3_db.h
	gcc -lsqlite3 sqlite3_db.c -c 
main.o : main.c
	gcc -lsqlite3 main.c -c 

.PHONY : clean

clean:
	rm -rf *.o
	rm -rf sqlite

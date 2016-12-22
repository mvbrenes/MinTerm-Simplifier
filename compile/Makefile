OBJS = main.o Column.o Chart.o Group.o Minterm.o
CC = g++
CFLAG = -std=c++11

sim: $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o sim
	
main.o: main.cpp Column.h Chart.h Group.h Minterm.h
	$(CC) $(CFLAG) -c main.cpp
	
Column.o: Column.h Column.cpp Group.h
	$(CC) $(CFLAG) -c Column.cpp
	
Chart.o: Chart.h Chart.cpp Minterm.h
	$(CC) $(CFLAG) -c Chart.cpp

Group.o: Group.h Group.cpp Minterm.h
	$(CC) $(CFLAG) -c Group.cpp
	
Minterm.o: Minterm.h Minterm.cpp
	$(CC) $(CFLAG) -c Minterm.cpp
	
clean:
	rm -rf *.o ./sim
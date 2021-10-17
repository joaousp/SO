output := jantar_executavel

CFLAGS :=
#CFLAGS += -DDEBUG

main : main.o monitor.o  
	gcc -o $(output) main.o monitor.o -lpthread -lrt

monitor.o : monitor.c monitor.h 
	gcc -c monitor.c $(CFLAGS)
	
main.o : main.c monitor.h 
	gcc -c main.c $(CFLAGS)

clean:
	rm *.o
	rm $(output)

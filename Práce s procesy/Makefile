#koncový FLAGS: 
FLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic -pthread -lrt

#pracovní FLAGS:
#FLAGS = -std=gnu99 -pthread -lrt

MAZANI = proj2 proj2.out

all:
	gcc $(FLAGS) main.c -o proj2
	
run: all
	./proj2 3 2 100 100 100
	cat proj2.out
	
clean:
	rm $(MAZANI)

CC=gcc
CFLAGS=-I.

all :  parallel_min_max parallel_sum

parallel_min_max : utils.o find_min_max.o  utils.h find_min_max.h
	$(CC) -o parallel_min_max utils.o find_min_max.o  parallel_min_max.c $(CFLAGS)

# zombie : zombie.o
# 	$(CC) -o zombie zombie.o W $(CFLAGS)

process_memory : process_memory.o
	$(CC) -o process_memory process_memory.o $(CFLAGS)

parallel_sum :  utils.o utils.h
	$(CC)  -pthread -o parallel_sum  utils.o parallel_sum.c $(CFLAGS)

utils.o : utils.h
	$(CC) -o utils.o -c utils.c $(CFLAGS)

find_min_max.o : utils.h find_min_max.h
	$(CC) -o find_min_max.o -c find_min_max.c $(CFLAGS)

# zombie.o : 
# 	$(CC) -o zombie.o -c zombie.c $(CFLAGS)

process_memory.o :
	$(CC) -o process_memory.o -c process_memory.c $(CFLAGS)


clean :
	rm utils.o find_min_max.o  parallel_min_max zombie.o zombie parallel_sum parallel_sum.o process_memory process_memory.o

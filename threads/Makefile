CC = gcc
CFLAGS = -pthread

all: producer_consumer

producer_consumer: producer_consumer.c
	$(CC) $(CFLAGS) -o $@ $^

run: producer_consumer
	./producer_consumer

clean:
	rm -f producer_consumer

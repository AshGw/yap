CC = gcc
CFLAGS = -Wall -Wextra
LIBS = -lmicrohttpd
SERVER_EXEC = server

$(SERVER_EXEC): server.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

serve: $(SERVER_EXEC)
	./$(SERVER_EXEC)

shut:
	killall $(SERVER_EXEC)

clean:
	rm -f $(SERVER_EXEC)

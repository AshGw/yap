CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lsqlite3 -ldl
TARGET = sqlite

all: $(TARGET)

$(TARGET): sqlite.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
	rm -f test.db

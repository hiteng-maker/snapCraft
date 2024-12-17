CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -lrt
TARGET = server-mq

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)
install:
	mkdir -p $(DESTDIR)/bin
	cp $(TARGET) $(DESTDIR)/bin/

clean:
	rm -f $(TARGET)


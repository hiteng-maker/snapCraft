CC = gcc
CFLAGS = -Wall
LDFLAGS = -lrt
TARGET = client-mq

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LDFLAGS)
install:
	mkdir -p $(DESTDIR)/bin
	cp $(TARGET) $(DESTDIR)/bin/
clean:
	rm -f $(TARGET)


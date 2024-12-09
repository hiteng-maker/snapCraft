CC = gcc
CFLAGS = -Wall -O2
TARGET = client

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c
install:
	mkdir -p $(DESTDIR)/bin
	cp $(TARGET) $(DESTDIR)/bin/
clean:
	rm -f $(TARGET)


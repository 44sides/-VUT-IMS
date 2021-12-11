CC = g++
CFLAGS = -std=c++11
run:
	$(CC) $(CFLAGS) source.cpp -o source

clean:
	rm -rf source
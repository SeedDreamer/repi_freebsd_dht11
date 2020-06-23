CC = clang

DHT11: DHT11.c time.o read_dht11.o
	$(CC) DHT11.c time.o read_dht11.o -o DHT11 -lgpio

read_dht11.o: read_dht11.c
	$(CC) -c read_dht11.c

time.o: time.c
	$(CC) -c time.c

clean:
	rm *.o



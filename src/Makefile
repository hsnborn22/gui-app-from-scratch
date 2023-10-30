main: main.c
	gcc -Wno-format -o main-bin main.c jsonParser.c httpsClient.c -lssl -lcrypto -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

clean:
	rm main
	

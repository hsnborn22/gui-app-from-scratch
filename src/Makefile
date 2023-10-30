COMPILER = gcc
PROGRAM = main
FLAGS = -lssl -lcrypto -Wno-deprecated-declarations -Wno-format-security -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic

${PROGRAM}: ${PROGRAM}.c
	${COMPILER} -Wno-format -o ${PROGRAM} ${PROGRAM}.c jsonParser.c httpsClient.c ${FLAGS}

clean:
	rm ${PROGRAM}
	

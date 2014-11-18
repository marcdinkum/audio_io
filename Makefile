CPP = g++
CC = gcc
CFLAGS = -I/usr/local/include -Wall -I../include
LDFLAGS= -L/usr/local/lib -lportaudio


all: sinewave sinephase sweep am fm delay filter toonladder

sinewave: sinewave.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sinewave.o audio_io.o $(LDFLAGS) -lpthread

sinephase: sinephase.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sinephase.o audio_io.o $(LDFLAGS) -lpthread

sweep: sweep.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sweep.o audio_io.o $(LDFLAGS) -lpthread

am: am.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) am.o audio_io.o $(LDFLAGS) -lpthread

fm: fm.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) fm.o audio_io.o $(LDFLAGS) -lpthread

delay: delay.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) delay.o audio_io.o $(LDFLAGS) -lpthread

filter: filter.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) filter.o audio_io.o $(LDFLAGS) -lpthread

toonladder: toonladder.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) toonladder.o audio_io.o $(LDFLAGS) -lpthread


.cpp.o:
	$(CPP) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm +111 -type f`


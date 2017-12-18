CPP = g++
CC = gcc
CFLAGS = -I/usr/local/include -Wall -I../include
LDFLAGS= -lportaudio


all: sinewave sinus sinephase sweep am fm delay filter \
        toonladder guitartuner smooth_harsh

sinewave: sinewave.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sinewave.o audio_io.o $(LDFLAGS) -lpthread

sinus: sinus.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sinus.o audio_io.o $(LDFLAGS) -lpthread

sinephase: sinephase.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) sinephase.o audio_io.o $(LDFLAGS) -lpthread

smooth_harsh: smooth_harsh.o audio_io.o
	$(CPP) -o $@ $(CFLAGS) smooth_harsh.o audio_io.o $(LDFLAGS) -lpthread

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

guitartuner: guitartuner.o audio_io.o keypress.o
	$(CPP) -o $@ $(CFLAGS) guitartuner.o audio_io.o keypress.o $(LDFLAGS) -lpthread

.cpp.o:
	$(CPP) -c $< $(CFLAGS)

.c.o:
	$(CPP) -c $<

clean:
	rm -f *.o
	rm -f `find . -perm /111 -type f`


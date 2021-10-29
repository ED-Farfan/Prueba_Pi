#*Variables globales
PROYECTO = principal
DESTDIR = /usr/local/bin
CFLAGS=-Wall
LFLAGS = -lpthread
CC=gcc
ARCHIVO_C := $(wildcard *.c)
ARCHIVO_O := $(ARCHIVO_C:.c=.o)
#Compilar programas
all: $(PROYECTO)
%.o : %.c
	$(CC) $< -c $(CFLAGS)	

$(PROYECTO): $(ARCHIVO_O)	
	@echo "\n$(ARCHIVO_O)"
	$(CC) $^ -o $@ $(LFLAGS) $(CFLAGS)	

.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo mkdir $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)
unistall:
	sudo rm $(DESTDIR)/$(PROYECTO)
clean:
	rm -f *.o $(PROYECTO) 
PROJECT = arpg
INCLUDES = \
	$(shell find . -type f -name "*.c")\
	$(shell find . -type f -name "*.h")\

all: build

build: $(PROJECT).pce

$(PROJECT).pce: $(INCLUDES)
	huc -O2 $(PROJECT).c

run: build
	mednafen $(PROJECT).pce

clean:
	rm -f *.pce *.s *.sym *.lst
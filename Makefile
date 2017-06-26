PDPATH ?= pure-data
CFLAGS = -I$(PDPATH)/src -fPIC -rdynamic -g 
CFLAGS += -O2 -ffast-math -funroll-loops -fomit-frame-pointer -fPIC \
		  -DPD

CFLAGS += -DHAVE_LIBDL=1 -DHAVE_UNISTD_H
CFLAGS += -DUSEAPI_DUMMY
include obj.mk

LDFLAGS = -lm -ldl -lportaudio 

default: pd.so

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

pd.so: pd.o $(OBJ)
	$(CC) $(CFLAGS) -shared $(OBJ) $< -o $@ $(LDFLAGS) -lsporth -lsoundpipe 

clean:
	rm -rf pd.so
	rm -rf pd.o
	rm -rf $(OBJ)

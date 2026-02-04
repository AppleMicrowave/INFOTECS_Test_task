CC       = gcc
CFLAGS  += -std=c++17 
# -Wall -Werror -Wextra

CCFILES  = app.cc utils.cc
OBJ      = $(CCFILES:%.cc=%.o)
LIBFILES = liblogger.cc liblogger.hh
LIB      = liblogger.so

.PHONY: all, test, clean

all: $(LIB) app

app: $(CCFILES)
	$(CC) $(CFLAGS) $^ -o $@ -lstdc++

$(LIB): $(LIBFILES)
	$(CC) $(CFLAGS) -fPIC -shared $^ -o $@ -lstdc++

clean:
	rm -rf *.o *.so app

CC        = gcc
CFLAGS   += -std=c++17 -Wall -Werror -Wextra

TARGET   := app
CCFILES  := app.cc
OBJ      := $(CCFILES:%.cc=%.o)
LIBFILES := liblogger.cc liblogger.hh
LIBOBJ   := liblogger.o
LIB      := liblogger.so

.PHONY: all, test, clean

all: $(LIB) $(TARGET)

# compile whole app with dynamic lib
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -L. -llogger -lstdc++ 

#build app obj
$(OBJ): $(CCFILES)
	$(CC) $(CFLAGS) -c $^ -o $@

#build .so file
$(LIB): $(LIBOBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@	

# build lib obj
$(LIBOBJ): $(LIBFILES)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf *.o *.so $(TARGET)

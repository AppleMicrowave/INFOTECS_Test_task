CC        = gcc
CFLAGS   += -std=c++17 -Wall -Werror -Wextra

TARGET   := app
CCFILES  := app.cc
OBJ      := $(CCFILES:%.cc=%.o)
LIBFILES := liblogger.cc liblogger.hh
LIBOBJ   := liblogger.o
LIB      := liblogger.so

.PHONY: all
all: lib $(TARGET)

# compile whole app with dynamic lib
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ -L. -llogger -lstdc++
	touch test.txt

#build app obj
$(OBJ): $(CCFILES)
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: lib
lib: $(LIB)

#build .so file
$(LIB): $(LIBOBJ)
	$(CC) $(CFLAGS) -shared $^ -o $@	

# build lib obj
$(LIBOBJ): $(LIBFILES)
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

.PHONY: clean
clean:
	rm -rf *.o *.so $(TARGET)

SOURCE := $(shell ls *.c $(TARGET)/*.c)

$(TARGET):
	$(CC) $(SOURCE) -I. -I$@/include -o $@.so -Os -s -shared -fPIC

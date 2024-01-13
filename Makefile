SOURCE := $(shell find $(TARGET) -name *.c)

$(TARGET):
	$(CC) $(SOURCE) -I $@ -I $@/include -o $@.so -Os -s -shared -fPIC

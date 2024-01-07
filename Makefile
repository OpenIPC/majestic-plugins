$(TARGET):
	$(CC) -I $@/include $@/$@.c -o $@.so -Os -s -shared -fPIC

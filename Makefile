$(TARGET): clean
	$(CC) -I include/$(TARGET) -shared $@.c -o $@.so -Os -s

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RETURN(f, ...) snprintf(common.buffer, sizeof(common.buffer), f, ##__VA_ARGS__); return

typedef struct {
	const char *cmd;
	void (*func)(const char *);
} table;

typedef struct {
	char buffer[512];
	table *list;
	int size;
} config;

extern config common;

void call_motion(const char* value);
void call_setup(const char* value);
void get_usage();

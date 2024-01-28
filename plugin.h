#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PRINTP(f, ...) snprintf(result, sizeof(result), f, ##__VA_ARGS__)

char *call_custom(const char *command, const char *value);

typedef struct {
	const char *cmd;
	void (*func)(const char *);
} table;

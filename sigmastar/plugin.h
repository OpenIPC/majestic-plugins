#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mi_common.h>
#include <mi_isp_iq.h>

#define PRINTP(f, ...) snprintf(result, sizeof(result), f, ##__VA_ARGS__)

extern char result[512];

void set_brightness(const char *value);
void set_contrast(const char *value);

struct table {
	const char *cmd;
	void (*func)(const char *);
};

static struct table list[] = {
	{ "brightness", &set_brightness },
	{ "contrast", &set_contrast },
};

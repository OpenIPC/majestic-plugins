#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <imp_isp.h>
#include <imp_system.h>
#include <su_base.h>

#define PRINTP(f, ...) snprintf(result, sizeof(result), f, ##__VA_ARGS__)

extern char result[512];

void set_again(const char *value);
void set_dgain(const char *value);
void set_brightness(const char *value);
void set_rotation(const char *value);

void get_cpu();
void get_device();
void get_model();
void get_system();
void get_version();

struct table {
	const char *cmd;
	void (*func)(const char *);
};

static struct table list[] = {
	{ "again", &set_again },
	{ "dgain", &set_dgain },
	{ "brightness", &set_brightness },
	{ "rotation", &set_rotation },
	{ "cpu", &get_cpu },
	{ "device", &get_device },
	{ "model", &get_model },
	{ "version", &get_version },
};

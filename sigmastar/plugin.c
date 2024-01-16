#include <plugin.h>

#define USAGE "Usage:"

char result[512];

char *plugin_call(const char *command, const char *value) {
	int size = sizeof(list) / sizeof(struct table);
	for (int i = 0; i < size; i++) {
		if (strstr(command, list[i].cmd)) {
			list[i].func(value);
			return result;
		}
	}

	PRINTP(USAGE);
	size_t sum = strlen(USAGE);
	for (int i = 0; i < size; i++) {
		sum += snprintf(result + sum,
			sizeof(result) - sum, " %s", list[i].cmd);
	}

	return result;
}

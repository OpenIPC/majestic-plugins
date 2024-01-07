#include <plugin.h>

void get_usage() {
	int sum = sprintf(common.buffer, "Usage:");
	for (int i = 0; i < common.size; i++) {
		sum += snprintf(common.buffer + sum,
			sizeof(common.buffer) - sum, " %s", common.list[i].cmd);
	}
}

char *plugin_call(const char *command, const char *value) {
	for (int i = 0; i < common.size; i++) {
		if (strstr(command, common.list[i].cmd)) {
			common.list[i].func(value);
			break;
		}
	}

	return common.buffer;
}

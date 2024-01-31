#include <plugin.h>

static void set_script(const char* file, const char* value) {
	if (!access(file, X_OK)) {
		sprintf(common.buffer, "%s %s", file, value);
		system(common.buffer);
		RETURN("Execute script: %s", file);
	} else {
		RETURN("Cannot access: %s", file);
	}
}

void call_motion(const char* value) {
	set_script("/usr/sbin/motion.sh", value);
}

void call_setup(const char* value) {
	set_script("/usr/sbin/setup.sh", value);
}

void get_usage() {
	int sum = sprintf(common.buffer, "Usage:");
	for (int i = 0; i < common.size; i++) {
		sum += sprintf(common.buffer + sum, " %s", common.list[i].cmd);
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

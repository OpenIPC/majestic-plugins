#include <plugin.h>

static char result[128];

static void set_script(const char* file, const char* value) {
	char cmd[64];
	if (!access(file, X_OK)) {
		PRINTP("Execute script: %s", file);
		sprintf(cmd, "%s %s", file, value);
		system(cmd);
	} else {
		PRINTP("Cannot access: %s", file);
	}
}

static void call_motion(const char* value) {
	set_script("/usr/sbin/motion.sh", value);
}

static void call_setup(const char* value) {
	set_script("/usr/sbin/setup.sh", value);
}

static table common[] = {
	{ "motion", &call_motion },
	{ "setup", &call_setup },
};

char *plugin_call(const char *command, const char *value) {
	for (size_t i = 0; i < sizeof(common) / sizeof(table); i++) {
		if (strstr(command, common[i].cmd)) {
			common[i].func(value);
			return result;
		}
	}

	return call_custom(command, value);
}

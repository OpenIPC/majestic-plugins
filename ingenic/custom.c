#include <imp_isp.h>
#include <imp_system.h>
#include <su_base.h>
#include <plugin.h>

static char result[256];

static void set_again(const char *value) {
	if (strlen(value)) {
		unsigned int index = atoi(value);
		if (IMP_ISP_Tuning_SetMaxAgain(index)) {
			PRINTP("IMP_ISP_Tuning_SetMaxAgain failed");
			return;
		}

		PRINTP("Set again: %d", index);
	} else {
		unsigned int current;
		if (IMP_ISP_Tuning_GetMaxAgain(&current)) {
			PRINTP("IMP_ISP_Tuning_GetMaxAgain failed");
			return;
		}

		PRINTP("Get again: %d", current);
	}
}

static void set_brightness(const char *value) {
	if (strlen(value)) {
		unsigned char index = atoi(value);
		if (IMP_ISP_Tuning_SetBrightness(index)) {
			PRINTP("IMP_ISP_Tuning_SetBrightness failed");
			return;
		}

		PRINTP("Set brightness: %d", index);
	} else {
		unsigned char current;
		if (IMP_ISP_Tuning_GetBrightness(&current)) {
			PRINTP("IMP_ISP_Tuning_GetBrightness failed");
			return;
		}

		PRINTP("Get brightness: %d", current);
	}
}

static void set_rotation(const char *value) {
	int index = strlen(value) ? atoi(value) : -1;

	switch (index) {
		case 0:
			IMP_ISP_Tuning_SetISPVflip(0);
			IMP_ISP_Tuning_SetISPHflip(0);
			break;

		case 1:
			IMP_ISP_Tuning_SetISPVflip(0);
			IMP_ISP_Tuning_SetISPHflip(1);
			break;

		case 2:
			IMP_ISP_Tuning_SetISPVflip(1);
			IMP_ISP_Tuning_SetISPHflip(0);
			break;

		case 3:
			IMP_ISP_Tuning_SetISPVflip(1);
			IMP_ISP_Tuning_SetISPHflip(1);
			break;

		default:
			PRINTP("Unknown rotation: %d", index);
			return;
	}

	PRINTP("Set rotation: %d", index);
}

static void get_cpu() {
	const char* info = IMP_System_GetCPUInfo();
	if (!info) {
		 PRINTP("IMP_System_GetCPUInfo failed");
		 return;
	}

	PRINTP("%s", info);
}

static table custom[] = {
	{ "again", &set_again },
	{ "brightness", &set_brightness },
	{ "rotation", &set_rotation },
	{ "cpu", &get_cpu },
};

char *call_custom(const char *command, const char *value) {
	for (size_t i = 0; i < sizeof(custom) / sizeof(table); i++) {
		if (strstr(command, custom[i].cmd)) {
			custom[i].func(value);
			return result;
		}
	}

	PRINTP("Plugin: %s %s", command, value);

	return result;
}

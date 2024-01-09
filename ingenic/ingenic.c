#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <imp/imp_isp.h>

#define getf(f) strstr(command, f)
#define printp(f, ...) snprintf(result, sizeof(result), f, ##__VA_ARGS__)

static char result[128];

static void set_brightness(const char *value) {
	if (strlen(value)) {
		int digit = atoi(value);
		if (IMP_ISP_Tuning_SetBrightness(digit)) {
			printp("IMP_ISP_Tuning_SetBrightness failed");
			return;
		}

		printp("Set brightness: %d", digit);
	} else {
		unsigned char current;
		if (IMP_ISP_Tuning_GetBrightness(&current)) {
			printp("IMP_ISP_Tuning_GetBrightness failed");
			return;
		}

		printp("Get brightness: %d", current);
	}
}

static void set_rotation(const char *value) {
	int digit = strlen(value) ? atoi(value) : -1;

	switch (digit) {
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
			printp("Unknown rotation: %d", digit);
			return;
	}

	printp("Set rotation: %d", digit);
}

char *plugin_call(const char *command, const char *value) {
	if (getf("brightness")) {
		set_brightness(value);
	} else if (getf("rotation")) {
		set_rotation(value);
	} else {
		printp("Command: %s, Value: %s", command, value);
	}

	return result;
}

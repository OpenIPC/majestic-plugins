#include <imp_isp.h>
#include <su_base.h>
#include <plugin.h>

static void set_again(const char *value) {
	if (strlen(value)) {
		unsigned int index = atoi(value);
		if (IMP_ISP_Tuning_SetMaxAgain(index)) {
			RETURN("IMP_ISP_Tuning_SetMaxAgain failed");
		}

		RETURN("Set again: %d", index);
	} else {
		unsigned int current;
		if (IMP_ISP_Tuning_GetMaxAgain(&current)) {
			RETURN("IMP_ISP_Tuning_GetMaxAgain failed");
		}

		RETURN("Get again: %d", current);
	}
}

static void set_brightness(const char *value) {
	if (strlen(value)) {
		unsigned char index = atoi(value);
		if (IMP_ISP_Tuning_SetBrightness(index)) {
			RETURN("IMP_ISP_Tuning_SetBrightness failed");
		}

		RETURN("Set brightness: %d", index);
	} else {
		unsigned char current;
		if (IMP_ISP_Tuning_GetBrightness(&current)) {
			RETURN("IMP_ISP_Tuning_GetBrightness failed");
		}

		RETURN("Get brightness: %d", current);
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
			RETURN("Unknown rotation: %d", index);
	}

	RETURN("Set rotation: %d", index);
}

static void get_version() {
	SUVersion version;
	if (SU_Base_GetVersion(&version)) {
		RETURN("SU_Base_GetVersion failed");
	}

	RETURN("%s", version.chr);
}

static table custom[] = {
	{ "again", &set_again },
	{ "brightness", &set_brightness },
	{ "rotation", &set_rotation },
	{ "version", &get_version },
	{ "motion", &call_motion },
	{ "setup", &call_setup },
	{ "help", &get_usage },
};

config common = {
	.list = custom,
	.size = sizeof(custom) / sizeof(table),
};

#include <imp_isp.h>
#include <su_base.h>
#include <plugin.h>

static void set_blackwhite(const char *value) {
	bool index = strlen(value) ? atoi(value) : false;
	if (IMP_ISP_Tuning_SetISPRunningMode(index)) {
		RETURN("IMP_ISP_Tuning_SetISPRunningMode failed");
	}

	RETURN("Set blackwhite: %d", index);
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

static void set_contrast(const char *value) {
	if (strlen(value)) {
		unsigned char index = atoi(value);
		if (IMP_ISP_Tuning_SetContrast(index)) {
			RETURN("IMP_ISP_Tuning_SetContrast failed");
		}

		RETURN("Set contrast: %d", index);
	} else {
		unsigned char current;
		if (IMP_ISP_Tuning_GetContrast(&current)) {
			RETURN("IMP_ISP_Tuning_GetContrast failed");
		}

		RETURN("Get contrast: %d", current);
	}
}

static void set_rotation(const char *value) {
	int index = strlen(value) ? atoi(value) : -1;

	switch (index) {
		case 0:
			IMP_ISP_Tuning_SetISPHflip(0);
			IMP_ISP_Tuning_SetISPVflip(0);
			break;

		case 1:
			IMP_ISP_Tuning_SetISPHflip(1);
			IMP_ISP_Tuning_SetISPVflip(0);
			break;

		case 2:
			IMP_ISP_Tuning_SetISPHflip(0);
			IMP_ISP_Tuning_SetISPVflip(1);
			break;

		case 3:
			IMP_ISP_Tuning_SetISPHflip(1);
			IMP_ISP_Tuning_SetISPVflip(1);
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
	{ "blackwhite", &set_blackwhite },
	{ "brightness", &set_brightness },
	{ "contrast", &set_contrast },
	{ "rotation", &set_rotation },
	{ "version", &get_version },
	{ "help", &get_usage },
};

config common = {
	.list = custom,
	.size = sizeof(custom) / sizeof(table),
};

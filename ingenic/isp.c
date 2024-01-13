#include <command.h>

void set_again(const char *value) {
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

void set_dgain(const char *value) {
	if (strlen(value)) {
		unsigned int index = atoi(value);
		if (IMP_ISP_Tuning_SetMaxDgain(index)) {
			PRINTP("IMP_ISP_Tuning_SetMaxDgain failed");
			return;
		}

		PRINTP("Set dgain: %d", index);
	} else {
		unsigned int current;
		if (IMP_ISP_Tuning_GetMaxDgain(&current)) {
			PRINTP("IMP_ISP_Tuning_GetMaxDgain failed");
			return;
		}

		PRINTP("Get dgain: %d", current);
	}
}

void set_brightness(const char *value) {
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

void set_rotation(const char *value) {
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

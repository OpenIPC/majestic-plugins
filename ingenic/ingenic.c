#include <stdio.h>
#include <imp/imp_isp.h>

static int set_brightness(int value) {
	if (IMP_ISP_Tuning_SetBrightness(value)) {
		printf("IMP_ISP_Tuning_SetBrightness failed");
		return 1;
	}

	printf("Set brightness: %d", value);

	return 0;
}

static int set_rotation(int value) {
	switch (value) {
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
			return 1;
	}

	printf("Set rotation: %d", value);

	return 0;
}

int plugin_call(int command, int value) {
	int result = 0;

	switch (command) {
		case 10:
			result = set_brightness(value);
			break;

		case 50:
			result = set_rotation(value);
			break;
	}

	return result;
}

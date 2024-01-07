#include <stdio.h>
#include <mi_common.h>
#include <mi_isp_iq.h>

static int set_brightness(int value) {
	MI_ISP_IQ_BRIGHTNESS_TYPE_t brightness;
	if (MI_ISP_IQ_GetBrightness(0, &brightness)) {
		printf("MI_ISP_IQ_GetBrightness failed");
		return 1;
	}

	brightness.bEnable = SS_TRUE;
	brightness.enOpType = SS_OP_TYP_MANUAL;
	brightness.stManual.stParaAPI.u32Lev = value;

	if (MI_ISP_IQ_SetBrightness(0, &brightness)) {
		printf("MI_ISP_IQ_SetBrightness failed");
		return 1;
	}

	printf("Set brightness: %d", value);

	return 0;
}

static int set_contrast(int value) {
	MI_ISP_IQ_CONTRAST_TYPE_t contrast;
	if (MI_ISP_IQ_GetContrast(0, &contrast)) {
		printf("MI_ISP_IQ_GetContrast failed");
		return 1;
	}

	contrast.bEnable = SS_TRUE;
	contrast.enOpType = SS_OP_TYP_MANUAL;
	contrast.stManual.stParaAPI.u32Lev = value;

	if (MI_ISP_IQ_SetContrast(0, &contrast)) {
		printf("MI_ISP_IQ_SetContrast failed");
		return 1;
	}

	printf("Set contrast: %d", value);

	return 0;
}

int plugin_call(int command, int value) {
	int result = 0;

	switch (command) {
		case 10:
			result = set_brightness(value);
			break;

		case 11:
			result = set_contrast(value);
			break;
	}

	return result;
}

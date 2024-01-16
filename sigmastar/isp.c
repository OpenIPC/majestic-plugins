#include <plugin.h>

void set_brightness(const char *value) {
	MI_ISP_IQ_BRIGHTNESS_TYPE_t brightness;
	if (MI_ISP_IQ_GetBrightness(0, &brightness)) {
		PRINTP("MI_ISP_IQ_GetBrightness failed");
		return;
	}

	if (!strlen(value)) {
		PRINTP("Get brightness: %d", brightness.stManual.stParaAPI.u32Lev);
		return;
	}

	int index = atoi(value);
	brightness.bEnable = SS_TRUE;
	brightness.enOpType = SS_OP_TYP_MANUAL;
	brightness.stManual.stParaAPI.u32Lev = index;

	if (MI_ISP_IQ_SetBrightness(0, &brightness)) {
		PRINTP("MI_ISP_IQ_SetBrightness failed");
		return;
	}

	PRINTP("Set brightness: %d", index);
}

void set_contrast(const char *value) {
	MI_ISP_IQ_CONTRAST_TYPE_t contrast;
	if (MI_ISP_IQ_GetContrast(0, &contrast)) {
		PRINTP("MI_ISP_IQ_GetContrast failed");
		return;
	}

	if (!strlen(value)) {
		PRINTP("Get contrast: %d", contrast.stManual.stParaAPI.u32Lev);
		return;
	}

	int index = atoi(value);
	contrast.bEnable = SS_TRUE;
	contrast.enOpType = SS_OP_TYP_MANUAL;
	contrast.stManual.stParaAPI.u32Lev = index;

	if (MI_ISP_IQ_SetContrast(0, &contrast)) {
		PRINTP("MI_ISP_IQ_SetContrast failed");
		return;
	}

	PRINTP("Set contrast: %d", index);
}

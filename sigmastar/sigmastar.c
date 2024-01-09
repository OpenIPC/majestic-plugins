#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mi_common.h>
#include <mi_isp_iq.h>

#define getf(f) strstr(command, f)
#define printp(f, ...) snprintf(result, sizeof(result), f, ##__VA_ARGS__)

static char result[128];

static void set_brightness(const char *value) {
	MI_ISP_IQ_BRIGHTNESS_TYPE_t brightness;
	if (MI_ISP_IQ_GetBrightness(0, &brightness)) {
		printp("MI_ISP_IQ_GetBrightness failed");
		return;
	}

	if (!strlen(value)) {
		printp("Get brightness: %d",
			brightness.stManual.stParaAPI.u32Lev);
		return;
	}

	int digit = atoi(value);
	brightness.bEnable = SS_TRUE;
	brightness.enOpType = SS_OP_TYP_MANUAL;
	brightness.stManual.stParaAPI.u32Lev = digit;

	if (MI_ISP_IQ_SetBrightness(0, &brightness)) {
		printp("MI_ISP_IQ_SetBrightness failed");
		return;
	}

	printp("Set brightness: %d", digit);
}

static void set_contrast(const char *value) {
	MI_ISP_IQ_CONTRAST_TYPE_t contrast;
	if (MI_ISP_IQ_GetContrast(0, &contrast)) {
		printp("MI_ISP_IQ_GetContrast failed");
		return;
	}

	if (!strlen(value)) {
		printp("Get contrast: %d",
			contrast.stManual.stParaAPI.u32Lev);
		return;
	}

	int digit = atoi(value);
	contrast.bEnable = SS_TRUE;
	contrast.enOpType = SS_OP_TYP_MANUAL;
	contrast.stManual.stParaAPI.u32Lev = digit;

	if (MI_ISP_IQ_SetContrast(0, &contrast)) {
		printp("MI_ISP_IQ_SetContrast failed");
		return;
	}

	printp("Set contrast: %d", digit);
}

char *plugin_call(const char *command, const char *value) {
	if (getf("brightness")) {
		set_brightness(value);
	} else if (getf("contrast")) {
		set_contrast(value);
	} else {
		printp("Command: %s, Value: %s", command, value);
	}

	return result;
}

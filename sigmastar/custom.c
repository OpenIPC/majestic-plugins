#include <mi_common.h>
#include <mi_isp_iq.h>
#include <mi_sys.h>
#include <plugin.h>

static char result[256];

static void set_brightness(const char *value) {
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

static void set_contrast(const char *value) {
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

static void get_version() {
	MI_SYS_Version_t version;
	if (MI_SYS_GetVersion(&version)) {
		PRINTP("MI_SYS_GetVersion failed");
		return;
	}

	PRINTP("%s", version.u8Version);
}

static table custom[] = {
	{ "brightness", &set_brightness },
	{ "contrast", &set_contrast },
	{ "version", &get_version },
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

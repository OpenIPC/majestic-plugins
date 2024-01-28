#include <plugin.h>
#include <mpi_isp.h>
#include <mpi_sys.h>

static char result[256];

static void set_brightness(const char *value) {
	ISP_CSC_ATTR_S attr;
	if (HI_MPI_ISP_GetCSCAttr(0, &attr)) {
		PRINTP("HI_MPI_ISP_GetCSCAttr failed");
		return;
	}

	if (!strlen(value)) {
		PRINTP("Get brightness: %d", attr.u8Luma);
		return;
	}

	int index = atoi(value);
	attr.u8Luma = index;

	if (HI_MPI_ISP_SetCSCAttr(0, &attr)) {
		PRINTP("HI_MPI_ISP_SetCSCAttr failed");
		return;
	}

	PRINTP("Set brightness: %d", index);
}

static void set_contrast(const char *value) {
	ISP_CSC_ATTR_S attr;
	if (HI_MPI_ISP_GetCSCAttr(0, &attr)) {
		PRINTP("HI_MPI_ISP_GetCSCAttr failed");
		return;
	}

	if (!strlen(value)) {
		PRINTP("Get contrast: %d", attr.u8Contr);
		return;
	}

	int index = atoi(value);
	attr.u8Contr = index;

	if (HI_MPI_ISP_SetCSCAttr(0, &attr)) {
		PRINTP("HI_MPI_ISP_SetCSCAttr failed");
		return;
	}

	PRINTP("Set contrast: %d", index);
}

static void get_version() {
	MPP_VERSION_S version;
	if (HI_MPI_SYS_GetVersion(&version)) {
		PRINTP("MI_SYS_GetVersion failed");
		return;
	}

	PRINTP("%s", version.aVersion);
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

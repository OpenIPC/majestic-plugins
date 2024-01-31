#include <plugin.h>
#include <mpi_isp.h>
#include <mpi_sys.h>

static void set_brightness(const char *value) {
	ISP_CSC_ATTR_S attr;
	if (HI_MPI_ISP_GetCSCAttr(0, &attr)) {
		RETURN("HI_MPI_ISP_GetCSCAttr failed");
	}

	if (!strlen(value)) {
		RETURN("Get brightness: %d", attr.u8Luma);
	}

	int index = atoi(value);
	attr.u8Luma = index;

	if (HI_MPI_ISP_SetCSCAttr(0, &attr)) {
		RETURN("HI_MPI_ISP_SetCSCAttr failed");
	}

	RETURN("Set brightness: %d", index);
}

static void set_contrast(const char *value) {
	ISP_CSC_ATTR_S attr;
	if (HI_MPI_ISP_GetCSCAttr(0, &attr)) {
		RETURN("HI_MPI_ISP_GetCSCAttr failed");
	}

	if (!strlen(value)) {
		RETURN("Get contrast: %d", attr.u8Contr);
	}

	int index = atoi(value);
	attr.u8Contr = index;

	if (HI_MPI_ISP_SetCSCAttr(0, &attr)) {
		RETURN("HI_MPI_ISP_SetCSCAttr failed");
	}

	RETURN("Set contrast: %d", index);
}

static void get_version() {
	MPP_VERSION_S version;
	if (HI_MPI_SYS_GetVersion(&version)) {
		RETURN("MI_SYS_GetVersion failed");
	}

	RETURN("%s", version.aVersion);
}

static table custom[] = {
	{ "brightness", &set_brightness },
	{ "contrast", &set_contrast },
	{ "version", &get_version },
	{ "motion", &call_motion },
	{ "setup", &call_setup },
	{ "help", &get_usage },
};

config common = {
	.list = custom,
	.size = sizeof(custom) / sizeof(table),
};

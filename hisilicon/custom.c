#include <mpi_ae.h>
#include <mpi_isp.h>
#include <mpi_sys.h>
#include <mpi_venc.h>
#include <mpi_vpss.h>
#include <plugin.h>

static void set_blackwhite(const char *value) {
	bool index = strlen(value) ? atoi(value) : false;

	VENC_CHN_PARAM_S param;
	if (HI_MPI_VENC_GetChnParam(0, &param)) {
		RETURN("HI_MPI_VENC_GetChnParam failed");
	}

	param.bColor2Grey = index;
	if (HI_MPI_VENC_SetChnParam(0, &param)) {
		RETURN("HI_MPI_VENC_SetChnParam failed");
	}

	RETURN("Set blackwhite: %d", index);
}

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

static void set_rotation(const char *value) {
	int index = strlen(value) ? atoi(value) : -1;

	VPSS_CHN_ATTR_S attr;
	if (HI_MPI_VPSS_GetChnAttr(0, 0, &attr)) {
		RETURN("HI_MPI_VPSS_GetChnAttr failed");
	}

	switch (index) {
		case 0:
			attr.bMirror = false;
			attr.bFlip = false;
			break;

		case 1:
			attr.bMirror = true;
			attr.bFlip = false;
			break;

		case 2:
			attr.bMirror = false;
			attr.bFlip = true;
			break;

		case 3:
			attr.bMirror = true;
			attr.bFlip = true;
			break;

		default:
			RETURN("Unknown rotation: %d", index);
	}

	if (HI_MPI_VPSS_SetChnAttr(0, 0, &attr)) {
		RETURN("HI_MPI_VPSS_SetChnAttr failed");
	}

	RETURN("Set rotation: %d", index);
}

static void get_isp_again() {
	ISP_EXP_INFO_S info;
	if (HI_MPI_ISP_QueryExposureInfo(0, &info)) {
		RETURN("HI_MPI_ISP_QueryExposureInfo failed");
	}

	RETURN("%d", info.u32AGain);
}

static void get_version() {
	MPP_VERSION_S version;
	if (HI_MPI_SYS_GetVersion(&version)) {
		RETURN("HI_MPI_SYS_GetVersion failed");
	}

	RETURN("%s", version.aVersion);
}

static table custom[] = {
	{ "blackwhite", &set_blackwhite },
	{ "brightness", &set_brightness },
	{ "contrast", &set_contrast },
	{ "rotation", &set_rotation },
	{ "isp_again", &get_isp_again },
	{ "version", &get_version },
	{ "motion", &call_motion },
	{ "setup", &call_setup },
	{ "help", &get_usage },
};

config common = {
	.list = custom,
	.size = sizeof(custom) / sizeof(table),
};

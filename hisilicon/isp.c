#include <plugin.h>

void set_brightness(const char *value) {
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

void set_contrast(const char *value) {
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

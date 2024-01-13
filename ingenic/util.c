#include <command.h>

void get_cpu() {
	const char* info = IMP_System_GetCPUInfo();
	if (!info) {
		 PRINTP("IMP_System_GetCPUInfo failed");
		 return;
	}

	PRINTP("%s", info);
}

void get_system() {
	IMPVersion version;
	if (IMP_System_GetVersion(&version)) {
		PRINTP("IMP_System_GetVersion failed");
		return;
	}

	PRINTP("%s", version.aVersion);
}

void get_device() {
	SUDevID devID;
	if (SU_Base_GetDevID(&devID)) {
		PRINTP("SU_Base_GetDevID failed");
		return;
	}

	PRINTP("%s", devID.chr);
}

void get_model() {
	SUModelNum modelNum;
	if (SU_Base_GetModelNumber(&modelNum)) {
		PRINTP("SU_Base_GetModelNumber failed");
		return;
	}

	PRINTP("%s", modelNum.chr);
}

void get_version() {
	SUVersion version;
	if (SU_Base_GetVersion(&version)) {
		PRINTP("SU_Base_GetVersion failed");
		return;
	}

	PRINTP("%s", version.chr);
}

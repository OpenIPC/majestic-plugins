#include <stdio.h>

void plugin_call(int command, int value) {
	switch (command) {
		case 1:
			printf("set_brightness: %d", value);
			break;

		case 2:
			printf("set_contrast: %d", value);
			break;

		case 3:
			printf("set_saturation: %d", value);
			break;
	}
}

void plugin_exit() {
	printf("plugin_exit\n");
}

#include <stdlib.h>
#include <stdio.h>

#include <glib.h>
#include "gnome-keyring.h"

#include "definitions.h"
#include "input.h"

int main(int argc, char * argv[]) {
	Mode mode;

	g_set_application_name(APPLICATION_NAME);

	process_arguments(argc, argv, &mode);

	if(mode == MODE_GET) {
		fprintf(stdout, "W: Mode \"get\" isn't implemented yet.\n");
	} else if (mode == MODE_SET) {
		fprintf(stdout, "W: Mode \"set\" isn't implemented yet.\n");
	}

	return EXIT_SUCCESS;
}

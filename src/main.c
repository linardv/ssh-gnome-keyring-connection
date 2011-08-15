#include <stdlib.h>
#include <stdio.h>

#include <glib.h>
#include "gnome-keyring.h"

#include "definitions.h"
#include "input.h"
#include "connector-keyring.h"

int main(int argc, char * argv[]) {
	char * name;
	Mode mode;

	g_set_application_name(APPLICATION_NAME);

	process_arguments(argc, argv, &mode, &name);

	if(mode == MODE_GET) {
		get_password(name);
	} else if (mode == MODE_SET) {
		set_password(name);
	} else {
		fprintf(stderr, "E: Could not determine which mode. (Assert false)");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

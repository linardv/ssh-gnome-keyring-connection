#include <stdlib.h>
#include <stdio.h>

#include <glib.h>

#include "definitions.h"

void print_usage() {
	puts("Usage:\n"
	     "    APPLICATION_NAME <mode> <name>\n"
	     "Parameters:\n"
	     "    mode     - either 'get' or 'set' (without quotes)\n"
	     "    name     - a name to identify the key\n"
	     "Notes:\n"
	     "    If mode is 'get', then the password is dumped to stdout.\n"
	     "    If mode is 'set', then the password is read from stdin.\n");
}

void process_arguments(int argc, char * argv[], Mode * mode, char ** name) {
	if(argc == 2 && g_ascii_strcasecmp(argv[1], "-h") == 0) {
		print_usage();
		exit(EXIT_FAILURE);
	}

	if(argc != 3) {
		fprintf(stderr, "E: Illegal usage...\n-- Invoke with -h for usage\n");
		exit(EXIT_FAILURE);
	}

	if(g_ascii_strcasecmp(argv[1], "get") == 0) {
		*mode = MODE_GET;
		*name = argv[2];
	} else if(g_ascii_strcasecmp(argv[1], "set") == 0) {
		*mode = MODE_SET;
		*name = argv[2];
	} else {
		fprintf(stderr, "E: Invalid mode: %s\n-- Invoke with -h for usage\n", argv[1]);
		exit(EXIT_FAILURE);
	}
}

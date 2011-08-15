#include <stdlib.h>
#include <stdio.h>

#include <glib.h>
#include "gnome-keyring.h"

#include "definitions.h"

char * retrieve_password(const char * name) {
	GnomeKeyringAttributeList * attributes;
	GnomeKeyringResult result;
	GList * found_list;
	GnomeKeyringFound * found;
	char * password;

	attributes = g_array_new(FALSE, FALSE, sizeof (GnomeKeyringAttribute));
	gnome_keyring_attribute_list_append_string(attributes, "name", name);
	gnome_keyring_attribute_list_append_string(attributes, "magic", APPLICATION_NAME);
     
	result = gnome_keyring_find_items_sync(GNOME_KEYRING_ITEM_GENERIC_SECRET, attributes, &found_list);
	gnome_keyring_attribute_list_free(attributes);
     
	if (result != GNOME_KEYRING_RESULT_OK) {
		return NULL;
	}

	if(found_list != NULL) {
		found = found_list->data;
		password = g_strdup(found->secret);
	} else {
		return NULL;
	}
     
	gnome_keyring_found_list_free(found_list);
     
	return password;
}

void get_password(const char * name) {
	char * password = retrieve_password(name);

	if(!password) {
		fprintf(stderr, "E: Failed to get the password of: %s\n", name);
		exit(EXIT_FAILURE);
	}

	puts(password);
	g_free(password);
}

int send_password(const char * name, const char * password) {
	GnomeKeyringAttributeList * attributes;
	GnomeKeyringResult result;
	guint item_id;
     
	attributes = g_array_new(FALSE, FALSE, sizeof (GnomeKeyringAttribute));
	gnome_keyring_attribute_list_append_string(attributes, "name", name);
	gnome_keyring_attribute_list_append_string(attributes, "magic", APPLICATION_NAME);

	result = gnome_keyring_item_create_sync(NULL, GNOME_KEYRING_ITEM_GENERIC_SECRET, name, attributes, password, TRUE, &item_id);

	gnome_keyring_attribute_list_free(attributes);
	return (result == GNOME_KEYRING_RESULT_OK);
}

void set_password(const char * name) {
	char * read_success;
	int send_success;

	char password[MAX_PASSWORD_LENGTH];
	*password = '\0';
	read_success = fgets(password, MAX_PASSWORD_LENGTH, stdin);

	if(read_success == NULL) {
		fprintf(stderr, "E: Failed to read password.\n");
		exit(EXIT_FAILURE);
	}

	send_success = send_password(name, password);

	if(!send_success) {
		fprintf(stderr, "E: Failed to set the password of: %s\n", name);
		exit(EXIT_FAILURE);
	}
}

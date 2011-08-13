CC = gcc
CCFLAGS = -Wall -O3 `pkg-config --cflags --libs gnome-keyring-1 glib-2.0` -o ssh-gnome-keyring-connection

build:
	$(CC) $(CCFLAGS) src/*.c


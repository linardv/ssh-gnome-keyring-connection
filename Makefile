CC = gcc
CCFLAGS = -Wall -Wextra -O3 `pkg-config --cflags --libs gnome-keyring-1 glib-2.0` -o ssh-kc
BASE_INSTALL = /usr/local/bin

build:
	$(CC) $(CCFLAGS) src/*.c

install:
	cp ssh-kc $(BASE_INSTALL)
	chmod +x $(BASE_INSTALL)/ssh-kc

install-defaults:
	if [ ! -d "${HOME}/.ssh-kc" ]; then mkdir ${HOME}/.ssh-kc; cp scripts/ssh-kc-autorun.sh ${HOME}/.ssh-kc; mkdir ${HOME}/.ssh-kc/scripts; cp scripts/ssh-kc-askpass-default.sh ${HOME}/.ssh-kc/scripts; else echo "${HOME}/.ssh-kc folder already present, so we are not touching it.";fi

uninstall:
	rm $(BASE_INSTALL)/ssh-kc

purge:
	rm -r ${HOME}/.ssh-kc

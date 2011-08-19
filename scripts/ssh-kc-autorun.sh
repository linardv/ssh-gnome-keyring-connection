#!/bin/bash

## This script can be called by your session manager (e.g: gnome-session) when
## you log in. Once done, the passphrases to all your SSH keys will be read
## from the keyring and the keys added to your ssh-agent.

## You can change and add the keys that will be loaded by changing the relevant
## fields in the configuration section below. Each key as a script that queries
## ssh-kc for the passphrase and a location of the key-file itself. A sensible
## default is already provided which can function as an example.

## Start configuration section

nb_configs=1

base_script="${HOME}/.ssh-kc/scripts/ssh-kc-askpass-"
base_key="${HOME}/.ssh/"

script_files[0]="${base_script}default.sh"
key_files[0]="${base_key}id_rsa"

## End configuration section

for ((i=0; i < ${nb_configs}; i++))
do
	SSH_ASKPASS="${script_files[${i}]}" ssh-add "${key_files[${i}]}" < /dev/null
done

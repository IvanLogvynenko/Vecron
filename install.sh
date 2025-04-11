#!/bin/bash

vecron_home=$HOME/.config/vecron

echo "Installing Vecron"
go install github.com/IvanLogvynenko/vecron@latest

echo "Setting up default templates"
mkdir -p $vecron_home
cp -r ./templates $vecron_home

# shell_name="$(basename "$SHELL")"
# read -p "Autodefined path to rc file is ~/.${shell_name}rc. Is that right? [y/n]? " yn
# case $yn in 
# 	[yY])
# 		shell_config="$HOME/.${shell_name}rc"
# 		;;
# 	[nN])
# 		read -p "Enter path to your shell config: " shell_config
# 		;;
# 	*) 
# 		rm -rf "$CPPCH_CONF/.conf"
# 		echo "Invalid option. Start over."
# 		exit 1
# 		;;
# esac

echo "You are ready to GO"


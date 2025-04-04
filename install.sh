#!/bin/bash

vecron_home=$HOME/.config/vecron

echo "Installing Vecron"
go install github.com/IvanLogvynenko/vecron@latest

echo "Setting up default templates"
mkdir -p $vecron_home
cp -r ./templates $vecron_home

echo "You are ready to GO"


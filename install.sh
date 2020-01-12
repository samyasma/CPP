#!/bin/bash

echo "Welcome to Smoke - v1.0 - ASMA Samy - BELKADA Younes"
echo "You need to install [SDL2/SDL2_ttf/SFML_audio] [Y/N]?"

read input

if [ $input == "Y" ]; then
	echo "Installing SDL2 ..."
	sudo apt-get install libsdl2-2.0
	echo "Installing SDL2_ttf ..."
	sudo apt-get install libsdl2-ttf-dev
	echo "Installing SFML_audio"
	sudo apt-get install libsfml-dev
	echo "Libraries installed !"
fi

echo "building the game ..."

make

echo "Installation completed, now to run the game type ./game then enter."
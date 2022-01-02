#!/bin/bash

files=( "img2pbf" "pbf2img" "pbf2imgbulk" )
installdir=/usr/local/bin

if [ -n "$1" ]; then
	# uninstall
	for file in "${files[@]}"; do
		echo "Uninstalling ${installdir}/${file}"
		rm -rf "${installdir}/${file}"
	done
else
	# install
	for file in "${files[@]}"; do
		echo "Installing ${installdir}/${file}"
		cp "tools/${file}" ${installdir}
	done
fi

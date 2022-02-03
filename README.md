# PixelBuffer

PixelBuffer datastructure with helper functions.

	pixelbuffer/color.h
	pixelbuffer/pixelbuffer.h
	pixelbuffer/vec2.h

To use the tools, have python3 and pip3 installed:

	sudo apt install python3.9 python3-pip

Install Pillow:

	python3 -m pip install --upgrade pip
	python3 -m pip install --upgrade Pillow

## examples

See the [Canvas](https://github.com/rktrlng/canvas) project for examples on how to use this code.

## install

	$ sudo ./install.sh

output:

	cp tools/* /usr/local/bin/
	cp -r pixelbuffer /usr/local/lib/

## uninstall

	$ sudo ./install.sh -u

output:

	rm -f /usr/local/bin/img2pbf
	rm -f /usr/local/bin/pbf2img
	rm -f /usr/local/bin/pbf2imgbulk
	rm -rf /usr/local/lib/pixelbuffer

## MS Windows

Use WSL to install and use PixelBuffer tools.

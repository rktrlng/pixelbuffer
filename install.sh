#!/bin/bash

set -x #echo on

if [ -n "$1" ]; then
	# uninstall
	rm -f /usr/local/bin/img2pbf
	rm -f /usr/local/bin/pbf2img
	rm -f /usr/local/bin/pbf2imgbulk
else
	# install
	cp tools/* /usr/local/bin/
fi

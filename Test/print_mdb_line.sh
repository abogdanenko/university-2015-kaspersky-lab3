#!/bin/bash
#
# usage: script INPUT_FILE
#
# Prints virus database file line
#
# 1403368:5c254da7d549224d3a805397bb237971:SimpleAntivirusScanner.Test-GovoritMoskva.wav

file="$1"
size="$(stat --format="%s" "$file")"
base=$(basename "$file")
name=${base// /_}
# make array, $md5 is first elem, which is md5 sum
md5=($(md5sum "$file"))
echo $size:$md5:SimpleAntivirusScanner.Test-$name

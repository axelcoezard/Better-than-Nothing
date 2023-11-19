#!/bin/bash

for shader in $(find ${1:-$(pwd)} -name "*.vert" -o -name "*.frag"); do
	glslc $shader -o "$shader.spv"
	echo "Compiled $shader to $shader.spv"
done

#!/bin/bash

for shader in $(find ${1:-$(pwd)} -name "*.vert" -o -name "*.frag");
do
	rm -f "$shader.spv"
	echo "Compiling GLSL shader $shader.spv"
	glslc $shader -o "$shader.spv"
done

#!/bin/bash

# Install all required tools using apt
sudo apt install cmake -y
sudo apt install vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools -y
sudo apt install libglfw3-dev libglm-dev -y
sudo apt install doxygen doxygen-gui doxygen-doc -y
sudo apt install wget -y

# Insall all required packages for Github actions
sudo apt install libxinerama-dev libxcursor-dev libxi-dev -y

# Install glslc using the downloaded archive
wget https://storage.googleapis.com/shaderc/artifacts/prod/graphics_shader_compiler/shaderc/linux/continuous_clang_release/419/20230623-090916/install.tgz
tar -xvzf install.tgz
sudo cp ./install/bin/glslc /usr/local/bin/
sudo rm -rf install.tgz ./install/

# Install all required tools for libsndfile
sudo apt install -y autoconf autogen automake build-essential libasound2-dev \
	libflac-dev libogg-dev libtool libvorbis-dev libopus-dev libmp3lame-dev \
	libmpg123-dev pkg-config python3

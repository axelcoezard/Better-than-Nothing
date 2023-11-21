#!/bin/bash

# ==================================================================================================
# Variables
# ==================================================================================================

destination_folder="Better-than-Nothing/docs"

# ==================================================================================================
# Script
# ==================================================================================================

mkdir -p $destination_folder
rm -rf $destination_folder/*

doxygen Doxyfile &>/dev/null

echo -e "Doxygen documentation updated and avalaible here:"
echo -e "=> \e[1;32mfile://$PWD/$destination_folder/html/index.html\e[0m"

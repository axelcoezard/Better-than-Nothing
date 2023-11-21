#!/bin/bash

# ==================================================================================================
# Variables
# ==================================================================================================

destination_folder="Better-than-Nothing/Documentation"
source_folder="$destination_folder/html"

# ==================================================================================================
# Script
# ==================================================================================================

rm -rf $destination_folder
mkdir $destination_folder

doxygen Doxyfile &>/dev/null

mv $source_folder/* $destination_folder
rm -rf $source_folder

echo -e "Doxygen documentation updated and avalaible here:"
echo -e "=> \e[1;32mfile://$PWD/$destination_folder/index.html\e[0m"

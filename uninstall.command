#!/bin/bash

echo
echo

while true; do
    read -p "Do you wish to uninstall DAQlib for user $USER [Y/N]? " yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "    Invalid option $yn.  Please enter Y or N.";;
    esac
done
echo

INSTALL_DIR="$HOME/Library/APSC160"
echo Removing DAQ from "$INSTALL_DIR"
rm -rf "$INSTALL_DIR"

TEMPLATE_DIR="$HOME/Library/Developer/Xcode/Templates/Application"
echo Removing Xcode Template from "$TEMPLATE_DIR"
rm -rf "$TEMPLATE_DIR/DAQ.xctemplate"

echo 
echo Uninstallation complete.
echo
echo

#!/bin/bash

DIRNAME=`dirname "$0"`

echo
echo

while true; do
    read -p "Do you wish to install DAQlib for user $USER [Y/N]? " yn
    case $yn in
        [Yy]* ) break;;
        [Nn]* ) exit;;
        * ) echo "    Invalid option $yn.  Please enter Y or N.";;
    esac
done
echo

INSTALL_DIR="$HOME/Library/APSC160"
echo Installing DAQlib to "$INSTALL_DIR"
rm -rf "$INSTALL_DIR"
mkdir -p "$INSTALL_DIR"
cp -R "$DIRNAME/DAQlib" "$INSTALL_DIR/DAQlib"

TEMPLATE_DIR="$HOME/Library/Developer/Xcode/Templates/Application/"
echo Installing Xcode Template to "$TEMPLATE_DIR"
rm -rf "$TEMPLATE_DIR"
mkdir -p "$TEMPLATE_DIR"
cp -R "$DIRNAME/DAQlib/Xcode/DAQ.xctemplate" "$TEMPLATE_DIR/DAQ.xctemplate"

echo 
echo Installation complete.
echo
echo

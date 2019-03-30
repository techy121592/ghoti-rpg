#!/bin/bash

if [ ! -f ./linuxdeploy-x86_64.AppImage ]; then
    wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
    chmod +x ./linuxdeploy-x86_64.AppImage
fi

if [ ! -d ./AppDir/ ]; then
    rm -R ./AppDir
fi

cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make -j8
make install DESTDIR=AppDir
cp -R ../game-library/res ./AppDir/usr/bin/
./linuxdeploy-x86_64.AppImage --appdir AppDir -d ./ghoti-rpg.desktop -i ./ghoti-rpg.svg --output appimage

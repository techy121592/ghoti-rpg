#!/bin/bash

rm -R ./AppDir
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make -j8
make install DESTDIR=AppDir
cp -R ./game-library/res ./AppDir/usr/bin/
./linuxdeploy-x86_64.AppImage --appdir AppDir -d ./appimage/ghoti-rpg.desktop -i ./appimage/ghoti-rpg.svg --output appimage

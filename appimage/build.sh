#!/bin/bash

if [ ! -f ./linuxdeploy-x86_64.AppImage ]; then
    wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
    chmod +x ./linuxdeploy-x86_64.AppImage
    sed -i 's|AI\x02|\x00\x00\x00|' ./linuxdeploy-x86_64.AppImage
fi

if [ ! -d ./AppDir/ ]; then
    rm -R ./AppDir
fi

cmake .. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
make -j8
make install DESTDIR=AppDir
cp -R ../game-library/res ./AppDir/usr/bin/
./linuxdeploy-x86_64.AppImage --appdir AppDir -d ./ghoti-rpg.desktop -i ./ghoti-rpg.svg --output appimage
mv ./Ghoti_RPG-*-x86_64.AppImage /output

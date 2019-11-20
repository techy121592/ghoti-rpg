FROM archlinux:latest
MAINTAINER David Welch<techy121592@gmail.com>

RUN pacman -Syu --noconfirm
RUN pacman -S --noconfirm base-devel git cmake make gcc python3 pulseaudio jack python python-pip pkg-config nasm libxaw imake wget fuse
RUN pip install conan
RUN useradd nas
RUN mkdir /nas && chown nas:nas /nas
RUN echo "nas ALL= NOPASSWD: /usr/bin/pacman" >> /etc/sudoers

USER nas
WORKDIR /nas
RUN curl -O https://aur.archlinux.org/cgit/aur.git/snapshot/nas.tar.gz &&\
    tar -xvf nas.tar.gz &&\
    cd nas &&\
    makepkg -si --noconfirm &&\
    cd .. &&\
    rm -R ./nas

USER root
RUN userdel nas

COPY . /ghoti-rpg
WORKDIR /ghoti-rpg/appimage

VOLUME /output

CMD ["./build.sh"]
# Updated build script to use Conan to manage libraries

I ended up taking a minor detour on adding the start sequence because I was trying to build this on Windows and the libraries that I was using proved to make it much harder to get it working on there.

In the hopes that it would make it easier to port my game to as many system, I have started using Conan to manage this project's libraries. The cmake script takes care of installing the required libraries and then uses the Conan variables to include the headers and link the libraries. So far it seems to be working, but it is including more libraries into the linking process than I would like.

I will deal with that later, but for now this will work. I still need to try this new build process on Windows to see if it works on there too before I merge this into master, so I have my fingers crossed.

If that works, then I can either try using ffmpeg to add video support or TheanoPlay which would requiring including libraries like libogg, libvorbis, and libtheora, but either way that should be easier now.

Now back to the start sequence.
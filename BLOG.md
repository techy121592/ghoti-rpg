# Added XML settings & general improvements

Converted std::list to std::vector because it is supposed to get better performance; also made some changes recommended by my IDE.
Made some static functions private and made some public wrappers for them; my IDE kept suggesting to use the static functions directly, rather than the way I intended it to be used.

I also added the ability to customize the Main Menu using an XML file.
This has control over the location of the button, the button images, and what map is loaded first.
This will make it easier for other people to come along and make a game using my code with only the minimal changes.

Next I will add the ability to create a sequence animation using ffmpeg, which will allow us to use a video file for the starting sequence animation.
One of the benefits of this will be later on when we want to add cut-scenes we will be able to just use video files, which helps me by not worrying about those details and the other people using this to make their games, because they will be able to use standard video editors to create the cut-scenes.

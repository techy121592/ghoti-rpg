# Possible end to this particular code-base

Hello to everybody that is reading this,

Despite working on this game for years, I don't know if it is a bug in the library or an issue with my new computer,
but the lag in GhotiRPG became so bad that I am not sure exactly where I am going to go next.

After some troubleshooting I was able to trace down the occasional hickup to SDL_PollEvent, which is in SDL2, so that
really leaves me with 2 choices either to download the libraries code and start going through that to find the bug or
starting a new project using different tools to create the game.
Every so often SDL_PollEvent take 1+ seconds even though there are no events. I have removed my threads, so I know it
isn't an issue with my threading and when I remove it, it becomes a whole lot faster.

I have started a conversation with the other people that I am trying to work with to make this game to see what they
think, but so far it seems like we are going to swap tools.
The one that I have suggested is [Godot](https://godotengine.org/) if we are going to swap tools(which considering how
much time I expect learning SDL2's code would take me, I am willing to start a new project with reservations.)
If I am being completely honest, this project will feel like a failure if I swap tools, but I would rather complete a
project than constantly spinning my wheels.
This has been my pet project for years and is one of the large reason I wrote this blogging software.

If you haven't heard of Godot it is essentially an open source alternative to Unity and based on what I have seen and
heard it seems to have come a long way in the past few years; I would really suggest checking them out.
If you just want to see a demo reel [check this one out.](https://www.youtube.com/watch?v=MGHN3t7RR84)

The code for this project will remain available [here](https://git.ghotigames.com/dwelch/ghoti-rpg) whether or not we
keep working on it.
I have included the changes in a branch with the timing logging to show the issue I ran into with SDL_PollEvent.

Have a great day,

David
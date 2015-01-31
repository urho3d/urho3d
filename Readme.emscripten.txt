This branch was branched from the 1.32 tag and has been modified to build a subset of the Urho3D library with emscripten for use in web browsers.

Much of the changes were borrowed from the AtomicRuntime github repository[1].
Anything taken from there were from files marked with the standard Urho license header text. Many thanks to the Atomic Game Engine developers! 

Make sure you have the latest emscripten installed and updated on your build system. You can find it at [2].

Use the cmake_emscripten.sh to create the direectory emscripten-build/. Once complete, cd to there and type #make Urho3D

Once the library has been built, you can build the samples. There is a build script buildEmscriptenSamples.sh which you can copy to the emscripten-build directory and modify for your setup.

WHAT DOESN'T WORK 
* The new build system. The old one barely works and I don't grok the new one yet, hence the branch at the 1.32 tag rather than git HEAD.
* Sound.
* Terrain rendering.
* Networking. Javascript can only use http and websockets protocols so it's not likely that kNet will ever function.
* Mouse locking.
* Angelscript. There appears to be some issues with generic calling conventions.
* Anything else I haven't tested yet.

 Have fun! :)

[1] https://github.com/AtomicGameEngine/AtomicRuntime
[2] http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html





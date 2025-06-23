# PKMN

A super awesome and high quality attempt to recreate the first generation pokemon games (Red, Blue, etc.) in C++. I will also attempt to remove many of the bugs that have plagued players for nearly 30 years at this point.

I have chosen C++ as my language for this as it retains much of the same lower-level features as C, allowing me to more closely recreate the original games which were in a unique assembly language, as well as having many utilities that make my job easier, such as classes. I could implement it completely in C but I see no need when I could effectively recreate most of the C++ features through structs in C anyway.

I will try to make this a faithful recreation, meaning that while I will be leaving out many bugs (like the 1/256 glitch and the error in Focus Energy), I will leave in intentional features, however strange, such as bug being super effective against poison and no dragon-type moves existing besides dragon rage.

In order to preserve as much of the original game experience as possible, my implementation of most things will mirror the exact function of the original games, but I will be using some more modern programming techniques and tools (such as classes, non-binary data types, etc.). For example, I will decompress pokemon sprite data through the exact same algorithm as the original game, but the algorithm may not be implemented the exact same way.

I will also be taking advantage of having multitudes more memory available than the original GB did. I will be able to keep all of the text graphics in memory constantly alongside all other graphics that are needed, where the original game has to be very selective about what is retained in memory as there is very little space to go around.

For those wondering, MissingNo. (as it exists in the original game) will not be present in my version. This is due to the following:
A. The appearance of most glitch entities in the original pokemon games is determined by the processor reading out-of-bounds junk data (usually game code) as graphics data. Because that is inherently reliant on the data in memory at and following the pointer provided to the algorithm, it will result in different outputs on each system dependent on the state of that device's memory. As my machine's hard drive is not exactly identical to the cartridge ROM of the original pokemon red/blue games, even if I deliberately allow the algorithm to malfunction, the result will not be the same as the original game.
B. The production of the MissingNo. sprite and other similar pokemon is cause by buffer overflow and reading out of bounds data. Since this project is being done in C++, any attempts at doing so will most likely result in the program receiving a segmentation fault from the system and terminating, preventing the malfunctioning algorithm from ever finishing.

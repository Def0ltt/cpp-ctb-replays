# cpp-ctb-replays
**Completely not ready but you can use it if you want**

SFML is already in the project so its technically ready to use.

**How to parse replays:**

Since im really smart, no parser is built in, SO:
- Get raw replay data with any parser (https://github.com/Swan/osuReplayParser this one works)

- Replace symbols "|" and "," with a line skip (http://www.unit-conversion.info/texttools/add-line-breaks/ this one works)

- Save both **parsed** replays in the same directory with **main.cpp** with the names, "catchthing1.txt" and "catchthing2.txt"

- Done!

Compile **main.cpp** in **Visual Studio 2019** and be happy! (no)

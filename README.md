# Sporth-PD

A sporth plugin that allows one to run pure-data patches from inside of Sporth.

The plugin has the following limitations:

- No GUI control (headless)
- Mono
- No MIDI (probably)
- Patch is "read only"

To compile:

1. Clone the [pure-data](https://www.github.com/pure-data/pure-data) repo.
2. Clone this repo inside the pure-data directory.
3. Inside the sporth-pd directory, run "make". 
4. Make sure things work with "sporth test.sp". If all is well, a 5-second
audio file called "test.wav" should contain some blippy sounds. 

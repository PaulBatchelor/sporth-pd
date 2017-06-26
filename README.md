# Sporth-PD

A sporth plugin that allows one to run pure-data patches from inside of Sporth.

The plugin has the following limitations:

- No GUI control (headless)
- Mono
- No MIDI (probably)
- Patch is "read only"

To compile:

1. Clone this rep.
2. Grab the submodules with "git submodule init" and "git submodule update".
3. Run "make"
4. Test out the program with "sporth test.sp". This should generate a 5 second
audio file called "test.wav", which plays sinusoidal blips!

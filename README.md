# FM Synthesizer

## Project summary

### One-sentence description of the project

A polyphonic FM synthesizer with highly flexible parameter modulation.

### Additional information about the project

Our synthesizer aims to be a highly flexible instrument which is both easy to use and inspiring for the musician. The instrument's design emphasizes an exploration of interesting new sounds without requiring extensize prior knowlege about synthesis.

Our **target audience** is any musician looking for a highly tweakable instrument capable of producing novel/unique sound.
**Main functionality**: Our synth will take the form of a standardized plugin, easily usable with and OS and DAW. The foundation of our signal processing relies on frequency modulation(FM). FM allows for highly complex sounds that would otherwise be unattainable. On top of this, our synth will allow for very powerful paramater modulation through the use of numerous LFOs (Low Frequency Oscillators).The combination of these two design choices will allow for very insteresting and surprising results for the musician.

## Installation

### Prerequisites
 - **Windows** Visual Studio (2015 and later)
 - **OSX** Xcode
DAW that supports VST3 or AU

### Dependencies

**JUCE Framework:** a C++ framework that streamlines the installation, development, and distribution process for audio software.

### Installation Steps

1. Install Visual Studio(Windows) or XCode(OSX).
2. Install the JUCE framework:
 - https://shop.juce.com/get-juce
 - The "education" license is free and sufficent for our needs.
 - Follow the simple installation instructions for JUCE according to your OS.
3. Clone this repo (fmSynthesizer) to your machine
4. Open Projucer (located in your JUCE installation folder) and create a new project.
 - Select Audio Plugin
 - Uncheck "use global path" option and click "Create"
 - Open the plugin settings and inside of "plugin characterstics" select: "plugin is a synth" and "plugin MIDI input"
5. Delete all of the files that have been generated within your project
6. Drag the files from fmSynth/Source into your project
7. Press "Save and Open in IDE"
8. Once the IDE has opened, build the project
9. OSX: The plugin should now be installed and recognized in your IDE of choice
10. Windows: in the Juce project folder, navigate to Builds\VisualStudio\x64\VST3
 - This is where the built VST3 is located. Installation of VST3 plugins is simple but varies depending on your DAW of choice.


## Functionality

Currently, the synth only has a few features. Once the plugin is running within your DAW:
 - The synth plugin will be looking for midi signals for note input 
 - Select the carrier wave type (sin, square, or sawtooth) via the dropdown menu
 - Set the filter cutoff frequency using the filter cutoff slider

## Known Problems

 - There is an audible "click" when notes start. This expected as we have not implemented an envelope yet.

 - Several GUI elements are not functional, as they have not been implemented yet. (modulator section, volume, octave selection, etc)


## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## License

See `LICENSE.txt`

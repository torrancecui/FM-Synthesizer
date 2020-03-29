# The Höller

A polyphonic FM synthesizer with highly flexible parameter modulation.

### Additional information

Our synthesizer aims to be a highly flexible instrument which is both easy to use and inspiring for the musician. The instrument's design emphasizes an exploration of interesting new sounds without requiring extensize prior knowlege about synthesis.

Our **target audience** is any musician looking for a highly tweakable instrument capable of producing novel/unique sound.
**Main functionality**: Our synth will take the form of a standardized plugin, easily usable with and OS and DAW. The foundation of our signal processing relies on frequency modulation (FM). FM allows for highly complex sounds that would otherwise be unattainable. On top of this, our synth will allow for very powerful parameter modulation through the use of numerous LFOs (Low Frequency Oscillators).The combination of these two design choices will allow for very insteresting and surprising results for the musician.

## Installation

### Prerequisites
 - MinGW (Windows Only)
 - CMAKE
 - Python 3
 - DAW that supports VST3 or AU

### Dependencies

**JUCE Framework:** a C++ framework that streamlines the installation, development, and distribution process for audio software.

**FRUT:** an extension of JUCE that is used to convert its build files into a CMakeList.txt.

### Installation Steps

1. Clone repo: https://github.com/ucsb-cs48-w20/fmSynthesizer/
2. cd fmSynth/
3. To configure the build files, run: python3 configure.py
4. To compile the files in src/, run: python3 run.py
5. find the VST/AU/Standalone application in build/

## Functionality

 - Holler has three executables:
    - Standalone application - support for MIDI instruments
    - VST Plugin - support for common DAWs (Windows, MacOS, Unix)
    - AU Plugin (MacOS)
  
 - The VST/AU can be loaded as a plugin with your DAW, taking in MIDI note and control input.
     - Outputs audio that can be chained with an arbitrary number of effects.
     - All adjustable parameters can be controlled by the DAW.
     
 - The Holler is a frequency modulation synthesizer, where a carrier signal's frequency is modulated by another signal.
 
 - 12 voice polyphonic triggered by MIDI input.
 
 - There are two chained modulators that modulate the carrier signal.
 
 - For each signal, the user can select from a variety of different wave types: Noise, Triangle, Saw, Sine, Square.
 
 - Modulating signals have the following parameters: wave type, octave change, detune, and amount.
 
 - Carrier signal has the same parameters except the amount knob.
 
 - ADSR envelopes are applied to each note.

## Known Problems
 
 - Triangle wave occassionally bugs out when modulating another signal.
 
 - Text positioning is slightly inconsistent between OSes
 

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request

## License

See `LICENSE.txt`

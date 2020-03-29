//PolySynth.h

#pragma one

#include "../JuceLibraryCode/JuceHeader.h"

class PolySynth
{
public:
    
    PolySynth (MidiKeyboardState& keyState): keyboardState (keyState) {}
    
    ~PolySynth()
    {
        synth.clearSounds();
        synth.clearVoices();
    }
    
    int getNumVoices() const noexcept
    {
        return synth.getNumVoices();
    }
    
    SynthesiserVoice* getVoice(int index) const
    {
        return synth.getVoice(index);
    }
    
    /**
     @brief Add a certain number of voices to the PolySynth.
     
     @param T1 : A class that derives from the SynthesiserVoice class (provided by JUCE).
     
     @param  T2 : A class that derives from the SynthesiserSound class (provided by JUCE).
     
     @param number : The amount of voices to be added to the PolySynth.
     */
    template<typename T1, typename T2>
    void addVoice(int number, AudioProcessorValueTreeState* params)
    {        
        static_assert(std::is_base_of<SynthesiserVoice, T1>::value,
                      "Second type must derive from the SynthesiserVoice class.");
        static_assert(std::is_base_of<SynthesiserSound, T2>::value,
                             "First type must derive from the SynthesiserSound class.");
        
        for (auto i = 0; i < number; ++i)
            synth.addVoice (new T1(params, blockSize));
        
        synth.addSound (new T2());
    
    }
    
    void clearSounds()
    {
       synth.clearSounds();
    }
    
    void clearVoices()
    {
        synth.clearVoices();
    }
    
    void prepareToPlay (double sampleRate, int blockSize)
    {
        this->blockSize = blockSize;
        synth.setCurrentPlaybackSampleRate (sampleRate);
        midiCollector.reset (sampleRate);
    }
    
    MidiMessageCollector* getMidiCollector()
    {
        return &midiCollector;
    }
    
     void renderNextAudioBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples, MidiBuffer& incomingMidi)
    {
        outputBuffer.clear();
        
        midiCollector.removeNextBlockOfMessages (incomingMidi, numSamples);

        keyboardState.processNextMidiBuffer (incomingMidi, startSample,
                                             numSamples, true);

        synth.renderNextBlock (outputBuffer, incomingMidi,
                               startSample, numSamples);
    }
    
private:
    MidiKeyboardState& keyboardState;
    MidiMessageCollector midiCollector;
    Synthesiser synth;
    int blockSize;
};

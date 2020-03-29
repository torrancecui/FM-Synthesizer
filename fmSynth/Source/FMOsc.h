//
//  FMOsc.h
//  fmSynth
//
//  Created by Jack Kilgore on 2/19/20.
//



#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ModOscillators.h"
#include "CarrOscillators.h"

struct FMSound : public SynthesiserSound
{

    FMSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }

};

class FMVoice : public SynthesiserVoice
{
public:
    
    FMVoice(int blockSize) : ModBuffer(1, blockSize)
    {
        params = NULL;
        mCarrier.isCarrier(true, &ModBuffer);
        mModulator.isCarrier(false, nullptr);
    }
    
    FMVoice(AudioProcessorValueTreeState* params, int blockSize) : ModBuffer(1, blockSize), mModulator(params),
    mModulator_1(params), mCarrier(params)
    {
        this->params = params;
        mCarrier.isCarrier(true, &ModBuffer);
        mModulator.isCarrier(false, nullptr);
        mModulator_1.isCarrier(true, &ModBuffer);
        mModulator_1.isRecycleOutput(true);
        mCarrier.isRecycleOutput(true);
    }

    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<FMSound*> (sound) != nullptr;
    }
    
    /**
     @brief Set x in the equation ModulatorFrequency = CarrierFrequency * x;
     */
    void setModMultiple(int value);
    
    /**
        @brief Set f in the equation ModulatorFrequency = CarrierFrequency *( x + f);
                where f is a number between 0 and 1. For detuning the modulator.
    */
    void setModDetune(float value);
    
    void startNote(int midiNoteNumber, float velocity,
        SynthesiserSound* sound, int currentPitchWheelPosition) override;

    void stopNote(float velocity, bool allowTailOff) override;

    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    

private:
    
    ModOscVoice_0 mModulator;
    ModOscVoice_1 mModulator_1;
    CarrOscVoice_0 mCarrier;
    
    AudioProcessorValueTreeState* params;
    AudioBuffer<float> ModBuffer;
 
};

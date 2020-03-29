//
//  CarrOscillators.h
//  fmSynth
//
//  Created by Jack Kilgore on 2/22/20.
//

#pragma one

#include "Oscillator.h"

struct CarrOscSound_0 : public OscillatorSound
{

    CarrOscSound_0() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }

};

/**
 An OscillatorVoice with modulation capabilities in mind.
 */
class CarrOscVoice_0 : public OscillatorVoice
{
public:

    CarrOscVoice_0() {
        params = NULL;
    }
    CarrOscVoice_0(AudioProcessorValueTreeState* params) : OscillatorVoice(params){
    }

    bool canPlaySound(SynthesiserSound* sound) override
    {
       return dynamic_cast<CarrOscSound_0*> (sound) != nullptr;
    }
    
    void startNote(int midiNoteNumber, float velocity,
                   SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;
    
protected:
    void parameterUpdatePerBlock() override;
    void parameterUpdatePerSample() override {};
};

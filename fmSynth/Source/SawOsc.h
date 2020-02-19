//
//  SawOsc.hpp
//  fmSynth
//
#pragma one

#include "../JuceLibraryCode/JuceHeader.h"

struct SawSound : public SynthesiserSound
{

    SawSound() {}

    bool appliesToNote(int) override { return true; }
    bool appliesToChannel(int) override { return true; }

};

class SawVoice : public SynthesiserVoice
{
public:

    SawVoice() {}

    bool canPlaySound(SynthesiserSound* sound) override
    {
        return dynamic_cast<SawSound*> (sound) != nullptr;
    }

    //    DUMMY FUNCTION
    //    void setParam1(float* param1);

    void startNote(int midiNoteNumber, float velocity,
        SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;

    void stopNote(float /*velocity*/, bool allowTailOff) override;

    void pitchWheelMoved(int) override {}
    void controllerMoved(int, int) override {}

    void renderNextBlock(AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

private:
    float saw(float currentAngle);
    bool resetCheck = false;
    void angleCap(); // call after you increment currentAngle to avoid overflows

    float nextSample = 0.0, delta = 0.0,
        currentAngle = 0.0, angleDelta = 0.0,
        level = 0.0, tailOff = 0.0, twoPi = 0.0;
};

//
//  SquareOsc.h
//  fmSynth
//
#pragma one

#include "../JuceLibraryCode/JuceHeader.h"

struct SquareSound : public SynthesiserSound
{
    
    SquareSound() {}    
    
    bool appliesToNote    (int) override        { return true; }
    bool appliesToChannel (int) override        { return true; }
    
};

class SquareVoice : public SynthesiserVoice
{
public:
    
    SquareVoice() {}
    
    bool canPlaySound (SynthesiserSound* sound) override
    {
        return dynamic_cast<SquareSound*> (sound) != nullptr;
    }
    
//    DUMMY FUNCTION 
//    void setParam1(float* param1);
    
    void startNote (int midiNoteNumber, float velocity,
                    SynthesiserSound* sound, int /*currentPitchWheelPosition*/) override;
    
    void stopNote (float /*velocity*/, bool allowTailOff) override;
    
    void pitchWheelMoved (int) override      {}
    void controllerMoved (int, int) override {}
    
    void renderNextBlock (AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    
private:
     void angleCap(); // call after you increment currentAngle to avoid overflows

     float currentAngle = 0.0, angleDelta = 0.0,
            level = 0.0, tailOff = 0.0, twoPi = 0.0;
};

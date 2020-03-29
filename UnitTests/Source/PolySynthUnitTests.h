
#pragma once
#include "../../fmSynth/Source/PolySynth.h"
#include <assert.h>


class PolySynthVoiceTest : public UnitTest
{
    public:
    PolySynthVoiceTest() : UnitTest("Basic Poly Synth testing","PolySynth") {} //name,category


    void runTest() override  //contents of the test
    {
        MidiKeyboardState keyboardState;
        PolySynth Test(keyboardState);
        Test.clearVoices();
        Test.clearSounds();
        assert(Test.getNumVoices() == 0); //JUCE's built in expect() method segfaults for some reason,so using c++ assert
        std::cout << "Poly Synth test success!\n"; 
    }
};
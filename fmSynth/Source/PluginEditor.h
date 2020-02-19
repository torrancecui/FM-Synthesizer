/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class FmSynthAudioProcessorEditor  : public AudioProcessorEditor,
                                     private Slider::Listener
{
public:
    FmSynthAudioProcessorEditor (FmSynthAudioProcessor&);
    ~FmSynthAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    void sliderValueChanged(Slider* slider) override;

    void WaveSelectChanged();

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    FmSynthAudioProcessor& processor;
    Slider cutoffSlider;
    Slider volumeSlider;
    Slider octaveKnob;
    Slider cmRatioKnob;
    Slider modAmtKnob;

    Label textLabel;
    ComboBox modWaveSelect;
    ComboBox carWaveSelect;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FmSynthAudioProcessorEditor)
};

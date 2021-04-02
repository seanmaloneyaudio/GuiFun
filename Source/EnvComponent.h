#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class EnvComponent  : public juce::Component
{
public:
    //==============================================================================
    EnvComponent();
    ~EnvComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //void sliderValueChanged (juce::Slider *slider) override;
    float attack = 0.0f;
    float decay = 0.0f;
    float sustain = 0.0f;
    float release = 0.0f;
    float velocityPeak = 0.5f;
    float velocitySustain = 0.5f;
    float velocityRelease = 0.5f;
private:
    //==============================================================================
    // Your private member variables go here...
    float phase       = 0.0f;
    float phaseDelta  = 0.0f;
    float frequency   = 5000.0f;
    float amplitude   = 0.2f;

    double sampleRate = 0.0;
    int expectedSamplesPerBlock = 0;
    juce::Point<float> lastMousePosition;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvComponent)
};

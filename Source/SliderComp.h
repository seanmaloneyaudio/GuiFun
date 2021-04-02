/*
  ==============================================================================

    SliderComp.h
    Created: 19 Feb 2021 8:38:21am
    Author:  Sean Maloney

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EnvComponent.h"
#include "SeansLookAndFeel.h"
//==============================================================================
/*
*/
class SliderComp  : public juce::Component, public juce::Slider::Listener
{
public:
    SliderComp();
    ~SliderComp() override;

    void paint (juce::Graphics&) override;
    void sliderValueChanged (juce::Slider *slider) override;
    void resized() override;

private:
    SeansLookAndFeel seansLookAndFeel;
    juce::Slider sliderA;
    juce::Slider sliderD;
    juce::Slider sliderS;
    juce::Slider sliderR;
    juce::Label attackLabel;
    juce::Label decayLabel;
    juce::Label sustainLabel;
    juce::Label releaseLabel;
    
    
    juce::TextButton gap;
    
    float attackPos = 0.0f;
    float attackPosY = 0.0f;
    float decayPos = 0.0f;
    float sustainPos = 0.0f;
    float releasePos = 0.0f;
    EnvComponent envelope;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SliderComp)
};

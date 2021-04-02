/*
  ==============================================================================

    SliderComponent.cpp
    Created: 19 Feb 2021 8:38:21am
    Author:  Sean Maloney

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SliderComp.h"
#include "EnvComponent.h"

//==============================================================================
SliderComp::SliderComp()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(envelope);
    addAndMakeVisible(gap);
    gap.setLookAndFeel(&seansLookAndFeel);
    
    sliderA.setLookAndFeel(&seansLookAndFeel);
    sliderA.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderA.setRange(0.0f, 1.0f);
    sliderA.setValue(0.5f);
    sliderA.addListener(this);
    sliderA.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30);
    addAndMakeVisible(sliderA);
    addAndMakeVisible(attackLabel);
    attackLabel.setText("Attack", juce::dontSendNotification);
    attackLabel.attachToComponent(&sliderA, false);
    attackLabel.setJustificationType(juce::Justification::centredBottom);
    
    
    
    sliderD.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderD.setRange(0.0f, 1.0f);
    sliderD.setValue(0.5f);
    sliderD.addListener(this);
    sliderD.setLookAndFeel(&seansLookAndFeel);
    sliderD.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30);
    addAndMakeVisible(sliderD);
    addAndMakeVisible(decayLabel);
    decayLabel.setText("Decay", juce::dontSendNotification);
    decayLabel.attachToComponent(&sliderD, false);
    decayLabel.setJustificationType(juce::Justification::centredBottom);
    
    sliderS.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderS.setRange(0.0f, 1.0f);
    sliderS.setValue(0.5f);
    sliderS.addListener(this);
    sliderS.setLookAndFeel(&seansLookAndFeel);
    sliderS.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30);
    addAndMakeVisible(sliderS);
    addAndMakeVisible(sustainLabel);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    sustainLabel.attachToComponent(&sliderS, false);
    sustainLabel.setJustificationType(juce::Justification::centredBottom);
    
    sliderR.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    sliderR.setRange(0.0f, 1.0f);
    sliderR.setValue(0.5f);
    sliderR.addListener(this);
    sliderR.setLookAndFeel(&seansLookAndFeel);
    sliderR.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 60, 30);
    addAndMakeVisible(sliderR);
    addAndMakeVisible(releaseLabel);
    releaseLabel.setText("Release", juce::dontSendNotification);
    releaseLabel.attachToComponent(&sliderR, false);
    releaseLabel.setJustificationType(juce::Justification::centredBottom);
}

SliderComp::~SliderComp()
{
}

void SliderComp::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SliderComp::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    auto area = getLocalBounds();
    envelope.setBounds(area.removeFromTop(getHeight() / 3));
    gap.setBounds(area.removeFromTop(40));
    auto ADSRarea = area.removeFromTop((getHeight() / 3));
    gap.setBounds(area.removeFromTop(40));
    sliderA.setBounds(ADSRarea.removeFromLeft(getWidth()/4));
    sliderD.setBounds(ADSRarea.removeFromLeft(getWidth()/4));
    sliderS.setBounds(ADSRarea.removeFromLeft(getWidth()/4));
    sliderR.setBounds(ADSRarea.removeFromLeft(getWidth()/4));
    
}

void SliderComp::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &sliderA)
    {
        //attackPos = sliderA.getValue();
        envelope.attack = sliderA.getValue();
        repaint();
        DBG(sliderA.getValue());
        DBG("Envelope.attack: " << envelope.attack);
    }
    else if(slider == &sliderD)
    {
        decayPos = sliderD.getValue();
        envelope.decay = sliderD.getValue();
        repaint();
    }
    else if(slider == &sliderS)
    {
        sustainPos = sliderS.getValue();
        envelope.sustain = sliderS.getValue();
        repaint();
    }
    else if(slider == &sliderR)
    {
        releasePos = sliderR.getValue();
        envelope.release = sliderR.getValue();
        repaint();
    }
    
}

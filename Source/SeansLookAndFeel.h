/*
  ==============================================================================

    ArtiLookAndFeel.h
    Created: 5 March 2021 6:19:30pm
    Author:  Sean Maloney

  ==============================================================================
*/
#include <JuceHeader.h>
#pragma once
class SeansLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SeansLookAndFeel() {};
    ~SeansLookAndFeel() {};
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height,
                          float sliderPos, float startAngle,
                          float endAngle, juce::Slider &s) override;
    
    juce::Slider::SliderLayout getSliderLayout (juce::Slider& slider) override;
    
    void drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
        float sliderPos, float minSliderPos, float maxSliderPos,
                                    const juce::Slider::SliderStyle style, juce::Slider& slider) override;
    
    void drawLabel (juce::Graphics& g, juce::Label& label) override;
    
    void drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown) override;
    
    
    //juce::Typeface::Ptr getTypefaceForFont(const juce::Font& f) override;
    //juce::TextButton::buttonColourId override;
private:
    juce::Colour artiDefaultColor = juce::Colours::slategrey;
    //juce::Typeface::Ptr artiFont;
    //juce::DropShadow dropShadow;
    
};

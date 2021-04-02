#include "EnvComponent.h"
#include "SliderComp.h"

//==============================================================================
EnvComponent::EnvComponent()
{

    
}

EnvComponent::~EnvComponent()
{
}

//==============================================================================
void EnvComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::transparentBlack);
    
    
    //points
    auto height = getHeight() - 8.0f;
    auto width = getWidth() - 8.0f;
    auto pointA = juce::Point<float>(4.0f, height + 4.0f);
    auto pointBmax = juce::Point<float>((width * 0.3f * attack), 4.0f);
    auto pointCmax = juce::Point<float>((width * 0.3f * (attack + 0.1f + 0.9f * (decay))), height * (1.0f - sustain) + 4.0f);
    auto pointDmax = juce::Point<float>(width * 0.7f, height * (1.0f - sustain) + 4.0f);
    
    auto pointF = juce::Point<float>(width * (0.73f + 0.27f * release) + 4.0f, height + 4.0f);
    

    //===================================================================
    //quadratic envelope with max velocity
    juce::Path quadMaxEnvelope;
            quadMaxEnvelope.startNewSubPath (pointA);
            quadMaxEnvelope.lineTo (pointBmax);
            quadMaxEnvelope.lineTo(pointCmax);
            quadMaxEnvelope.lineTo(pointDmax);
            quadMaxEnvelope.lineTo(pointF);
            g.setGradientFill(juce::ColourGradient(juce::Colour (0xff008891), 0, 0, juce::Colour (0xffffffff), getWidth(), getHeight(), false));
            g.strokePath (quadMaxEnvelope, juce::PathStrokeType (5.0f, juce::PathStrokeType::JointStyle::curved, juce::PathStrokeType::EndCapStyle::rounded));
}

void EnvComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}



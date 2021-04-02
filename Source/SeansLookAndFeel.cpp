/*
  ==============================================================================

    ArtiLookAndFeel.cpp
    Created: 5 March 2021 6:19:30pm
    Author:  Sean Maloney

  ==============================================================================
*/

#include "SeansLookAndFeel.h"


void SeansLookAndFeel::drawRotarySlider(juce::Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &slider)
{
    auto radius = (float) juce::jmin (width / 2, height / 2);
            //auto centreX = (float) x + (float) width  * 0.5f;
            //auto centreY = (float) y + (float) height * 0.5f;
    auto centreX = (float) x + (float) slider.getWidth()  * 0.5f;
    auto centreY = (float) y + (float) slider.getHeight() * 0.5f;
            auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
            auto midPointAngle = (rotaryStartAngle + rotaryEndAngle) / 2;
            auto lineW = juce::jmin (18.0f, radius * 0.4f);
            auto arcRadius = radius - lineW * 0.5f;
            auto arcRadiusLarger = arcRadius * 1.2;
    
    juce::Path backgroundArc;
    backgroundArc.addCentredArc (centreX, centreY, arcRadius, arcRadius, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
    g.setGradientFill(juce::ColourGradient(juce::Colour (0xff008891), 0, 0, juce::Colour (0xffffffff), width, height, false));
    g.strokePath (backgroundArc, juce::PathStrokeType (lineW, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    
//    juce::Path skinnyArc;
//    skinnyArc.addCentredArc (centreX, centreY, arcRadiusLarger, arcRadiusLarger, 0.0f, rotaryStartAngle, rotaryEndAngle, true);
//    g.setGradientFill(juce::ColourGradient(juce::Colour (0xffffffff), 0, 0, juce::Colour (0xffffffff), width, height, false));
//    g.strokePath (skinnyArc, juce::PathStrokeType (2.0f, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
//
    //circle rotary slider
    if (slider.isEnabled()) {
        //outer ring arc
        juce::Path filledArc;
        filledArc.addCentredArc (centreX,centreY, arcRadius, arcRadius, 0.0f, midPointAngle, toAngle, true);
    }
    
    
    //Drop shadow for pointer
    juce::Path p;
    auto pointerLength = radius;
    auto pointerThickness = 5.0f;
    p.addRoundedRectangle(-pointerThickness * 0.5f, -radius - 3, pointerThickness, pointerLength, 2.5f, 2.5f);
    p.applyTransform(juce::AffineTransform::rotation (toAngle).translated (centreX, centreY));
    g.setColour(juce::Colours::white);
    juce::DropShadow dropShadow;
    dropShadow.colour = (juce::Colours::white);
    dropShadow.radius = 20;
    dropShadow.drawForPath(g, p);
    g.fillPath(p);

    
    
}

juce::Slider::SliderLayout SeansLookAndFeel::getSliderLayout (juce::Slider& slider)
{
    // 1. compute the actually visible textBox size from the slider textBox size and some additional constraints
    
    int minXSpace = 0;
    int minYSpace = 0;
    
    auto textBoxPos = slider.getTextBoxPosition();
    
    if (textBoxPos == juce::Slider::TextBoxLeft || textBoxPos == juce::Slider::TextBoxRight)
        minXSpace = 30;
    else
        minYSpace = 15;
    
    auto localBounds = slider.getLocalBounds();
    
    auto textBoxWidth  = juce::jmax (0, juce::jmin (slider.getTextBoxWidth(),  localBounds.getWidth() - minXSpace));
    auto textBoxHeight = juce::jmax (0, juce::jmin (slider.getTextBoxHeight(), localBounds.getHeight() - minYSpace));
    
    juce::Slider::SliderLayout layout;
    
    // 2. set the textBox bounds
    
    if (textBoxPos != juce::Slider::NoTextBox)
    {
        if (slider.isBar())
        {
            layout.textBoxBounds = localBounds;
        }
        else
        {
            layout.textBoxBounds.setWidth (textBoxWidth);
            layout.textBoxBounds.setHeight (textBoxHeight);
            
            if (textBoxPos == juce::Slider::TextBoxLeft)           layout.textBoxBounds.setX (0);
            else if (textBoxPos == juce::Slider::TextBoxRight)     layout.textBoxBounds.setX (localBounds.getWidth() - textBoxWidth);
            else /* above or below -> centre horizontally */ layout.textBoxBounds.setX ((localBounds.getWidth() - textBoxWidth) / 2);
            
            if (textBoxPos == juce::Slider::TextBoxAbove)          layout.textBoxBounds.setY (0);
            //Move the slider value text box here
            else if (textBoxPos == juce::Slider::TextBoxBelow)     layout.textBoxBounds.setY
                (localBounds.getHeight() - textBoxHeight + 10);
            else /* left or right -> centre vertically */    layout.textBoxBounds.setY ((localBounds.getHeight() - textBoxHeight) / 2);
        }
    }
    
    // 3. set the slider bounds
    
    layout.sliderBounds = localBounds;
    
    if (slider.isBar())
    {
        layout.sliderBounds.reduce (1, 1);   // bar border
    }
    else
    {
        if (textBoxPos == juce::Slider::TextBoxLeft)       layout.sliderBounds.removeFromLeft (textBoxWidth);
        else if (textBoxPos == juce::Slider::TextBoxRight) layout.sliderBounds.removeFromRight (textBoxWidth);
        else if (textBoxPos == juce::Slider::TextBoxAbove) layout.sliderBounds.removeFromTop (textBoxHeight);
        else if (textBoxPos == juce::Slider::TextBoxBelow) layout.sliderBounds.removeFromBottom (textBoxHeight);
        
        if (slider.isHorizontal())    layout.sliderBounds.reduce (3, 0);
        else if (slider.isVertical()) layout.sliderBounds.reduce (0, 3);
    }
    
    return layout;
}

void SeansLookAndFeel::drawLinearSliderBackground(juce::Graphics& g, int x, int y, int width, int height,
    float sliderPos, float /* minSliderPos */, float /* maxSliderPos */,
    const juce::Slider::SliderStyle /* style */, juce::Slider& slider)
{
    const float sliderRadius = (float)(getSliderThumbRadius(slider) - 2);
    const bool isMouseOver = slider.isMouseOverOrDragging() && slider.isEnabled();
    const bool bidirectional = (slider.getMinimum() < 0.0f) && (slider.getMaximum() > 0.0f);

    const juce::Colour trackColour(slider.findColour(juce::Slider::trackColourId));
    juce::Path indent;
    juce::Path bar;
    
    if (slider.isHorizontal())
    {
        auto iy = y + height * 0.5f - sliderRadius * 0.5f;

        indent.addRoundedRectangle(x - 3.0f, (float)iy, width + 6.0f, sliderRadius, 5.0f);
        if (bidirectional)
        {
            float zeroPoint = (float)(width * -slider.getRange().getStart() /
                (slider.getRange().getEnd() - slider.getRange().getStart()));
            if (zeroPoint > sliderPos)
            {
                bar.addRectangle(x + sliderPos, iy, zeroPoint - sliderPos, sliderRadius);
            }
            else
            {
                bar.addRectangle(x + zeroPoint, iy, sliderPos - zeroPoint, sliderRadius);
            }
        }
        else
        {
            bar.addRoundedRectangle(x - 2.0f, (float)iy, sliderPos + 3.0f, sliderRadius, 5.0f);
        }
    }
    else
    {
        auto ix = x + width * 0.5f - sliderRadius * 0.5f;

        indent.addRoundedRectangle((float)ix, y - 3.0f, sliderRadius, height + 6.0f, 5.0f);
        if (bidirectional)
        {
            float zeroPoint = (float)(height * -slider.getRange().getStart() /
                (slider.getRange().getEnd() - slider.getRange().getStart()));
            if (zeroPoint > sliderPos)
            {
                bar.addRectangle(ix, y + sliderPos, sliderRadius, zeroPoint - sliderPos);
            }
            else
            {
                bar.addRectangle(ix, y + zeroPoint, sliderRadius, sliderPos - zeroPoint);
            }
        }
        else
        {
            bar.addRoundedRectangle((float)ix, y + sliderPos - 2.0f, sliderRadius, height + 3.0f - sliderPos, 5.0f);
        }
    }

    if (slider.isEnabled())
        g.setColour (slider.findColour (juce::Slider::rotarySliderFillColourId).withAlpha (isMouseOver ? 1.0f : 0.7f));
    else
        g.setColour (juce::Colour (0xc0808080));
    g.fillPath(bar);

    g.setColour(trackColour);
    g.strokePath(indent, juce::PathStrokeType(slider.isEnabled() ? (isMouseOver ? 2.0f : 1.5f) : 0.3f));
}



void SeansLookAndFeel::drawLabel (juce::Graphics& g, juce::Label& label)
{
    g.fillAll (label.findColour (juce::Label::backgroundColourId));

    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const juce::Font font (getLabelFont (label));

        g.setColour (juce::Colours::white);
        g.setFont (font);

        auto textArea = getLabelBorderSize(label).subtractedFrom (label.getLocalBounds());
        g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                          juce::jmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                          label.getMinimumHorizontalScale());
        g.setColour (juce::Colours::transparentWhite);
    }
    else if (label.isEnabled())
    {
        g.setColour (juce::Colours::transparentWhite);
    }

    g.drawRect (label.getLocalBounds());
}
//juce::Typeface::Ptr ArtiLookAndFeel::getTypefaceForFont(const juce::Font& f) {
//    artiFont = juce::Typeface::createSystemTypefaceFor(BinaryData::JosefinSansVariableFont_wght_ttf, BinaryData::JosefinSansVariableFont_wght_ttfSize);
//    return artiFont;
//}


void SeansLookAndFeel::drawButtonBackground (juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
                               bool isMouseOverButton, bool isButtonDown)
    {
        auto baseColour = juce::Colours::transparentWhite;

        auto flatOnLeft   = button.isConnectedOnLeft();
        auto flatOnRight  = button.isConnectedOnRight();
        auto flatOnTop    = button.isConnectedOnTop();
        auto flatOnBottom = button.isConnectedOnBottom();

        auto width  = (float) button.getWidth()  - 1.0f;
        auto height = (float) button.getHeight() - 1.0f;

        if (width > 0 && height > 0)
        {
            auto cornerSize = juce::jmin (15.0f, juce::jmin (width, height) * 0.45f);
            auto lineThickness = cornerSize    * 0.1f;
            auto halfThickness = lineThickness * 0.5f;

            juce::Path outline;
            outline.addRoundedRectangle (0.5f + halfThickness, 0.5f + halfThickness, width - lineThickness, height - lineThickness,
                                         cornerSize, cornerSize,
                                         ! (flatOnLeft  || flatOnTop),
                                         ! (flatOnRight || flatOnTop),
                                         ! (flatOnLeft  || flatOnBottom),
                                         ! (flatOnRight || flatOnBottom));

            auto outlineColour = juce::Colours::transparentWhite;

            g.setColour (baseColour);
            g.fillPath (outline);
        }
    }



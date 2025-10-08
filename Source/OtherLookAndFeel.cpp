/* Class fully created by student to deal with slider designs, called within DeckGUI and Turntable classes, using the look and feel tutorial from juce as reference only:https://docs.juce.com/master/tutorial_look_and_feel_customisation.html*/

#include <JuceHeader.h>
#include "OtherLookAndFeel.h"

//==============================================================================
OtherLookAndFeel::OtherLookAndFeel()
{

}

OtherLookAndFeel::~OtherLookAndFeel()
{

}

void OtherLookAndFeel::paint (juce::Graphics& g)
{

}

void OtherLookAndFeel::resized()
{

}

/* student's Work, creating graphics for rotary slider */
void OtherLookAndFeel::drawRotarySlider(Graphics& g,
                                        int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPos,
                                        float rotaryStartAngle,
                                        float rotaryEndAngle,
                                        Slider& slider)
{
    //local variables
    float diameter = jmin(width, height);
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float smallIncr = diameter / 20;
    float largeIncr = diameter / 5;
    float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

    //calling function within class to draw dial
    OtherLookAndFeel::innerDial(g, rx,
                                ry,
                                diameter,
                                centreX,
                                centreY,
                                radius,
                                largeIncr,
                                angle,
                                smallIncr);
}

/* student's Work, creating graphics for linear slider */
void OtherLookAndFeel::drawLinearSlider(Graphics& g, int x,
                                        int y,
                                        int width,
                                        int height,
                                        float sliderPos,
                                        float minSliderPos,
                                        float maxSliderPos,
                                        const Slider::SliderStyle style,
                                        Slider& slider)
{
    //colours required
    juce::Array<juce::Colour> custLinSliderColours{juce::Colour(153, 204, 204), //0 light turquoise
                                                   juce::Colour(181, 250, 255), //1 light blue
                                                   juce::Colour(102, 153, 153) //2 light grey turquoise
                                                   };
    
    //code for creating thumb track
    auto thumbTrackWidth = 4.0f;
    auto thumbTrack = Rectangle<float>((width / 2) - thumbTrackWidth / 2,
                                        y,
                                        thumbTrackWidth,
                                        height);
    g.setColour(custLinSliderColours[0]);
    g.fillRect(thumbTrack.toFloat());

    //code for creating thumb
    auto thumbWidth = 10.0 * 2;
    auto thumbHeight = 5.0f;
    auto thumbX = x + (width - thumbWidth) * 0.5f;
    auto thumbY = sliderPos;

    auto thumb = Rectangle<float>(thumbX,
                                  thumbY - 10,
                                  thumbWidth,
                                  thumbHeight * 2);
    g.setColour(custLinSliderColours[2]);
    g.fillRect(thumb.toFloat());
    auto thumb1 = Rectangle<float>(thumbX,
                                   thumbY - 10,
                                   thumbWidth,
                                   thumbHeight);
    g.setColour(custLinSliderColours[1]);
    g.fillRect(thumb1.toFloat());

}
/* student's work, creating inner dial, called in Turntable class and OtherLookAndFeel::rotary slider */
void OtherLookAndFeel::innerDial(Graphics& g, 
                                 float rx,
                                 float ry,
                                 float diameter,
                                 float centreX,
                                 float centreY,
                                 float radius,
                                 float largeIncr,
                                 float angle,
                                 float smallIncr)
{
    //creating paths for arcs
    Path custDial;
    Path cust2Dial;
    Path cust3Dial;
    Path cust4Dial;
    //creating rectangle class for ellipse data
    Rectangle<float> dialArea(centreX - (5 * radius / 14),
                               centreY - (5 * radius / 14),
                               5 * radius / 7,
                               5 * radius / 7);
    //shapes
    g.setColour(custColours[0]);
    g.fillEllipse(dialArea);

    g.setColour(custColours[8]);

    //creating arcs and rotating them with 'angle' using the current data from sliders
    g.setColour(custColours[5]);
    custDial.addCentredArc(0,
                           0,
                           largeIncr * 11 / 6,
                           largeIncr * 11 / 6,
                           (5 * 3.14) / 6,
                           0,
                           (7 * 3.14) / 8,
                           true);
    g.strokePath(custDial,
                 PathStrokeType(5.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(custColours[2]);
    cust2Dial.addCentredArc(0,
                            0,
                            largeIncr * 4 / 3,
                            largeIncr * 4 / 3,
                            (5 * 3.14) / 6,
                            0,
                            2 * 3.14,
                            true);
    g.strokePath(cust2Dial,
                 PathStrokeType(6.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));


    g.setColour(custColours[3]);
    cust3Dial.addCentredArc(0,
                            0,
                            largeIncr * 4 / 3,
                            largeIncr * 4 / 3,
                            (5 * 3.14) / 6,
                            0,
                            0.5,
                            true);
    g.strokePath(cust3Dial,
                 PathStrokeType(6.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(custColours[9]);
    cust4Dial.addCentredArc(0,
                            0,
                            largeIncr * 2,
                            largeIncr * 2,
                            (5 * 3.14) / 6,
                            0,
                            3 * 3.14f / 2,
                            true);
    g.strokePath(cust4Dial,
                 PathStrokeType(3.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

}
/* student's work, creating outer dial, called in Turntable class */
void OtherLookAndFeel::outerDial(Graphics& g, 
                                 float rx,
                                 float ry,
                                 float diameter,
                                 float centreX,
                                 float centreY,
                                 float radius,
                                 float largeIncr,
                                 float angle,
                                 float smallIncr)
{
    //creating paths for arcs and ticks
    Path dialTick;
    Path cust5Dial;
    Path cust6Dial;
    Path cust7Dial;
    Path cust8Dial;
    //creating arcs and rotating them with 'angle' using the current data from sliders
    g.setColour(custColours[8]);
    cust5Dial.addCentredArc(0,
                            0,
                            radius - 5.0f,
                            radius - 5.0f,
                            (5 * 3.14) / 6,
                            0,
                            (3 * 3.14) / 8,
                            true);
    g.strokePath(cust5Dial,
                 PathStrokeType(8.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(custColours[5]);
    cust6Dial.addCentredArc(0,
                            0, 
                            radius - 5.0f,
                            radius - 5.0f,
                            (5 * 3.14) / 6,
                            (3 * 3.14) / 8,
                            (15 * 3.14) / 16,
                            true);
    g.strokePath(cust6Dial,
                 PathStrokeType(8.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(custColours[4]);
    cust7Dial.addCentredArc(0,
                            0,
                            radius - 5.0f,
                            radius - 5.0f,
                            (5 * 3.14) / 6,
                            (15 * 3.14) / 16,
                            (5 * 3.14) / 3,
                            true);
    g.strokePath(cust7Dial,
                 PathStrokeType(8.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));

    g.setColour(custColours[2]);
    cust8Dial.addCentredArc(0,
                            0,
                            radius - 5.0f,
                            radius - 5.0f,
                            (5 * 3.14) / 6,
                            (5 * 3.14) / 3,
                            2 * 3.14,
                            true);
    g.strokePath(cust8Dial,
                 PathStrokeType(8.0f),
                 AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(custColours[10]);

    //creating rectangle class to use for the dial ticks, and using fill path to draw them. 'angle' used to rotate them by the current slider values
    dialTick.addRectangle(0 - (smallIncr / 8),
                          -radius + smallIncr,
                          smallIncr / 4,
                          radius - smallIncr);

    g.fillPath(dialTick,
               AffineTransform::rotation(angle).translated(centreX, centreY));
    g.fillPath(dialTick,
               AffineTransform::rotation(angle + 2.0944).translated(centreX, centreY));
    g.fillPath(dialTick,
               AffineTransform::rotation(angle + 4.18879).translated(centreX, centreY));
}
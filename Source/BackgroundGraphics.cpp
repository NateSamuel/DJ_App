
#include <JuceHeader.h>
#include "BackgroundGraphics.h"

/* Student's own class which deals with background gradient effects for the area above the playlist, and other miscellaneous items*/

BackgroundGraphics::BackgroundGraphics()
{

}

BackgroundGraphics::~BackgroundGraphics()
{

}

void BackgroundGraphics::paint (juce::Graphics& g)
{
    //local incremental variables
    double incr = getWidth() / 24;
    
    //creating background dark blue to mid blue gradient

    juce::Image darkGradientImage(juce::Image::ARGB,
        getWidth(),
        getHeight(),
        true);
    juce::Graphics darkGradientG(darkGradientImage);

    juce::Colour custDarkBlue(80,
        200,
        235);
    juce::ColourGradient darkBlueCG = juce::ColourGradient::horizontal(custDarkBlue.darker(1.0),
        0.0,
        custDarkBlue.darker(10.0),
        getWidth());
    darkGradientG.setGradientFill(darkBlueCG);
    darkGradientG.fillAll();

    g.drawImage(darkGradientImage, getLocalBounds().toFloat());

    //creating path line for futuristic aesthetic

    g.setColour(juce::Colours::lightcyan);

    Path myPath;

    myPath.startNewSubPath(0,
                           getHeight() * 4 / 7);
    myPath.lineTo(getWidth() / 2 - (2 * incr),
                  getHeight() * 4 / 7);
    myPath.lineTo(getWidth() / 2 - (incr / 2),
                  getHeight() * 5/8);
    myPath.lineTo(getWidth() / 2 - (incr/2),
                  getHeight());
    myPath.lineTo(getWidth() / 2 + (incr / 2),
                  getHeight());
    myPath.lineTo(getWidth() / 2 + (incr / 2),
                  getHeight() * 5/8);
    myPath.lineTo(getWidth() / 2 + (2 * incr),
                  getHeight() * 4 / 7);
    myPath.lineTo(getWidth(),
                  getHeight() * 4 / 7);

    g.strokePath(myPath,
        PathStrokeType(5.0f));

    //creating light blue to white gradient for frequency visualiser and bass/treble sliders area

    juce::Image lightGradientImage(juce::Image::ARGB,
                                  getWidth(),
                                  getHeight(),
                                  true);
    juce::Graphics lightGradientG(lightGradientImage);
    juce::Colour custLightBlue(181,
                               250,
                               255);
    juce::Colour white(255,
                       255,
                       255);
    juce::ColourGradient lightBlueCG = juce::ColourGradient::horizontal(custLightBlue,
                                                               0.0,
                                                               white,
                                                               getWidth());
    lightGradientG.setGradientFill(lightBlueCG);
    lightGradientG.fillAll();
    Rectangle<float> gradRectArea(0,
                              getHeight() * 2 / 7,
                              getWidth(),
                              getHeight() * 4 / 18);

    g.drawImage(lightGradientImage, gradRectArea);

}

void BackgroundGraphics::resized()
{


}

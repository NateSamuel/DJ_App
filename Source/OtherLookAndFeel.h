/* Class fully created by student to deal with slider designs, called within DeckGUI and Turntable classes, using the look and feel tutorial from juce as reference only:https://docs.juce.com/master/tutorial_look_and_feel_customisation.html*/
#pragma once

#include <JuceHeader.h>

class OtherLookAndFeel  : public Component,
                          public LookAndFeel_V4
{
public:
    OtherLookAndFeel();
    ~OtherLookAndFeel() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    //change look and feel of rotary slider
    void drawRotarySlider(Graphics& g,
        int x,
        int y,
        int width,
        int height,
        float sliderPos,
        float rotaryStartAngle,
        float rotaryEndAngle,
        Slider& slider);
    //change look and feel of linear slider
    void drawLinearSlider(Graphics&, int x,
                        int y,
                        int width,
                        int height,
                        float sliderPos,
                        float minSliderPos,
                        float maxSliderPos,
                        const Slider::SliderStyle style,
                        Slider& slider);
    //function to draw inner dial design, used in rotary slider and turntable class
    void innerDial(Graphics& ,
                    float rx,
                    float ry,
                    float diameter,
                    float centreX,
                    float centreY,
                    float radius,
                    float largeIncr,
                    float angle,
                    float smallIncr);
    //function to draw inner dial design, used in turntable class
    void outerDial(Graphics& ,
                    float rx,
                    float ry,
                    float diameter,
                    float centreX,
                    float centreY,
                    float radius,
                    float largeIncr,
                    float angle,
                    float smallIncr);


private:
    //colours used in inner and outer dial functions
    juce::Array<juce::Colour> custColours{ juce::Colour(7, 18, 22),     //0 Almost black
                                       juce::Colour(0, 51, 51),     //1 Dark dark turquoise
                                       juce::Colour(51, 102, 102),  //2 Grey turquoise
                                       juce::Colour(0, 153, 153),   //3 mid turquoise
                                       juce::Colour(102, 153, 153), //4 light grey turquoise
                                       juce::Colour(153, 204, 204), //5 light turquoise
                                       juce::Colour(80, 200, 235),  //6 sky blue
                                       juce::Colour(181, 250, 255), //7 light blue
                                       juce::Colour(204, 255, 255), //8 white blue
                                       juce::Colour(102, 255, 255), //9 bold turquoise
                                       juce::Colour(255, 255, 255)  //10 white
    };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OtherLookAndFeel)
};


/*Full class is student's work, creating a turntable component that is able to scratch the record forwards and backwards*/

#include <JuceHeader.h>
#include "Turntable.h"

Turntable::Turntable()
    
{
    //makes visible the turntables using &turnTableLAF as a parameter
    addAndMakeVisible(&turntableLAF);
    //starts the timer used in timerCallback
    startTimer(50);
}

Turntable::~Turntable()
{
    stopTimer();
}

void Turntable::paint(Graphics& g)
{
    //initialising local variables
    int x = 0;
    int y = 0;
    int width = getWidth();
    int height = getHeight();
    float diameter = jmin(width, height);
    float radius = diameter / 2;
    float centreX = x + width / 2;
    float centreY = y + height / 2;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float smallIncr = diameter / 40;
    float largeIncr = diameter / 10;

    //calls the innerDial and outerDial function in OtherLookAndFeel class in order to draw the turntables
    turntableLAF.innerDial(g,
                           rx,
                           ry,
                           diameter,
                           centreX,
                           centreY,
                           radius,
                           largeIncr,
                           angle,
                           smallIncr);
    turntableLAF.outerDial(g,
                           rx,
                           ry,
                           diameter,
                           centreX,
                           centreY,
                           radius,
                           largeIncr,
                           angle,
                           smallIncr);
}

void Turntable::resized()
{
    //initialising local variables
    double dialMirror = 0;
    double rowH = getHeight() / 14;
    double marginW = getWidth() / 24;
    double centreW = getWidth() / 2;
    //makes the turntable be in the correct position from the centre point depending on which turntable it is.
    if (Turntable::isMirrored == 1)
    {
        dialMirror = centreW - (4 * marginW);

    }
    else if (Turntable::isMirrored == -1) {
        dialMirror = 4 * marginW;

    }
    //sets the bounds of the turntable
    turntableLAF.setBounds(dialMirror,
                           rowH * 8,
                           getWidth() / 2,
                           rowH * 6);

}


void Turntable::timerCallback()
{

    //a set of if statements that use boolean operators that have been called from the DeckGUI to alter the angle of the record within a set period of time

    //if the player is playing, then this starts to spin the record. If not then it stays in the same position.
    if (refreshGraphics == true)
    {
        timeframe += 0.1;

        angle = timeframe;

        repaint();
    }
    //if the invisible slider that is in DeckGUI has been pushed backwards, pushRecordBackward is made true. 
    //Whilst this is true, the angle number is being reduced, rotating the record backwards.
    if (pushRecordBackward == true)
    {
        timeframe -= 0.4;

        angle = timeframe;
        pushRecordBackward = false;
        repaint();
    }
    //if the invisible slider that is in DeckGUI has been pushed forwards, pushRecordForward is made true. 
    //Whilst this is true, the angle number is being increased, rotating the record forwards.
    if (pushRecordForward == true)
    {
        timeframe += 0.4;

        angle = timeframe;
        repaint();
        pushRecordForward = false;
    }
}



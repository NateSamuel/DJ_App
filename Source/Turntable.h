
/*Full class is student's work, creating a turntable component that is able to scratch the record forwards and backwards*/

#pragma once

#include <JuceHeader.h>
#include "OtherLookAndFeel.h"


class Turntable  : public Timer,
                   public Component
{
public:
    Turntable();
    ~Turntable() override;
    void paint (juce::Graphics&) override;

    //required integers, floats and booleans in order to start, stop, rotate, position the function correctly
    int isMirrored = 0;
    bool refreshGraphics = false;
    bool pushRecordForward = false;
    bool pushRecordBackward = false;
    float angle = 0;
    float frameToAngle = 0;
    float timeframe = 0;

    void resized() override;
    /** implement timer callback */
    void timerCallback() override;

private:
    //OtherLookAndFeel used to create record design
    OtherLookAndFeel turntableLAF;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Turntable)
};

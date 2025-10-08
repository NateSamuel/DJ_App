
#pragma once
#include <JuceHeader.h>

/* Student's own class which deals with background gradient effects for the area above the playlist, and other miscellaneous items*/

class BackgroundGraphics  : public juce::Component
{
public:
    BackgroundGraphics();
    ~BackgroundGraphics() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackgroundGraphics)
};

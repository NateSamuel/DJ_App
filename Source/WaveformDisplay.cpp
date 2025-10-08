/* Teachers work, student has only changed the sizes and colours of the design. Creates waveform display when track is loaded into DeckGUI player*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

/*Teacher's work*/
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
                                AudioThumbnailCache& cacheToUse) :
                                audioThumb(1000, formatManagerToUse, cacheToUse),
                                fileLoaded(false),
                                position(0)

{

    audioThumb.addChangeListener(this);
}
/*Teacher's work*/
WaveformDisplay::~WaveformDisplay()
{
}
/*Teacher's work*/
void WaveformDisplay::paint(Graphics& g)
{
    /*Student's work*/
    g.fillAll(Colours::lightcyan);   // the background colour

    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component
    /*Teacher's work*/
    // draws the wave file to the audioThumb
    if (fileLoaded)
    {
        //draws waveform
        audioThumb.drawChannel(g,
                               getLocalBounds(),
                               0,
                               audioThumb.getTotalLength(),
                               0,
                               1.0f);
        /*Student's work*/
        g.setColour(Colours::red);

        //draws line based on 'position' of playhead
        g.drawLine(position * getWidth(),
                   0,
                   position * getWidth(),
                   getHeight(),
                   2.0f);
    }
    /*Teacher's work*/
    else
    {
        g.setColour(Colours::black);
        g.setFont(40.0f);
        g.drawText("...",
                   getLocalBounds(),
                   Justification::centred,
                   true);   // draw some placeholder text

    }
}
/*Teacher's work*/
void WaveformDisplay::resized()
{

}
/*Teacher's work*/
void WaveformDisplay::loadURL(URL audioURL)
{
    //clears the audioThumb to be repainted
    audioThumb.clear();
    //adds new source to audioThumb when loadURl is called
    fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
    if (fileLoaded)
    {
        std::cout << "wfd: loaded! " << std::endl;
        repaint();
    }
    else {
        std::cout << "wfd: not loaded! " << std::endl;
    }

}
/*Teacher's work*/
void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
    std::cout << "wfd: change received! " << std::endl;

    repaint();

}
/*Teacher's work*/
void WaveformDisplay::setPositionRelative(double pos)
{
    //sets position to the playheads current pos and repaints it
    if (pos != position && !isnan(pos))
    {
        position = pos;
        repaint();
    }

}



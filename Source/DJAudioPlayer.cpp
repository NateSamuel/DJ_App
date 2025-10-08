/* Teacher's and Student's work, used to create filters like bass and treble and alter the track's positon or speed or volume */

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
    : formatManager(_formatManager)
{

}
DJAudioPlayer::~DJAudioPlayer()
{

}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

    /*Teacher's work*/
    getSampleRate = sampleRate;
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    /*student's work, setting initial bass and treble filters*/
    float setBass = 1.f;
    float setTreble = 1.f;
    filterSource.setCoefficients(IIRCoefficients::makeLowShelf(sampleRate,
                                                               300.f,
                                                               1.5f,
                                                               setBass));
    filterSource.setCoefficients(IIRCoefficients::makeHighShelf(sampleRate,
                                                                10000.f,
                                                                1.5f,
                                                                setTreble));

    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    /*student's work, adding filter to mixerSource*/
    mixerSource.addInputSource(&filterSource, false);

    /*Teacher's work*/
    resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

/*Teacher's work, gets the next audio block*/
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    resampleSource.getNextAudioBlock(bufferToFill);

}

/*Teacher's work, sets the resample source to releaseResources*/
void DJAudioPlayer::releaseResources()
{
    resampleSource.releaseResources();
}

/*Teacher's work, load's the URL send from the DeckGUI into the transportSource and resets the reader source*/
void DJAudioPlayer::loadURL(URL audioURL)
{
    auto* reader = formatManager.createReaderFor(audioURL.createInputStream(false));
    if (reader != nullptr) // good file!
    {
        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
                                                                                       true));
        transportSource.setSource(newSource.get(),
                                  0,
                                  nullptr,
                                  reader->sampleRate);
        readerSource.reset(newSource.release());
    }
}

/*Teacher's work, sets the volume*/
void DJAudioPlayer::setGain(double gain)
{
    if (gain < 0 || gain > 1.0)
    {
        std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
    }
    else {
        transportSource.setGain(gain);
    }

}

/*Teacher's work, sets the speed*/
void DJAudioPlayer::setSpeed(double ratio)
{
    if (ratio < 0 || ratio > 3.0)
    {
        std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 3" << std::endl;
    }
    else {
        resampleSource.setResamplingRatio(ratio);
    }
}

/*Teacher's work, sets the position of the track*/
void DJAudioPlayer::setPosition(double posInSecs)
{
    transportSource.setPosition(posInSecs);
}

/*Student's work, altering bass value of track, using the bass slider value*/
void DJAudioPlayer::setBass(double bassSliderVal,double samplesget)
{
    filterSource.setCoefficients(IIRCoefficients::makeLowShelf(samplesget,
                                                                   500.f,
                                                                   1.5f,
                                                                   bassSliderVal));

}

/*Student's work, altering treble value of track, using the treble slider value*/
void DJAudioPlayer::setTreble(double trebleSliderVal, double samplesget)
{
    filterSource.setCoefficients(IIRCoefficients::makeHighShelf(samplesget,
                                                                    3000.f,
                                                                    1.5f,
                                                                    trebleSliderVal));
    
}

/*Teacher's work, sets the position relative to the length of the track*/
void DJAudioPlayer::setPositionRelative(double pos)
{
    if (pos < 0 || pos > 1.0)
    {
        std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
    }

    else {
        double posInSecs = transportSource.getLengthInSeconds() * pos;
        setPosition(posInSecs);
    }
}

/*Teacher's work, starts the track*/
void DJAudioPlayer::start()
{
    transportSource.start();
}

/*Teacher's work, stops the track*/
void DJAudioPlayer::stop()
{
    transportSource.stop();
}

/*Teacher's work, gets the position relative to the length of the track*/
double DJAudioPlayer::getPositionRelative()
{
    return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

/*Teacher's work, gets the length of the track in seconds*/
double DJAudioPlayer::getLengthInSeconds()
{
    return transportSource.getLengthInSeconds();
}
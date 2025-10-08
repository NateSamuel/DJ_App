# DJ_App
This DJ app was created with C++ and JUCE to create mixes with multiple tracks.

Report
R1 –
Please see an overview of the basic functionalities of the project that are satisfied in R1:
R1A – In order to be able to load the audio files in the audio players, there are three classes we have made
specifically. MainComponent, DJAudioPlayer, and DeckGUI. The DeckGUI class called in MainComponent has
two separate instances, the left and right players. Each player, player1 and player2 can load tracks by using the
LoadURL function that is enacted when the button::listener for the load button is clicked. When the user
chooses the file, the URL is sent to the loadURL function in the DJAudioPlayer class, which creates an input
stream of information that is given to the transportSource. There is also the ‘isInterestedInFileDrag’ and
‘filesDropped’ functions in DeckGUI, that deal with if the file wants to be dragged and then the URL is loaded
into the player.
R1B – To play two tracks at the same time, the play button on each player is pressed, which is picked up by the
button::listeners in DeckGUIs and the start() function is called from DeckGUIs into the DJAudioPlayers. This calls
start() on the transportSources and then filters can be added to it before being sent back to the
mainComponent that mixes it together with the other track that is in the separate player. This is thed
mixerSource that is the title of the juce MixerAudioSource class.
R1C – The way the two players tracks can be mixed on a basic level is by using the volSlider. When the thumb
on the volSlider is moved, the slider::listener is called in DeckGUI, which notifies the sliderValueChanged
function. This calls the ‘DJAudioPlayer::setGain’ function with the value on the slider being put in as the
parameter. This enacts setGain on the transportSource, altering it by the value which reduces or adds to the
volume.
R1D – The way the two players tracks can be altered is by using the position and speed sliders. These work in a
similar way to R1C but for the position slider it enacts setPosition on the transport source and for the speed
slider it enacts setResamplingRatio on the resampleSource.
Extra: We also began to create a playlistComponent by using the tableListBox class to input columns and rows,
using the getNumRows, the paintRowBackground and the paintCell functions. We began to implement a load
button for each row by using a refreshComponentForCell, but this was not progressed any further than
implementing the button design itself. For part of R3 I have developed this further.
We implemented a waveformDisplay as well, which was called upon loading up a URL into a player. The data,
called in DeckGUI loadURL is given to the AudioThumbnail class, titled audioThumb which splits the data of the
track up into scaled down waveforms, that can be painted with ‘drawChannel’ in the paint component
function.
R2-
The aim of the graphic design of the project is
to make it a futuristic ‘Tron’ inspired UI. There
is a scene in ‘Tron Legacy’ where Daft Punk
play as DJs, and so I wanted to create a DJ
deck that would suit the feeling of this
moment in the movie. I used similar colouring
of the city and futuristically styled dials to do
this.
Reference from Tron
legacy.
R2A
To change the main graphics of the application I
have created two new classes, the
BackgroundGraphics Class, and the
OtherLookAndFeel class.
The BackgroundGraphics Class deals with the
background of the area above the playlist
component. It is therefore called within the MainComponent to not be built twice in the DeckGUI. In it I used
ColourGradient::horizontal to create the gradient effect for the dark blue to mid blue base background and the
light blue to white background that features where the frequency visualiser is. I also added in a white lined
Path class as a border to separate the two functions and give the project more of the ‘Tron’ feeling.
I wanted the design to be mirrored so that it was more symmetrical, so in DeckGUI::resized() I created if
statements to use as the parameters of the setBounds for the width positions of each DeckGUI element. Each
DeckGUI called a different instance of this. I did this for the Turntable as well, within its own class.
For the components that were in DeckGUI that were required to be replicated, I used the DeckGUI to
implement them as slider classes for a LinearSlider and a RotarySlider. Using the OtherLookAndFeel class I
created, I was able to implement my own graphics onto the different sliders. I used this tutorial for reference
only when creating this class:
https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
For the linear slider I drew the thumb track as a pale blue rectangle, and then the thumb slider itself was drawn
as a small rectangular noggin that moved on drag. In the DeckGUI I also added a function named
setSliderStyles() that went into more detail about what information I wanted on the sliders, adding labels to
title them where appropriate.
For the PlaylistComponent and Waveform Display I enacted minor changes to the colours and style, but I also
included ImageButtons to the load, play and pause below the WaveFormDisplay. I used imageButtons in the
‘loadButton’, the ‘load into player 1 and 2’ buttons, and the ‘delete’ button in the PlaylistComponent that
highlighted on hover. I used this video as reference for adding the imageButtons:
https://www.youtube.com/watch?v=g_6UKygCp-0&t=14s.
R2BFor this part I created two new sliders, the bass and treble slider. These were using the IIRFilterAudioSource
filterSource that was called in the DJAudioPlayer class, initially in the prepare to play, and then in the functions
‘setBass’ and ‘setTreble’ I created. Slider listeners in the DeckGUI tell the sliderValueChanged when the value
has changed, and then the values are passed to the DJAudioPlayer::setBass or setTreble to change the
amplitude at the frequency of the treble/bass amount. The graphics for the rotary slider or ‘dial’ is created
within the OtherLookAndFeel class, which creates Paths that are concentric ‘addCentredArc’ arcs. The angle is
passed in as a parameter, which is altered when the DeckGUI::sliderValueChanged is called, and this rotates the
rotarySlider.
R3 –
For this part, I used inspiration from the VirtualDJ application: https://www.virtualdj.com/
Within it I saw three items that I wanted to implement into this feature within my app. Please see the three
items below I added and the reasoning and workings behind implementing them:
Reference image for
‘Tron’ slider and
graphics inspiration.
Turntable –
In a lot of DJ applications that I found online there was a turntable feature where you could ‘scratch’ the record
forwards or backwards. This is something I really wanted to understand to fully visualise a dj app.
I thought the best way of doing it was to create a class that contained the functionality, and called to the
OtherLookAndFeel class to get the graphics of the ‘record’ that would spin around.
After implementing the graphics of the record, the first part of the implementation was to work out how to
make the record start to spin when the play button was clicked, and then stop when the pause button was
clicked. I needed to use the functionality of the DeckGUI to do this, by creating a flag that said on the
playbutton’s buttonClicked, that the turntable was ready to start rotating. When the pause button was clicked
then the flag told the turntable class to stop rotating.
I then needed to create the ‘scratching’ effect. This was done by creating an invisible rotary slider in the
DeckGUI that I fixed to the value 1.5. If the rotary slider was moved left then the value would change to 1, if the
value was moved right then the value was changed to 2. At each scratch that the user would do, I would then
force the slider back to the 1.5 position so that it was easier to navigate each time the user wanted to scratch. I
then created if statements to deal with the two scenarios where the slider value was set to 1 and 2. For
scenario 1 the if statement changed the setPositionRelative function in the DJAudioPlayer to the current value -
0.01 and in scenario 2 it changed it to +0.02. They also altered two bool’s in the Turntable classes
‘pushRecordBackward’ and ‘pushRecordForward’ to true, which then animated the records to rotate the record
forward slightly or backward in if statements in the Turntable::timerCallback class.
Frequency Visualiser –
To see the effects of the knobs and dials that I had created on the screen being changed, I wanted to create a
visualiser. On the VirtualDJ application it used a bar that uses the levels at the bass and treble meter at a
specific point on the frequency, but what I wanted to show was the full spectrum of the frequency as moving
bars.
I found a tutorial from the Juce website which was a ‘spectrum analyser’
https://docs.juce.com/master/tutorial_spectrum_analyser.html. This used the FFT from the Juce::dsp module
that I added (which will be required for the project to work), and created a visualisation of the amplitude over
Turntable for
scratching.
Visualisers for
base and treble
filter effects.
PlaylistComponent
fully realised.
the frequency. I implemented it using the tutorial for guidance, but it wasn’t quite what I wanted, as it showed
the spectrum as a series of jagged lines. In place of this, in the ‘drawFrame’ function I changed it so that it was
a series of bars/rectangles that had a gradient colour that were mapped to the amplitude along the frequency
axis. The effect worked well.
Playlist Component –
To develop the playlistComponent I first needed to work out how to implement a load button. First, button id’s
were assigned in the refreshComponentForCell to each button. On buttonClicked I used an if statement that
flagged the specific button id, and used the FileBrowserComponent class and used launchAsync on the
fChooser to load the URL. I then converted it into a standard string along with getting the filename, and pushed
that data along with a bool operator ‘isTrackLoaded ‘ to say whether a file’s URL is loaded or not into a Class
vector called TrackLibrary that I created. This is a data structure that contains 6 rows of data for tracks to be
implemented into the playlist.
I then created a load into player 1 button and load into player 2 button, which had ids set in the
refreshComponentForCell. These were then called similarly in buttonclicked, and if they were clicked it would
send the URL from the trackLibrary vector class into the specified player in the DeckGUI::loadFileToDeck, which
then loads it in the DJAudioPlayer:: loadURL. This only happens if the bool ‘isTrackLoaded’ in the trackLibrary
on that specific row is also true.
After this I implemented a delete button which worked in the same way as the other tracks but would
overwrite the trackLibrary vector with the standard template, with the bool operator ‘isTrackLoaded ‘ set back
to false, and the URLs and the track names removed.

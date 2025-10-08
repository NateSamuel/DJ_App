/*student's work, vector<class> which is used as a data structure for the tracks being loaded in from the playlist component*/

#pragma once
#include <string>
class TrackLibrary
{
public:
    TrackLibrary(std::string _urlString,
                 std::string _trackName,
                 bool _isTrackLoaded);
    //stores URL strings for each row
    std::string urlString;
    //stores the track name of the specific URL string on each row
    std::string trackName;
    //stores a boolean for each row that, when true allows the URL to be pushed into the player 1 or player 2 GUI
    bool isTrackLoaded;
private:
};
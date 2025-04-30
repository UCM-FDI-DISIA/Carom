#pragma once
#include <unordered_map>
#include <string>
#include "SDLUtils.h"

class AudioManager{
public:
    
    AudioManager();
    
    void addNewTrack(std::string trackId);
    void playMusicTrack(std::string trackId);
    void pauseMusicTrack(int track);
    void resumeMusicTrack(int track);

    void playSoundEfect();
protected:
    std::unordered_map<std::string, Music&> musicTrack;
};
#pragma once
#include <array>
#include <string>
#include "Singleton.h"

class SoundEffect;

enum trackName{
    MARCHA_IMPERIAL,
    BEAT,
    PAUSE_THEME,
    MAIN_THEME,
    NUM_TRACKS
};

class AudioManager : public Singleton<AudioManager> {
    friend Singleton<AudioManager> ;
public:
    AudioManager();
    virtual ~AudioManager();
    
    void playMusicTrack(trackName trackID);
    void pauseMusicTrack(trackName trackID);
    void resumeMusicTrack(trackName trackID);
    void setVolumeMusicTrack(trackName trackID, int volume = 128);
    void changeToPauseTheme();
    void changeToMainTheme();

    void playSoundEfect(std::string soundID, int volume = 128);
    bool inline init(){return true;};

protected:
    std::array<SoundEffect*, NUM_TRACKS> musicTrack;
};
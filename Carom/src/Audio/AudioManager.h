#pragma once
#include <array>
#include <string>
#include "Singleton.h"

class SoundEffect;

enum trackName{
    BOSS_WHISPER,
    BEAT,
    PAUSE_THEME,
    MAIN_THEME,
    NUM_TRACKS
};

class AudioManager : public Singleton<AudioManager> {
    friend Singleton<AudioManager>;
public:
    AudioManager();
    virtual ~AudioManager();
    
    void playMusicTrack(trackName trackID);
    void pauseMusicTrack(trackName trackID);
    void resumeMusicTrack(trackName trackID);
    void setVolumeMusicTrack(trackName trackID, int volume = 64);
    void changeToPauseTheme();
    void changeToMainTheme();

    void playSoundEfect(std::string soundID, int volume = 64);
    bool inline init(){return true;};
    inline trackName getCurrentTheme() { return currentTheme; };

protected:
    std::array<SoundEffect*, NUM_TRACKS> musicTrack;
    trackName currentTheme;
};
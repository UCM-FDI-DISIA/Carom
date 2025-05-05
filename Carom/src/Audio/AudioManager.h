#pragma once
#include <array>
#include <string>

class SoundEffect;

enum trackName{
    MARCHA_IMPERIAL,
    BEAT,
    NUM_TRACKS
};

class AudioManager{
public:
    AudioManager();
    ~AudioManager();
    void playMusicTrack(trackName trackID);
    void pauseMusicTrack(trackName trackID);
    void resumeMusicTrack(trackName trackID);
    void setVolumeMusicTrack(trackName trackID, int volume = 128);

    void playSoundEfect(std::string soundID, int volume = 128);

protected:
    std::array<SoundEffect*, NUM_TRACKS> musicTrack;
};
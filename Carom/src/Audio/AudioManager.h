#pragma once
#include <array>
#include <string>

class Music;

enum trackName{
    MARCHA_IMPERIAL,
    BEAT,
    NUM_TRACKS
};

class AudioManager{
public:
    AudioManager();
    void playMusicTrack(trackName trackID);
    void pauseMusicTrack(trackName trackID);
    void resumeMusicTrack(trackName trackID);

    void playSoundEfect(std::string soundID, int volume = 70);

protected:
    std::array<Music&, NUM_TRACKS> musicTrack;
};
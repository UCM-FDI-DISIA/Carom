#include "AudioManager.h"
#include "sdlutils.h"

AudioManager::AudioManager(){
    musicTrack ={
        &sdlutils().soundEffects().at("imperial_march"),
        &sdlutils().soundEffects().at("beat")
    };
}

void AudioManager::playMusicTrack(trackName trackName){
    musicTrack[trackName]->play(-1, trackName);
}

void AudioManager::resumeMusicTrack(trackName trackName){
    musicTrack[trackName]->resumeChannel(trackName);
}

void AudioManager::pauseMusicTrack(trackName trackName){
    musicTrack[trackName]->pauseChannel(trackName);
}

void AudioManager::playSoundEfect(std::string soundID, int volume){
    sdlutils().soundEffects().at(soundID).setVolume(volume);
    sdlutils().soundEffects().at(soundID).play();
}

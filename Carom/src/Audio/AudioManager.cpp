#include "AudioManager.h"
#include "sdlutils.h"

AudioManager::AudioManager(){
    
    SoundEffect::setNumberofChannels(12);

    musicTrack ={
        &sdlutils().soundEffects().at("imperial_march"),
        &sdlutils().soundEffects().at("beat")
    };
}

AudioManager::~AudioManager(){
    for(auto track : musicTrack){
        delete track;
    }
}

void AudioManager::playMusicTrack(trackName trackID){
    musicTrack[trackID]->play(-1, trackID);
}

void AudioManager::resumeMusicTrack(trackName trackID){
    musicTrack[trackID]->resumeChannel(trackID);
}

void AudioManager::pauseMusicTrack(trackName trackID){
    musicTrack[trackID]->pauseChannel(trackID);
}

void AudioManager::setVolumeMusicTrack(trackName trackID, int volume = 128){
    musicTrack[trackID]->setVolume(volume);
}

void AudioManager::playSoundEfect(std::string soundID, int volume){
    sdlutils().soundEffects().at(soundID).setVolume(volume);
    sdlutils().soundEffects().at(soundID).play();
}
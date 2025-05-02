#include "AudioManager.h"
#include "sdlutils.h"

AudioManager::AudioManager(){
    musicTrack ={
        sdlutils().musics().at("imperial_march"),
        sdlutils().musics().at("beat")
    };
}

void AudioManager::playMusicTrack(trackName trackName){
    //musicTrack[trackName].play();
}

void AudioManager::resumeMusicTrack(trackName trackName){
    //musicTrack[trackName].resumeMusic();
}

void AudioManager::pauseMusicTrack(trackName trackName){
    //musicTrack[trackName].pauseMusic();
}

void AudioManager::playSoundEfect(std::string soundID, int volume){
    /*sdlutils().soundEffects().at(soundID).setVolume(volume);
    sdlutils().soundEffects().at(soundID).play();*/
}

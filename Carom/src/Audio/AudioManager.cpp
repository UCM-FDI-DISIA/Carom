#include "AudioManager.h"


AudioManager::AudioManager(){
    
}

void AudioManager::addNewTrack(std::string trackId){
    auto& a = sdlutils().musics().at("imperial_march");
    musicTrack[trackId]
}

void AudioManager::playMusicTrack(std::string trackId){
    if(musicTrack.contains(trackId)){
        musicTrack[trackId].play();
    }
}

void AudioManager::resumeMusicTrack(int track){
    sdlutils().musics().at("imperial_march").resumeMusic();
}

void AudioManager::pauseMusicTrack(int track){
    sdlutils().musics().at("imperial_march").pauseMusic();
}

void AudioManager::playSoundEfect(){

}

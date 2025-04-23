#include "AudioManager.h"
#include "SDLUtils.h"

AudioManager::AudioManager(){
    
}

void AudioManager::playMusic(){
    sdlutils().musics().at("imperial_march").play(2);
}
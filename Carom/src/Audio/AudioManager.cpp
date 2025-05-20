#include "AudioManager.h"
#include "sdlutils.h"

AudioManager::AudioManager(){
    
    SoundEffect::setNumberofChannels(12);

    musicTrack ={
        &sdlutils().soundEffects().at("boss_whisper"),
        &sdlutils().soundEffects().at("beat"),
        &sdlutils().soundEffects().at("pause_theme"),
        &sdlutils().soundEffects().at("main_theme")
    };

    setVolumeMusicTrack(trackName::BOSS_WHISPER, 12);
}

AudioManager::~AudioManager(){
    for(int i = 0; i < musicTrack.size(); ++i)
        musicTrack[i] = nullptr;
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

void AudioManager::setVolumeMusicTrack(trackName trackID, int volume){
    musicTrack[trackID]->setVolume(volume);
}

void AudioManager::playSoundEfect(std::string soundID, int volume){
    sdlutils().soundEffects().at(soundID).setVolume(volume);
    sdlutils().soundEffects().at(soundID).play();
}

void AudioManager::changeToPauseTheme(){
    setVolumeMusicTrack(MAIN_THEME, 0);
    setVolumeMusicTrack(PAUSE_THEME, 64);
    
    currentTheme = PAUSE_THEME;
}

void AudioManager::changeToMainTheme(){
    setVolumeMusicTrack(MAIN_THEME, 64);
    setVolumeMusicTrack(PAUSE_THEME, 0);

    currentTheme = MAIN_THEME;
}

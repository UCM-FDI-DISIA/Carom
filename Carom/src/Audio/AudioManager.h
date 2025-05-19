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
    
    /// @brief Empieza a sonar una cancion de una pista en concreto
    /// @param trackID Nombre de la pista en la que esta la cancion
    void playMusicTrack(trackName trackID);

    /// @brief Pausa una cancion de una pista en concreto
    /// @param trackID Nombre de la pista en la que esta la cancion
    void pauseMusicTrack(trackName trackID);

    /// @brief Continua sonando una cancion pausada de una pista en concreto
    /// @param trackID Nombre de la pista en la que esta la cancion
    void resumeMusicTrack(trackName trackID);

    /// @brief Cambia el volumen de una cancion de una pista en concreto
    /// @param trackID Nombre de la pista en la que esta la cancion
    /// @param volume Volumen que le quieres dar a la pista con la cancion
    void setVolumeMusicTrack(trackName trackID, int volume = 15);

    void changeToPauseTheme();
    void changeToMainTheme();

    /// @brief Ejecuta un efecto desonido
    /// @param soundID La key con la que esta guardo el efecto de sonido en resources.json
    /// @param volume Volumen que le quieres dar al efecto de sonido
    void playSoundEfect(std::string soundID, int volume = 15);
    
    bool inline init(){return true;};
    inline trackName getCurrentTheme() { return currentTheme; };

protected:
    std::array<SoundEffect*, NUM_TRACKS> musicTrack;
    trackName currentTheme;
};
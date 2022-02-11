#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

class Music
{
private:
    static int MixNUM;
public:
    Music();
    virtual ~Music();

};

class EffectSound: public Music
{
private:
    Mix_Chunk* sound;
public:
    EffectSound(const std::string& sound_fileName);
    ~EffectSound();
    void play() const;
};

class MusicSound: public Music
{
private:
    Mix_Music* music;
public:
    MusicSound(const std::string& music_fileName);
    ~MusicSound();
    void play() const;
    void stop() const;
};

#include "GameMusic.h"

GameMusic::GameMusic()
{
	Sound1 = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm1.mp3", 0, 0, 0);
	Sound2 = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm2.mp3", 0, 0, 0);
	Sound3 = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm3.mp3", 0, 0, 0);
	Sound4 = ::BASS_StreamCreateFile(FALSE, "res/BGM/bgm4.mp3", 0, 0, 0);
}

GameMusic::~GameMusic()
{
	BASS_Free();
}

void GameMusic::PlayMusic(HSTREAM _sound)
{
	BASS_ChannelPlay(_sound, true);
}

void GameMusic::StopMusic(HSTREAM _sound)
{
	BASS_ChannelStop(_sound);
}
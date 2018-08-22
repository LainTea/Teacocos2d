/*FOR Le-mondai*/
#pragma once
#include <bass.h>
#pragma comment(lib, "bass.lib")
class GameMusic
{
private:
	GameMusic();
public:
	~GameMusic();

	static GameMusic* Instance()
	{
		static GameMusic Gmusic;
		return &Gmusic;
	}

	void PlayMusic(HSTREAM _sound);
	void StopMusic(HSTREAM _sound);

	HRESULT hResult = ::BASS_Init(-1, 44100, 0, NULL, NULL);

	HSTREAM Sound1, Sound2, Sound3, Sound4;
};


#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include "irrKlang.h"
#include <set>
#include <map>
#include <string>
#include "Vector3.h"
#include "SingletonTemplate.h"

using std::string;
using namespace irrklang;
using std::set;
using std::map;

class AudioManager : public Singleton<AudioManager> {

	friend class Singleton<AudioManager>;

private:
	//Variable(s)
	ISoundEngine* audioEngine;
	set<ISound*> audioList;

	//Constructor & Destructor
	AudioManager();
	virtual ~AudioManager();

public:
	//Function(s)
	void Update();
	bool PlayAudio2D(const string& audioFile, bool looped, float volume = 1.0f);
	bool PlaySoleAudio2D(const string& audioFile, bool looped, float volume = 1.0f);
	bool PlayAudio3D(const string& audioFile, bool looped, float minDistance, float maxDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector = Vector3(0, 1, 0), float volume = 1.0f);
	bool PlayAudio3D(const string& audioFile, bool looped, float minDistance, Vector3 listenerPosition, Vector3 listenerDirection, Vector3 soundPosition, Vector3 upVector = Vector3(0, 1, 0), float volume = 1.0f);
	bool UpdateAudio3D(const string& audioFile, Vector3 soundPosition);
	bool UpdateListener3D(Vector3 listenerPosition, Vector3 listenerDirection, Vector3 upVector = Vector3(0, 1, 0));
	bool PauseAudioList(bool state);
	bool ClearAudioList();
	void SetVolumeAll(const float& volume); //Only works a bit.

};

#endif
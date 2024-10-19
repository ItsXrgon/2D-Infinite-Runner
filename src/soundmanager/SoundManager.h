#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <string>
#include <map>
#include <cstdio>

class SoundManager {
protected:
	ALCdevice* device;
	ALCcontext* context;
	std::map<std::string, ALuint> buffers;
	std::map<std::string, ALuint> sources;
	ALuint musicSource;
public:
	SoundManager();
	~SoundManager();

	bool loadWAV(const std::string& name, const std::string& filename);
	void playSound(const std::string& name);
	bool loadBackgroundMusic(const std::string& name, const std::string& filename);
	void playBackgroundMusic(const std::string& name);
	void stopBackgroundMusic();
	void cleanup();
};


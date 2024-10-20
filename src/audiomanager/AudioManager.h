#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>
#include <map>
#include <AL/al.h>
#include <AL/alc.h>

class AudioManager {
protected:
	ALCdevice* audioDevice;
	ALCcontext* audioContext;
	ALuint bgSource;
	std::map<std::string, ALuint> audioBuffers;

	void loadFile(const std::string& filepath, ALuint* buffer);
public:
	AudioManager();
	~AudioManager();

	void addFile(const std::string& name, const std::string& filepath);
	void playFile(const std::string& name);
	void playMusic(const std::string& name); 
	void stopMusic();
};

#endif
#include "SoundManager.h"
#include <vector>
#include <fstream>
#include <cstdarg> 


SoundManager::SoundManager() {
	device = alcOpenDevice(nullptr);

	context = alcCreateContext(device, nullptr);
	if (!alcMakeContextCurrent(context)) {
		printf("Failed to set audio context!\n");
	}

	alGenSources(1, &musicSource);
}

SoundManager::~SoundManager() {
	cleanup();
}

bool SoundManager::loadWAV(const std::string& name, const std::string& filename) {
	std::ifstream file(filename, std::ios::binary);
	if (!file) {
		printf("Failed to load WAV file: %s\n", filename.c_str());
		return false;
	}

	file.seekg(44, std::ios::beg);
	std::vector<char> bufferData(std::istreambuf_iterator<char>(file), {});

	ALuint buffer;
	alGenBuffers(1, &buffer);
	alBufferData(buffer, AL_FORMAT_MONO16, bufferData.data(), bufferData.size(), 44100);

	buffers[name] = buffer;

	ALuint source;
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer);

	sources[name] = source;

	return true;
}

void SoundManager::playSound(const std::string& name) {
	alSourcePlay(sources[name]);
}

bool SoundManager::loadBackgroundMusic(const std::string& name, const std::string& filename) {
	return loadWAV(name, filename);
}

void SoundManager::playBackgroundMusic(const std::string& name) {
	alSourcei(musicSource, AL_BUFFER, buffers[name]);
	alSourcePlay(musicSource);
}

void SoundManager::stopBackgroundMusic() {
	alSourceStop(musicSource);
}

void SoundManager::cleanup() {
	for (auto it = sources.begin(); it != sources.end(); ++it) {
		ALuint source = it->second;
		alSourceStop(source);
		alDeleteSources(1, &source);
	}

	sources.clear();

	for (auto it = buffers.begin(); it != buffers.end(); ++it) {
		ALuint buffer = it->second;
		alDeleteBuffers(1, &buffer);
	}

	buffers.clear();

	if (alIsSource(musicSource)) {
		alSourceStop(musicSource);
		alDeleteSources(1, &musicSource);
	}

	alcMakeContextCurrent(nullptr);
	if (context) {
		alcDestroyContext(context);
		context = nullptr;
	}

	if (device) {
		alcCloseDevice(device);
		device = nullptr;
	}
}
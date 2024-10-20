#include "AudioManager.h"
#include <vector>
#include <fstream>
#include <cstdio>

AudioManager::AudioManager() {
	audioDevice = alcOpenDevice(nullptr);

	if (!audioDevice) {
		exit(EXIT_FAILURE);
	}

	audioContext = alcCreateContext(audioDevice, nullptr);
	if (!alcMakeContextCurrent(audioContext)) {
		exit(EXIT_FAILURE);
	}

	alGenSources(1, &bgSource);
}

AudioManager::~AudioManager() {
	for (auto& buffer : audioBuffers) {
		alDeleteBuffers(1, &buffer.second);
	}
	alDeleteSources(1, &bgSource);

	alcMakeContextCurrent(nullptr);
	alcDestroyContext(audioContext);
	alcCloseDevice(audioDevice);
}

void AudioManager::loadFile(const std::string& filepath, ALuint* buffer) {
	std::ifstream file(filepath, std::ios::binary);

	if (!file.is_open()) {
		return;
	}

	char header[44];
	file.read(header, 44);

	if (!file) {
		file.close();
		return;
	}

	int channels = header[22];
	int sampleRate = *(int*)&header[24];
	int bitsPerSample = header[34];

	if (bitsPerSample != 16) {
		file.close();
		return;
	}

	ALenum format;
	if (channels == 1) {
		format = AL_FORMAT_MONO16;
	}
	else if (channels == 2) {
		format = AL_FORMAT_STEREO16;
	} else {
		file.close();
		return;
	}

	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(44, std::ios::beg);

	std::vector<char> data(fileSize - 44);
	file.read(data.data(), fileSize - 44);

	if (!file) {
		file.close();
		return;
	}

	alGenBuffers(1, buffer);
	ALenum error = alGetError();
	if (error != AL_NO_ERROR) {
		file.close();
		return;
	}

	alBufferData(*buffer, format, data.data(), data.size(), sampleRate);
	error = alGetError();

	file.close();
}

void AudioManager::addFile(const std::string& name, const std::string& filepath) {
	ALuint buffer;
	loadFile(filepath, &buffer);
	audioBuffers[name] = buffer;
}

void AudioManager::playFile(const std::string& name) {
	if (audioBuffers.find(name) != audioBuffers.end()) {
		ALuint effectSource;
		alGenSources(1, &effectSource);

		if (alIsSource(effectSource)) {
			alSourcei(effectSource, AL_BUFFER, audioBuffers[name]);

			alSourcePlay(effectSource);

			ALenum error = alGetError();
		}
	}
}

void AudioManager::playMusic(const std::string& name) {
	if (audioBuffers.find(name) != audioBuffers.end()) {
		alSourcei(bgSource, AL_BUFFER, audioBuffers[name]);
		alSourcei(bgSource, AL_LOOPING,  AL_TRUE);
		alSourcePlay(bgSource);
	}
}

void AudioManager::stopMusic() {
	alSourceStop(bgSource); // Stop the background music
}
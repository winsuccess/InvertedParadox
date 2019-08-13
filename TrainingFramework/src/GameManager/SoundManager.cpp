#include "SoundManager.h"
#include <iostream>
#include<map>

SoundManager::SoundManager()
{
	std::string dataPath = "..\\Data\\";
	m_SoundsPath = dataPath + "Sounds\\";
	m_Soloud = std::make_shared<SoLoud::Soloud>();
	m_Soloud->init();
}

SoundManager::~SoundManager()
{
	m_MapWave.clear();
	m_Soloud->deinit();
}

void SoundManager::AddSound(const std::string& name,bool loop)
{
	std::cout << "Add Sound";
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		return;
	}
	std::shared_ptr<SoLoud::Wav>  wave;
	std::string wav = m_SoundsPath + name + ".wav";
	wave = std::make_shared<SoLoud::Wav>();
	wave->load(wav.c_str()); // Load a wave file
	m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
	wave->setLooping(loop);
}

void SoundManager::PlaySound(const std::string& name)
{
	std::shared_ptr<SoLoud::Wav>  wave;
	//if (loop) {
	//	wave->setLooping(1);
	//}
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	else
	{
		std::string wav = m_SoundsPath + name + ".wav";
		wave = std::make_shared<SoLoud::Wav>();
		wave->load(wav.c_str()); // Load a wave file
		m_MapWave.insert(std::pair<std::string, std::shared_ptr<SoLoud::Wav>>(name, wave));
	}
	m_Soloud->play(*wave);
}

void SoundManager::PauseSound(const std::string& name)
{
	std::shared_ptr<SoLoud::Wav>  wave;
	auto it = m_MapWave.find(name);
	if (it != m_MapWave.end())
	{
		wave = it->second;
	}
	m_Soloud->stopAudioSource(*wave);
}

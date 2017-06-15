#ifndef _SOUND_MGR_H_
#define _SOUND_MGR_H_

#include "SimpleAudioEngine.h"
#include "SoundConfig.h"
#define AE() CocosDenshion::SimpleAudioEngine::getInstance()

class SoundMgr
{
public:
	static void playBackgroundMusic(const char* musicName, bool loop = false)
	{
		auto pszFilePath = SoundConfig::getInfo(musicName);
		if (!pszFilePath) {
			pszFilePath = musicName;
		}
		AE()->playBackgroundMusic(pszFilePath, loop);
	}

	static void stopBackgroundMusic(bool releaseData = false)
	{
		AE()->stopBackgroundMusic(releaseData);
	}

	static void pauseBackgroundMusic()
	{
		AE()->pauseBackgroundMusic();
	}

	static void resumeBackgroundMusic()
	{
		AE()->resumeBackgroundMusic();
	}

	static bool isBackgroundMusicPlaying()
	{
		return AE()->isBackgroundMusicPlaying();
	}

	static float getBackgroundMusicVolume()
	{
		return AE()->getBackgroundMusicVolume();
	}

	static void setBackgroundMusicVolume(float volume)
	{
		AE()->setBackgroundMusicVolume(volume);
	}
	
		static float getEffectsVolume()
	{
		return AE()->getEffectsVolume();
	}

	
	static void setEffectsVolume(float volume)
	{
		AE()->setEffectsVolume(volume);
	}

	
	static unsigned int playEffect(const char* szEfxName, bool bLoop = false)
	{
		const char* pszFilePath = SoundConfig::getInfo(szEfxName);
		if (pszFilePath == NULL) {
			pszFilePath = szEfxName;
		}
		return AE()->playEffect(pszFilePath, bLoop);
	}
	
	static void pauseEffect(unsigned int nSoundId)
	{
		AE()->pauseEffect(nSoundId);
	}

	
	static void pauseAllEffects()
	{
		AE()->pauseAllEffects();
	}

	
	static void resumeEffect(unsigned int nSoundId)
	{
		AE()->resumeEffect(nSoundId);
	}

	
	static void resumeAllEffects()
	{
		AE()->resumeAllEffects();
	}

	
	static void stopEffect(unsigned int nSoundId)
	{
		AE()->stopEffect(nSoundId);
	}

	static void stopAllEffects()
	{
		AE()->stopAllEffects();
	}

	
	static void preloadEffect(const char* szEfxName)
	{
		const char* pszFilePath = SoundConfig::getInfo(szEfxName);
		if (pszFilePath == nullptr) {
			pszFilePath = szEfxName;
		}
		AE()->preloadEffect(pszFilePath);
	}

	
	static void unloadEffect(const char* szEfxName)
	{
		const char* pszFilePath = SoundConfig::getInfo(szEfxName);
		if (pszFilePath == nullptr) {
			pszFilePath = szEfxName;
		}
		AE()->unloadEffect(pszFilePath);
	}
};

#endif // !_SOUND_MGR_H_

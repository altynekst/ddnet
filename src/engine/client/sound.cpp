/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include "sound.h"

#include <base/log.h>
#include <base/math.h>
#include <base/system.h>

#include <engine/graphics.h>
#include <engine/shared/config.h>
#include <engine/storage.h>

#include <SDL.h>

#if defined(CONF_VIDEORECORDER)
#include <engine/shared/video.h>
#endif

#include <cmath>

static constexpr int SAMPLE_INDEX_USED = -2;
static constexpr int SAMPLE_INDEX_FULL = -1;
static constexpr int NUM_VOICES = 256; // нужно добавить, если нет в хедере

void CSound::Mix(short *pFinalOut, unsigned Frames)
{
	Frames = minimum(Frames, m_MaxFrames);
	mem_zero(m_pMixBuffer, Frames * 2 * sizeof(int));

	// acquire lock while we are mixing
	m_SoundLock.lock();

	const int MasterVol = m_SoundVolume.load(std::memory_order_relaxed);

	for(auto &Voice : m_aVoices)
	{
		if(!Voice.m_pSample)
			continue;
		
		// Basic mixing
		int *pMix = m_pMixBuffer;
		short *pSample = Voice.m_pSample->m_pData;
		
		for(unsigned i = 0; i < Frames; i++)
		{
			pMix[0] += pSample[0] * MasterVol / 100;
			pMix[1] += pSample[1] * MasterVol / 100;
			pMix += 2;
			pSample += 2;
		}
	}

	m_SoundLock.unlock();

	// clamp and convert to short
	for(unsigned i = 0; i < Frames * 2; i++)
	{
		int v = m_pMixBuffer[i] / NUM_VOICES; // используем константу вместо .size()
		if(v < -32768) v = -32768;
		if(v > 32767) v = 32767;
		pFinalOut[i] = v;
	}
}

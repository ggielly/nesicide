#include <stdio.h>
#include <boost/thread/mutex.hpp>
#include "alsa.hpp"
#include "core/time.hpp"

core_api_SoundSink * sound_create()
{
  return new AlsaSound;
}

struct _alsasound_threading
{
	boost::mutex mtx_running;
};

AlsaSound::AlsaSound()
	: m_handle(NULL), m_running(false)
{
	m_threading = new _alsasound_threading;
}
AlsaSound::~AlsaSound()
{
	m_thread.wait();
	AlsaSound::close();
	setPlaying(false);

	delete m_threading;
}

#define ALSA_TRY(x) if ( (err = (x)) < 0){ fprintf(stderr, "ERROR: %s\n", snd_strerror(err)); }

void AlsaSound::callback_bootstrap(void *data)
{
	AlsaSound *as = (AlsaSound*)data;
	as->callback();
}

void AlsaSound::callback()
{
	int err;
	core::u32 bufsz = m_buffer_size;
	core::s16 *buf = new core::s16[bufsz];

	core::u32 sr = sampleRate();

	core::u64 latency = m_buffer_size;
	latency = latency * 1000000 / sr;

	bool running = true;

	while (running)
	{
		m_threading->mtx_running.lock();
		running = m_running;
		m_threading->mtx_running.unlock();
		if (running)
		{
			snd_pcm_sframes_t delayp;

			core::u32 sz = m_period_size;

			performSoundCallback(buf, sz);

			snd_pcm_sframes_t frames = snd_pcm_writei(m_handle, buf, sz);
			snd_pcm_delay(m_handle, &delayp);

			core::s64 d = delayp * 1000000 / sr;
			d -= latency;

			applyTime(d);

			if (frames < 0)
			{
				frames = snd_pcm_recover(m_handle, frames, 0);
			}
			if (frames < 0)
			{
				// error
				fprintf(stderr, "snd_pcm_writei failed: %s\n", snd_strerror(frames));
			}
			if (frames > 0 && frames != (long)sz)
			{
				// error
				fprintf(stderr, "Short write (expected %li, wrote %li)\n", (long)sz, frames);
			}
		}
	}

	delete[] buf;

	ALSA_TRY(snd_pcm_drain(m_handle));
	ALSA_TRY(snd_pcm_prepare(m_handle));
}

void AlsaSound::setPlaying(bool playing)
{
	bool changed = playing != isPlaying();

	if (!changed)
		return;

	m_threading->mtx_running.lock();
	m_running = playing;
	m_threading->mtx_running.unlock();

	if (playing)
	{
		SoundSink::setPlaying(playing);
		m_thread.run(callback_bootstrap, this);
	}
	else
	{
		SoundSink::setPlaying(playing);
	}
}

void AlsaSound::initialize(unsigned int sampleRate, unsigned int channels, unsigned int latency_ms)
{
	AlsaSound::close();

	int err;

	if ((err = snd_pcm_open(&m_handle, "default", SND_PCM_STREAM_PLAYBACK, 0)) < 0)
	{
		// error
		fprintf(stderr, "Playback open error: %s\n", snd_strerror(err));
		return;
	}

	if ((err = snd_pcm_set_params(m_handle,
								  SND_PCM_FORMAT_S16,
								  SND_PCM_ACCESS_RW_INTERLEAVED,
								  channels,
								  sampleRate,
								  1,
								  latency_ms*1000)) < 0)
	{
		// error
		fprintf(stderr, "Playback open error: %s\n", snd_strerror(err));
		return;
	}

	snd_pcm_get_params(m_handle, &m_buffer_size, &m_period_size);

	m_sampleRate = sampleRate;
}

void AlsaSound::close()
{
	if (m_handle != NULL)
	{
		snd_pcm_close(m_handle);
	}
}

int AlsaSound::sampleRate() const
{
	return m_sampleRate;
}

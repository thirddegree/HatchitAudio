/**
**    Hatchit Engine
**    Copyright(c) 2015-2016 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/

#include <ht_audiosource.h>

namespace Hatchit
{
    namespace Audio
    {
        Source::Source(Core::Guid ID) : Core::RefCounted<Source>(std::move(ID)),
            m_source(0)
        {
        }

        Source::~Source()
        {
            if (m_source)
            {
                alDeleteSources(1, &m_source);
            }
        }

        bool Source::Initialize()
        {
            alGetError();   //Clear error
            alGenSources(1, &m_source);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::Play()
        {
            alGetError();
            alSourcePlay(m_source);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::Pause()
        {
            alGetError();
            alSourcePause(m_source);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::Stop()
        {
            alGetError();
            alSourceStop(m_source);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::Rewind()
        {
            alGetError();
            alSourceRewind(m_source);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::QueueBuffer(BufferHandle buffer)
        {
            alGetError();
            alSourceQueueBuffers(
                m_source,
                1,
                &(buffer->GetBuffer()));
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::UnqueueBuffer(BufferHandle buffer)
        {
            alGetError();
            alSourceUnqueueBuffers(
                m_source,
                1,
                &(buffer->GetBuffer()));
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetPosition(const ALfloat* values)
        {
            alGetError();
            alSourcefv(
                m_source,
                AL_POSITION,
                values);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetPosition(ALfloat x, ALfloat y, ALfloat z)
        {
            alGetError();
            alSource3f(
                m_source,
                AL_POSITION,
                x,
                y,
                z);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetDirection(const ALfloat* values)
        {
            alGetError();
            alSourcefv(
                m_source,
                AL_DIRECTION,
                values);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetDirection(ALfloat x, ALfloat y, ALfloat z)
        {
            alGetError();
            alSource3f(
                m_source,
                AL_DIRECTION,
                x,
                y,
                z);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetPitch(ALfloat newPitch)
        {
            alGetError();
            alSourcef(
                m_source,
                AL_PITCH,
                newPitch);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetGain(ALfloat newGain)
        {
            alGetError();
            alSourcef(
                m_source,
                AL_GAIN,
                newGain);
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::SetLooping(bool newVal)
        {
            alGetError();
            alSourcei(
                m_source,
                AL_LOOPING,
                newVal ? 1 : 0);
            return alGetError() == AL_NO_ERROR;
        }

        Source::State Source::GetState()
        {
            ALint value;
            alGetError();
            alGetSourcei(
                m_source,
                AL_SOURCE_STATE,
                &value);
            return Source::State(value);
        }

        int Source::GetNumBuffersQueued()
        {
            ALint value;
            alGetError();
            alGetSourcei(
                m_source,
                AL_BUFFERS_QUEUED,
                &value);
            if (alGetError() != AL_NO_ERROR)
                return -1;
            return value;
        }

        int Source::GetNumBuffersProcessed()
        {
            ALint value;
            alGetError();
            alGetSourcei(
                m_source,
                AL_BUFFERS_PROCESSED,
                &value);
            if (alGetError() != AL_NO_ERROR)
                return -1;
            return value;
        }
    }
}
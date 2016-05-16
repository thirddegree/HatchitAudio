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

#include <array>
#include <ht_debug.h>

namespace Hatchit
{
    namespace Audio
    {
        Source::Source()
            : m_source(0)
        {
            if (!Initialize())
                HT_ERROR_PRINTF("Error initializing AudioSource.\n");
        }

        Source::Source(const Source& source)
            : m_source(0)
        {
            if (!Initialize())
            {
                HT_ERROR_PRINTF("Error initializing AudioSource.\n");
                return;
            }
            //Copy info
            if (!CopyInfo(source))
                HT_ERROR_PRINTF("Error copying AudioSource information.\n");
        }

        Source::Source(Source&& source)
            : m_source(std::move(source.m_source))
        {
            source.m_source = 0;
        }

        Source::~Source()
        {
            DeInitialize();
        }

        Source& Source::operator=(const Source& source)
        {
            if (!CopyInfo(source))
                HT_ERROR_PRINTF("Error copying AudioSource information.\n");

            return *this;
        }

        Source& Source::operator=(Source&& source)
        {
            DeInitialize();
            m_source = std::move(source.m_source);
            source.m_source = 0;
            return *this;
        }

        bool Source::Initialize()
        {
            alGetError();   //Clear error
            alGenSources(1, &m_source);
            return alGetError() == AL_NO_ERROR;
        }

        void Source::DeInitialize()
        {
            if (m_source)
            {
                alDeleteSources(1, &m_source);
            }
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

        bool Source::QueueBuffer(const Buffer& buffer)
        {
            alGetError();
            alSourceQueueBuffers(
                m_source,
                1,
                &(buffer.GetBuffer()));
            return alGetError() == AL_NO_ERROR;
        }

        bool Source::UnqueueBuffer(Buffer& buffer)
        {
            alGetError();
            alSourceUnqueueBuffers(
                m_source,
                1,
                &(buffer.GetBuffer()));
            return alGetError() == AL_NO_ERROR;
        }

        void Source::GetPosition(std::array<ALfloat, 3>& outValueArray) const
        {
            GetPosition(outValueArray.data());
        }

        void Source::GetPosition(ALfloat* outValueArray) const
        {
            alGetSourcefv(m_source, AL_POSITION, outValueArray);
        }

        void Source::GetDirection(std::array<ALfloat, 3>& outValueArray) const
        {
            GetDirection(outValueArray.data());
        }

        void Source::GetDirection(ALfloat* outValueArray) const
        {
            alGetSourcefv(m_source, AL_DIRECTION, outValueArray);
        }

        ALfloat Source::GetPitch() const
        {
            ALfloat outValue;
            alGetSourcef(m_source, AL_PITCH, &outValue);
            return outValue;
        }

        ALfloat Source::GetGain() const
        {
            ALfloat outValue;
            alGetSourcef(m_source, AL_GAIN, &outValue);
            return outValue;
        }

        bool Source::GetLooping() const
        {
            ALint outValue;
            alGetSourcei(m_source, AL_LOOPING, &outValue);
            return outValue == AL_TRUE;
        }

        Source::State Source::GetState() const
        {
            ALint value;
            alGetError();
            alGetSourcei(
                m_source,
                AL_SOURCE_STATE,
                &value);
            return Source::State(value);
        }

        int Source::GetNumBuffersQueued() const
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

        int Source::GetNumBuffersProcessed() const
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

        bool Source::SetPosition(const std::array<ALfloat, 3>& values)
        {
            return SetPosition(values.data());
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

        bool Source::SetDirection(const std::array<ALfloat, 3>& values)
        {
            return SetDirection(values.data());
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

        

        bool Source::CopyInfo(const Source& source)
        {
            ALfloat valueArray[3];
            source.GetPosition(valueArray);
            if (!SetPosition(valueArray)) return false;
            source.GetDirection(valueArray);
            if (!SetDirection(valueArray)) return false;

            if (!SetPitch(source.GetPitch())) return false;
            if (!SetGain(source.GetGain())) return false;
            if (!SetLooping(GetLooping())) return false;

            return true;
        }
    }
}
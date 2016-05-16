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

#pragma once

#include <ht_platform.h> //HT_API
#include <AL/al.h>
#include <AL/alc.h>
#include <ht_audiobuffer.h> //BufferHandle
#include <array> //std::array

namespace Hatchit
{
    namespace Audio
    {
        class HT_API Source
        {
        public:

            enum class State : ALint
            {
                Initial = AL_INITIAL,
                Playing = AL_PLAYING,
                Paused = AL_PAUSED,
                Stopped = AL_STOPPED,
                Error = AL_INVALID_OPERATION
            };

            Source();
            Source(const Source& source);
            Source(Source&& source);
            virtual ~Source();

            Source& operator=(Source&& source);
            Source& operator=(const Source& source);

            bool Initialize();
            void DeInitialize();

            bool Play();
            bool Pause();
            bool Stop();
            bool Rewind();

            bool QueueBuffer(const Buffer& b);
            bool UnqueueBuffer(Buffer& b);

            //Getters
            void GetPosition(std::array<ALfloat, 3>& outValueArray) const;
            void GetPosition(ALfloat* outValueArray) const;
            void GetDirection(std::array<ALfloat, 3>& outValueArray) const;
            void GetDirection(ALfloat* outValueArray) const;

            ALfloat GetPitch() const;
            ALfloat GetGain() const;
            bool GetLooping() const;

            State GetState() const;
            int GetNumBuffersQueued() const;
            int GetNumBuffersProcessed() const;

            bool SetPosition(const std::array<ALfloat, 3>& values);
            bool SetPosition(const ALfloat* values);
            bool SetPosition(ALfloat x, ALfloat y, ALfloat z);
            bool SetDirection(const std::array<ALfloat, 3>& values);
            bool SetDirection(const ALfloat* values);
            bool SetDirection(ALfloat x, ALfloat y, ALfloat z);

            bool SetPitch(ALfloat newPitch);
            bool SetGain(ALfloat newGain);
            bool SetLooping(bool newVal);

        private:
            bool CopyInfo(const Source& source);
            ALuint m_source;
        };
    }
}
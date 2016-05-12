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
#include <ht_refcounted.h> //Core::RefCounted<T>
#include <ht_guid.h> //Core::Guid
#include <AL/al.h>
#include <AL/alc.h>
#include <ht_audiobuffer.h> //BufferHandle

namespace Hatchit
{
    namespace Audio
    {
        class HT_API Source final : public Core::RefCounted<Source>
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

            Source(Core::Guid ID);
            virtual ~Source();

            //Required function for all refCounted classes
            bool Initialize();

            bool Play();
            bool Pause();
            bool Stop();
            bool Rewind();

            bool QueueBuffer(BufferHandle b);
            bool UnqueueBuffer(BufferHandle b);

            bool SetPosition(const ALfloat* values);
            bool SetPosition(ALfloat x, ALfloat y, ALfloat z);
            bool SetDirection(const ALfloat* values);
            bool SetDirection(ALfloat x, ALfloat y, ALfloat z);

            bool SetPitch(ALfloat newPitch);
            bool SetGain(ALfloat newGain);
            bool SetLooping(bool newVal);

            State GetState();
            int GetNumBuffersQueued();
            int GetNumBuffersProcessed();

        private:
            ALuint m_source;
        };
    }
}
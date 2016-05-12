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

namespace Hatchit
{
    namespace Audio
    {
        class HT_API Buffer final : public Core::RefCounted<Buffer>
        {
        public:
            enum class Format : ALenum
            {
                Mono8 = AL_FORMAT_MONO8,
                Mono16 = AL_FORMAT_MONO16,
                Stereo8 = AL_FORMAT_STEREO8,
                Stereo16 = AL_FORMAT_STEREO16
            };

            Buffer(Core::Guid ID);
            virtual ~Buffer();

            //Required function for all refCounted classes
            bool Initialize();

            bool SetData(
                Format format,
                const void* data,
                ALsizei dataSize,
                ALsizei frequency);

        private:
            friend class Source;
            ALuint& GetBuffer();

            ALuint m_buffer;
        };

        using BufferHandle = Core::Handle<Buffer>;
    }
}
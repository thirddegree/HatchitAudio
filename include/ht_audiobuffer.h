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
#include <ht_noncopy.h>
#include <cstdlib>
#include <AL/al.h>
#include <AL/alc.h>

namespace Hatchit
{
    namespace Audio
    {
        class HT_API Buffer : public Core::INonCopy
        {
        public:
            static constexpr size_t BufferSize = 4096;

            enum class Format : ALenum
            {
                Mono8 = AL_FORMAT_MONO8,
                Mono16 = AL_FORMAT_MONO16,
                Stereo8 = AL_FORMAT_STEREO8,
                Stereo16 = AL_FORMAT_STEREO16
            };

            Buffer();
            Buffer(const Buffer&) = delete;
            Buffer(Buffer&& buffer);
            virtual ~Buffer();

            Buffer& operator=(const Buffer&) = delete;
            Buffer& operator=(Buffer&& buffer);

            bool Initialize();
            void DeInitialize();

            bool SetData(
                Format format,
                const void* data,
                ALsizei dataSize,
                ALsizei frequency);

            size_t GetBufferSize() const;

        private:
            friend class Source;
            const ALuint& GetBuffer() const;
            ALuint& GetBuffer();

            ALuint m_buffer;
            size_t m_bufferSize;
        };
    }
}

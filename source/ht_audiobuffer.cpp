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

#include <ht_audiobuffer.h>

#include <ht_debug.h>
#include <utility>

namespace Hatchit
{
    namespace Audio
    {
        Buffer::Buffer()
            : m_buffer(0),
            m_bufferSize(0)
        {
            if (!Initialize())
                HT_ERROR_PRINTF("Error initializing AudioBuffer.\n");
        }

        Buffer::Buffer(Buffer&& buffer)
            : m_buffer(std::move(buffer.m_buffer)),
            m_bufferSize(std::move(buffer.m_bufferSize))
        {
            buffer.m_buffer = 0;
        }

        Buffer::~Buffer()
        {
            DeInitialize();
        }

        Buffer& Buffer::operator=(Buffer&& buffer)
        {
            m_buffer = std::move(buffer.m_buffer);
            m_bufferSize = std::move(buffer.m_bufferSize);
            buffer.m_buffer = 0;
            return *this;
        }

        bool Buffer::Initialize()
        {
            alGetError();   //Clear error
            alGenBuffers(1, &m_buffer);
            return alGetError() == AL_NO_ERROR;
        }

        void Buffer::DeInitialize()
        {
            if (m_buffer)
            {
                alDeleteBuffers(1, &m_buffer);
            }
        }

        bool Buffer::SetData(
            Format format,
            const void* data,
            ALsizei dataSize,
            ALsizei frequency)
        {
            alGetError();   //Clear error
            alBufferData(
                m_buffer,
                static_cast<ALenum>(format),
                data,
                dataSize,
                frequency);
            m_bufferSize = dataSize;
            return alGetError() == AL_NO_ERROR;
        }

        size_t Buffer::GetBufferSize() const
        {
            return m_bufferSize;
        }

        const ALuint& Buffer::GetBuffer() const
        {
            return m_buffer;
        }

        ALuint& Buffer::GetBuffer()
        {
            return m_buffer;
        }
    }
}
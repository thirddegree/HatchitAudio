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

namespace Hatchit
{
    namespace Audio
    {
        Buffer::Buffer(Core::Guid ID)
            : Core::RefCounted<Buffer>(std::move(ID)),
            m_buffer(0)
        {
        }

        Buffer::~Buffer()
        {
            if (m_buffer)
            {
                alDeleteBuffers(1, &m_buffer);
            }
        }

        bool Buffer::Initialize()
        {
            alGetError();   //Clear error
            alGenBuffers(1, &m_buffer);
            return alGetError() == AL_NO_ERROR;
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
            return alGetError() == AL_NO_ERROR;
        }

        ALuint& Buffer::GetBuffer()
        {
            return m_buffer;
        }
    }
}
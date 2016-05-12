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

#include <ht_audiodevice.h>

namespace Hatchit
{
    namespace Audio
    {
        Device::Device()
            : m_instance(nullptr),
            m_context(nullptr)
        {
        }
        
        Device::~Device()
        {
            if (m_context)
            {
                alcDestroyContext(m_context);
            }
            if (m_instance)
            {
                alcCloseDevice(m_instance);
            }
        }
        
        bool Device::Initialize()
        {
            auto deviceName = alcGetString(nullptr, ALC_DEFAULT_DEVICE_SPECIFIER);
            m_instance = alcOpenDevice(deviceName);
            if (!m_instance)
                return false;
            m_context = alcCreateContext(m_instance, nullptr);
            return alcGetError(m_instance) == ALC_NO_ERROR;
        }
        
        void Device::MakeContextCurrent()
        {
            alcMakeContextCurrent(m_context);
        }
        
        void Device::ProcessContext()
        {
            alcProcessContext(m_context);
        }
        
        void Device::SuspendContext()
        {
            alcSuspendContext(m_context);
        }
        
        const ALCdevice* Device::GetDevice() const
        {
            return m_instance;
        }
        
        ALCdevice* Device::GetDevice()
        {
            return m_instance;
        }
        
        const ALCcontext* Device::GetContext() const
        {
            return m_context;
        }
        
        ALCcontext* Device::GetContext()
        {
            return m_context;
        }
    }
}
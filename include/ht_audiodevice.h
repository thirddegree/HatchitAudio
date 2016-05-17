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
#include <AL/alc.h> //ALCdevice, ALCcontext

namespace Hatchit
{
    namespace Audio
    {
        class HT_API Device
        {
        public:
            Device();
            ~Device();
            
            bool Initialize();
            
            void MakeContextCurrent();
            void ProcessContext();
            void SuspendContext();
            
            const ALCdevice* GetDevice() const;
            ALCdevice* GetDevice();
            const ALCcontext* GetContext() const;
            ALCcontext* GetContext();

        private:
            ALCdevice* m_instance;
            ALCcontext* m_context;
        };
    }
}
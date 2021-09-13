/*
  Copyright (C) 2021 hidenorly

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Device.hpp"

Device::Device(audio_module_handle_t hwModule, std::string filterPlugInPath) : IDevice(hwModule, filterPlugInPath)
{
  mStreamManager = StreamManager::getInstance().lock();
}

Device::~Device()
{

}


HalResult Device::initCheck(void)
{
  return mStreamManager ? HalResult::OK : NOT_INITIALIZED;
}

HalResult Device::close(void)
{
  mStreamManager.reset();
  return HalResult::OK;
}


HalResult Device::openOutputStream(AudioIoHandle ioHandle, DeviceAddress device, audio_config config, audio_output_flags_t flags, SourceMetadata sourceMetadata, std::shared_ptr<IStreamOut>& pOutStream, audio_config& outSuggestedConfig)
{
  if( mStreamManager ){
    std::shared_ptr<StreamOutContext> pContext = std::make_shared<StreamOutContext>(ioHandle, device, config, flags, sourceMetadata);
    std::shared_ptr<IPipe> pPipe = std::make_shared<Pipe>();

    mStreamManager->add( pContext, pPipe );
  }

  return mStreamManager ? HalResult::OK : NOT_INITIALIZED;
}

std::vector<ParameterValue> Device::getParameters(std::vector<std::string> keys)
{
  return std::vector<ParameterValue>();
}

HalResult Device::setParameters(std::vector<ParameterValue> parameters)
{
  return HalResult::NOT_SUPPORTED;
}


bool Device::supportsAudioPatches(void)
{
  return true;
}

audio_patch_handle_t Device::createAudioPatch(std::vector<audio_port_config> sources, std::vector<audio_port_config> sinks)
{
  return 0;
}

audio_patch_handle_t Device::updateAudioPatch(audio_patch_handle_t previousPatch, std::vector<audio_port_config> sources, std::vector<audio_port_config> sinks)
{
  return 0;
}

HalResult Device::releaseAudioPatch(audio_patch_handle_t patch)
{
  return HalResult::NOT_SUPPORTED;
}


HalResult Device::addDeviceEffect(audio_port_handle_t device, uint64_t effectId)
{
  return HalResult::NOT_SUPPORTED;
}

HalResult Device::removeDeviceEffect(audio_port_handle_t device, uint64_t effectId)
{
  return HalResult::NOT_SUPPORTED;
}


HalResult Device::setMasterVolume(float volume)
{
  return HalResult::NOT_SUPPORTED;
}

float Device::getMasterVolume(void)
{
  return 0.0f;
}

HalResult Device::setMasterMute(bool mute)
{
  return HalResult::NOT_SUPPORTED;
}

bool Device::getMasterMute(void)
{
  return false;
}


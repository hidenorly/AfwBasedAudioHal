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

#ifndef __ANDROID_AUDIO_HAL_DEVICE_HPP__
#define __ANDROID_AUDIO_HAL_DEVICE_HPP__


#include "AndroidHalDevice.hpp"
#include "StreamManager.hpp"
#include <memory>


class Device : public IDevice
{
protected:
  std::shared_ptr<StreamManager> mStreamManager;

public:
  Device();
  virtual ~Device();

  virtual HalResult initCheck(void);
  virtual HalResult close(void);

  virtual HalResult openOutputStream(AudioIoHandle ioHandle, DeviceAddress device, audio_config config, audio_output_flags_t flags, SourceMetadata sourceMetadata, std::shared_ptr<IStreamOut>& pOutStream, audio_config& outSuggestedConfig);

  virtual std::vector<ParameterValue> getParameters(std::vector<std::string> keys);
  virtual HalResult setParameters(std::vector<ParameterValue> parameters);

  virtual bool supportsAudioPatches(void);
  virtual audio_patch_handle_t createAudioPatch(std::vector<audio_port_config> sources, std::vector<audio_port_config> sinks);
  virtual audio_patch_handle_t updateAudioPatch(audio_patch_handle_t previousPatch, std::vector<audio_port_config> sources, std::vector<audio_port_config> sinks);
  virtual HalResult releaseAudioPatch(audio_patch_handle_t patch);

  virtual HalResult addDeviceEffect(audio_port_handle_t device, uint64_t effectId);
  virtual HalResult removeDeviceEffect(audio_port_handle_t device, uint64_t effectId);

  virtual HalResult setMasterVolume(float volume);
  virtual float getMasterVolume(void);
  virtual HalResult setMasterMute(bool mute);
  virtual bool getMasterMute(void);
};

#endif /* __ANDROID_AUDIO_HAL_DEVICE_HPP__ */

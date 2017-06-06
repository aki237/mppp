// Copyright (C) 2017 Akilan Elango <akilan1997@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#include <iostream>
#include "Device.hpp"

Device* Device::dev = nullptr;

Device* Device::getInstance() {

  if (dev != nullptr) {
    return dev;
  }
  dev = new Device;
  PaStreamParameters oparams;
  oparams.device = Pa_GetDefaultOutputDevice(); /* default output device */
  oparams.channelCount = 2; // cbc
  oparams.sampleFormat = paInt16;
  oparams.suggestedLatency = Pa_GetDeviceInfo( oparams.device )->defaultHighOutputLatency;
  oparams.hostApiSpecificStreamInfo = NULL;
  // Set up PortAudio 16-bit 44.1kHz stereo output
  PaError err = Pa_OpenStream(&(dev->stream),
                              nullptr,
                              &oparams,
                              44100, // cbc
                              0, // cbc
                              paClipOff,
                              nullptr,
                              nullptr
                              );
  if( err != paNoError ){
    std::cout << "Some Error In opening the device : " << Pa_GetErrorText(err) << std::endl;
    return nullptr;
  }
  err = Pa_StartStream( dev->stream );
  if( err != paNoError ) {
    std::cout << "Some Error In starting the stream : " << Pa_GetErrorText(err) << std::endl;
    return nullptr;
  }
  return dev;
}

void Device::closeInstance() {
  std::cout << "Killing the instance" << std::endl;
  Device* d = getInstance();
  PaError err = Pa_StopStream( d->stream );
  if( err != paNoError ) {
    std::cout << "Some Error in stopping the stream : " << Pa_GetErrorText(err) << std::endl;
    return;
  }
  err = Pa_CloseStream( d->stream );
  if( err != paNoError ) {
    std::cout << "Some Error In closing the device : " << Pa_GetErrorText(err) << std::endl;
    return;
  }
  err = Pa_Terminate();
  if( err != paNoError ) {
    std::cout << "Some Error In closing the device : " << Pa_GetErrorText(err) << std::endl;
    return;
  }
}

bool Device::write(void* buffer, unsigned long samples) {
  if (dev == nullptr) {
    dev = getInstance();
  }
  PaError err = Pa_WriteStream(dev->stream, buffer, samples);
  if (err != paNoError) {
    std::cout << "Some Error while playing : " << Pa_GetErrorText(err) << std::endl;
    return false;
  }
  return true;
}

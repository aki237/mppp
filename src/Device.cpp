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

Device::Device() {
  PaError err = Pa_Initialize();
  if( err != paNoError ) {
    std::cout << "Some Error In initializing portaudio : " << Pa_GetErrorText(err) << std::endl;
    return;
  }
  PaStreamParameters oparams;
  oparams.device = Pa_GetDefaultOutputDevice(); /* default output device */
  oparams.channelCount = 2; // cbc
  oparams.sampleFormat = paInt16;
  oparams.suggestedLatency = Pa_GetDeviceInfo( oparams.device )->defaultHighOutputLatency;
  oparams.hostApiSpecificStreamInfo = NULL;
  // Set up PortAudio 16-bit 44.1kHz stereo output
  err = Pa_OpenStream(&(stream),
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
  }
  err = Pa_StartStream( stream );
  if( err != paNoError ) {
    std::cout << "Some Error In starting the stream : " << Pa_GetErrorText(err) << std::endl;
  }
}

bool Device::write(void* buffer, unsigned long samples) {
  PaError err = Pa_WriteStream(stream, buffer, samples);
  if (err != paNoError) {
    std::cout << "Some Error while playing : " << Pa_GetErrorText(err) << std::endl;
    return false;
  }
  return true;
}

Device::~Device() {
  std::cout << "Killing the instance" << std::endl;
  PaError err = Pa_StopStream( stream );
  if( err != paNoError ) {
    std::cout << "Some Error in stopping the stream : " << Pa_GetErrorText(err) << std::endl;
    return;
  }
  err = Pa_CloseStream( stream );
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

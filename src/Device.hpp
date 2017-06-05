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
#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <portaudio.h>

class Device {
private:
  static Device* dev;
  PaStream* stream;
  Device(){
    PaError err = Pa_Initialize();
    if( err != paNoError ) {
      std::cout << "Some Error In initializing portaudio : " << Pa_GetErrorText(err) << std::endl;
      return;
    }
  }
public:
  static Device* getInstance();
  static void closeInstance();
  static bool write(void*, unsigned long);
};
#endif // DEVICE_HPP

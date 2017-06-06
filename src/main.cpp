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
#include <stdio.h>
#include <thread>
#include "Device.hpp"
#include "MPEGCodec.hpp"
#include "Codec.hpp"
#include "Duration.hpp"

void PrintDuration(MPEGCodec* mpgh) {
  //MPEGCodec* mpgh = (MPEGCodec*) mpg;
  while (mpgh->ended()) {
    Duration d;
    d << mpgh->getElapsed();
    std::string sep = ":";
    if (d.getSeconds() < 10){
      sep = ":0";
    }
    std::cout << "\rElapsed : " << d.getMinutes() << sep << d.getSeconds() << std::flush;
  }
  std::cout << std::endl;
  pthread_exit(nullptr);
}

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [filename.mp3]" << std::endl;
    return 255;
  }
  std::cout << "MP3 Player" << std::endl;
  Device* dev = Device::getInstance();
  std::string filename = std::string(argv[1]);
  MPEGCodec mpg(filename);
  PCMData pdata;
  std::thread thread (PrintDuration, &mpg);
  while(mpg.getFrame(&pdata)) {
    if (pdata.data == nullptr) {
      std::cerr << "Corrupt data" << std::endl;
      break;
    }
    dev->write(pdata.data, pdata.len);
  }

  thread.join();
  dev->closeInstance();

  return EXIT_SUCCESS;
}

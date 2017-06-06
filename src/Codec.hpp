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
#ifndef CODEC_HPP
#define CODEC_HPP

#include <iostream>

typedef struct {
  unsigned char* data;
  long len;
  long duration;
} PCMData;

class Codec {
public:
  Codec(std::string r_name) : _name(r_name) {}

  void printInfo() {
    std::cout << "Codec Name : " << _name << std::endl;
  }

  // interface virtual functions
  virtual bool getFrame(PCMData*) = 0;
  virtual float getElapsed() = 0;
  virtual float getDuration() = 0;
  virtual bool  ended() = 0;
protected:
  std::string _name;
};
#endif // CODEC_HPP

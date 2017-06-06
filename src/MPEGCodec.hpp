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
#ifndef MPEDCODEC_HPP
#define MPEDCODEC_HPP

#include "Codec.hpp"
#include <iostream>
#include <mpg123.h>

class MPEGCodec : public Codec {
private:
  mpg123_handle* _mh;
  unsigned char* _buffer;
  unsigned int _counter;
  size_t _buffer_size;
  size_t _done;
  bool _is_not_done;
  long _srate;
  float _elapsed;
  std::string _filename;
public:
  MPEGCodec(std::string);
  MPEGCodec();
  ~MPEGCodec();
  bool getFrame(PCMData*);
  float getElapsed();
  float getDuration();
  bool ended();
  void open(std::string);
};

#endif // MPEDCODEC_HPP

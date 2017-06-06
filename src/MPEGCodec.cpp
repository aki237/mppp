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
#include "MPEGCodec.hpp"
#include <cstring>

MPEGCodec::MPEGCodec(std::string filename) : _filename(filename),
                                             Codec("mpg123"){
  mpg123_init();
  open(filename);
}

MPEGCodec::MPEGCodec() : Codec("mpg123") {
  mpg123_init();
}

bool MPEGCodec::getFrame(PCMData* d) {
  if (_mh == nullptr) {
    return false;
  }
  int out = mpg123_read(_mh, _buffer, _buffer_size, &_done);
  _is_not_done = (out == MPG123_OK);
  d->data = (unsigned char*)malloc(_buffer_size * sizeof(unsigned char));
  std::memcpy(d->data, _buffer, _buffer_size * sizeof(unsigned char));
  d->len = _done/4;
  d->duration = 0;
  _elapsed += (_done/4)/(float)_srate;
  return _is_not_done;
}

float MPEGCodec::getElapsed() {
  return _elapsed;
}

float MPEGCodec::getDuration() {
  return (float) mpg123_tpf(_mh);
}

bool MPEGCodec::ended() {
  return _is_not_done;
}

void MPEGCodec::open(std::string filename) {
  _filename = filename;
  int err;
  _mh =mpg123_new(NULL, &err);
  _buffer_size = mpg123_outblock(_mh);
  _buffer = (unsigned char*)malloc(_buffer_size * sizeof(unsigned char));
  if (mpg123_open(_mh, _filename.c_str()) != MPG123_OK) {
    std::cerr << "Unable to open the file : "  << _filename << std::endl;
    return;
  }
  int channels, encoding;
  mpg123_getformat(_mh, &_srate, &channels, &encoding);
  _counter = 0;
  _is_not_done = true;
  _elapsed = 0;
}

MPEGCodec::~MPEGCodec() {
  free(_buffer);
  mpg123_close(_mh);
  mpg123_delete(_mh);
  mpg123_exit();
}

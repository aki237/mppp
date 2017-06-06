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
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Device.hpp"
#include "MPEGCodec.hpp"

class Player{
private:
  Device _dev;
  MPEGCodec _codec;
  bool _playing;
public:
  Player(std::string);
  Player();
  void start();
  void play();
  void load(std::string);
  void pause();
  ~Player();
};

#endif // PLAYER_HPP

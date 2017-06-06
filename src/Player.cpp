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
#include "Player.hpp"
#include "Codec.hpp"

Player::Player(std::string filename) : _codec(filename), _playing(false) {
  load(filename);
}

Player::Player() : _playing(false) {}

void Player::start() {
  PCMData pdata;
  _playing = true;
  while(_codec.getFrame(&pdata)) {
    if (pdata.data == nullptr) {
      std::cerr << "Corrupt data" << std::endl;
      break;
    }
    while(!_playing) {}
    _dev.write(pdata.data, pdata.len);
  }
  _playing = false;
}

void Player::play() {
  _playing = true;
}

void Player::load(std::string filename) {
  std::cout << filename << std::endl;
  _codec.open(filename);
}

void Player::pause() {
  _playing = false;
}

Player::~Player() {}

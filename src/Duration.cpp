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
#include "Duration.hpp"


Duration::Duration(float seconds) {
  _minutes = 0;
  _seconds = 0;
  parse(seconds);
}

Duration::Duration() {
  _minutes = 0;
  _seconds = 0;
}

void Duration::parse(float seconds) {
  if (seconds < 0) {
    return;
  }
  _minutes = (int)seconds / (int)60;
  _seconds = (int)seconds - (_minutes*60);
}

Duration Duration::operator+(const Duration&d) {
  Duration nd;
  nd._minutes = (uint)_minutes + d._minutes;
  nd._seconds = (uint)_seconds + d._seconds;
  return nd;
}

void Duration::operator<<(float seconds) {
  int mins = _minutes;
  int secs = _seconds;
  parse(seconds);
  _minutes += mins;
  _seconds += secs;
}

int Duration::getMinutes() {
  return _minutes;
}

int Duration::getSeconds() {
  return _seconds;
}

void Duration::setMinutes(uint minutes) {
  _minutes = (int)minutes;
}

void Duration::setSeconds(uint seconds) {
  _seconds = (int)seconds;
}

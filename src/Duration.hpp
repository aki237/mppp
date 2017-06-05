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
#ifndef DURATION_HPP
#define DURATION_HPP
#include <iostream>

class Duration {
private:
  int _minutes, _seconds;
  void parse(float);
public:
  Duration ();
  Duration (float);
  Duration operator+(const Duration&d) ;
  void operator<<(float);
  int getMinutes();
  int getSeconds();
  void setMinutes(uint);
  void setSeconds(uint);
};

#endif // DURATION_HPP

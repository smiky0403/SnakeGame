//Mingqi:Shared pointer implementation for toxic food
//note this section of code, I took reference from author pukkinming on its structure, modified based on my own need
#ifndef TOXIC_H
#define TOXIC_H

#include <memory>
#include <vector>
#include "toxic.h"
#include <iostream>

struct Coord{
 public:
    Coord(const int x, const int y)
        : _x(x), _y(y) {}

    int getX() const { return _x; }
    int getY() const { return _y; }

    // Overload operator ==
    bool operator==(const Coord &coord) const {
        return (_x == coord._x && _y == coord._y);
    }

 private:
    int _x, _y;
};


class ToxicFood {
 public:
  // Constructor
  ToxicFood();
  // Destructor
  ~ToxicFood();

  void addCoord(const Coord &&coord);
  bool Cell(const Coord &&coord);

  int size() const;
  const std::vector<Coord> &getCoord() const;

  std::unique_ptr<std::vector<Coord>> _coords;

  private:
};


#endif 
//Mingqi:Shared pointer implementation for toxic foods,
//note this section of code, I took reference from author pukkinming on its structure, modified based on my own need
#include <memory>

#include "toxic.h"


ToxicFood::ToxicFood() {
    _coords = std::unique_ptr<std::vector<Coord>>(new std::vector<Coord>);
}

ToxicFood::~ToxicFood(){};

void ToxicFood::addCoord(const Coord &&coord) {
    _coords->emplace_back(coord);
}

bool ToxicFood::Cell(const Coord &&coord) {
    for (const Coord &_coord : *_coords) {
        if (_coord == coord) {
            return true;
            break;
        }
    }
    return false;
}

const std::vector<Coord> &ToxicFood::getCoord() const {
    return *_coords;
}

int ToxicFood::size() const {
    return _coords->size();
}



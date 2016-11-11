#include <cassert>
#include <cmath>
#include "geometry.h"

#ifndef NDEBUG
#include <iostream>
const bool DEBUG = true;
#else
const bool DEBUG = false;
#endif

/* POSITION */

/* Position - punkt (pozycja) na płaszczyźnie. */

/* Position można stworzyć, przekazując współrzędne, np. Position(100, 200). Nie
powinno być możliwe skonstruowanie obiektu Position bez podawania argumentów
(t.j.  Position()). */
Position::Position(const int xx, const int yy)
  : coorX(xx)
  , coorY(yy) {
  if(DEBUG) std::cerr << "Position constructor\n";
};

// copy constructor
Position::Position(const Position& that)
: coorX( that.coorX )
, coorY( that.coorY ) {}

// move constructor
Position::Position(Position&& that)
: coorX( that.coorX )
, coorY( that.coorY ) {}

/* Position ma metody x() i y(), które wyciągają odpowiednie współrzędne. */
int Position::x() const { return coorX; };
int Position::y() const { return coorY; };

/* Position ma metodę reflection(), która zwraca pozycję odbitą względem osi x = y. */
Position Position::reflection() const {
  if(DEBUG) std::cerr << "Position reflection\n";
  return Position(coorY, coorX);
};

Position& Position::operator=(const Position& that) { //copy & move operator
  coorX = that.coorX;
  coorX = that.coorY;
  return *this;
}

inline bool Position::operator==(const Position& rhs) {
  return coorX==rhs.x() && coorY==rhs.y();
};

Position& Position::operator+=(const Vector& vec) {
  coorX += vec.x();
  coorY += vec.y();
  return *this;
};

Position const& Position::origin() {
  static const Position posOrigin = Position(0,0);
  return posOrigin;
};

/* VECTOR */

Vector::Vector(const int xx, const int yy)
  : coorX(xx)
  , coorY(yy) {
  if(DEBUG) std::cerr << "Vector constructor\n";
};

int Vector::x() const { return coorX; };
int Vector::y() const { return coorY; };

Vector Vector::reflection() const {
  if(DEBUG) std::cerr << "Vector reflection\n";
  return Vector(this->coorY, this->coorX);
};

inline bool Vector::operator==(const Vector& rhs) {
  return coorX == rhs.coorX && coorY == rhs.coorY;
};

Vector& Vector::operator+=(const Vector& vec) {
  coorX += vec.coorX;
  coorY += vec.coorY;
  return *this;
};


/* RECTANGLE */

Rectangle::Rectangle(int width, int height, const Position& pos)
  : diag(width, height)
  , bottomLeft(pos) {
    assert(width > 0 && height > 0);
  };

Rectangle::Rectangle(int width, int height, Position&& pos)
  : diag(width, height)
  , bottomLeft(std::move(pos)) {
    assert(width > 0 && height > 0);
  };

Rectangle::Rectangle(int width, int height)
  : diag(width, height)
  , bottomLeft(Position::origin()) {
    assert(width > 0 && height > 0);
  };

Rectangle::Rectangle(const Position& pos, const Vector& diagonal)
  : diag(diagonal)
  , bottomLeft(pos) {
    assert(diagonal.x() > 0 && diagonal.y() > 0);
  };

Rectangle::Rectangle(const Rectangle& that) // copy constructor
  : diag(that.diag)
  , bottomLeft(that.bottomLeft) {};

Rectangle::Rectangle(Rectangle&& that) // move constructor
  : diag(std::move(that.diag))
  , bottomLeft(std::move(that.bottomLeft)) {};

int Rectangle::width() const { return this->diag.x(); };
int Rectangle::height() const { return this->diag.y(); };
Position Rectangle::pos() const { return this->bottomLeft; };

Rectangle& Rectangle::operator=(const Rectangle& that) { /* Copy assignment operator */
  this->diag = that.diag;
  this->bottomLeft = that.bottomLeft;
  return *this;
}

Rectangle& Rectangle::operator=(Rectangle&& that) { /* Move assignment operator */
  this->diag = std::move(that.diag);
  this->bottomLeft = std::move(that.bottomLeft);
  return *this;
}

inline bool Rectangle::operator==(const Rectangle& that) {
  return this->diag == that.diag &&
         this->bottomLeft == that.bottomLeft;
}

Rectangle& Rectangle::operator+=(const Vector& vec) {
  this->diag += vec;
  return *this;
};

Rectangle Rectangle::reflection() const {
  const Vector &diagReflected = this->diag.reflection();
  const Position &posReflected = this->bottomLeft.reflection();
  return Rectangle(abs(diagReflected.x()), abs(diagReflected.y()),
    Position(posReflected.x() + (diagReflected.x() < 0) * diagReflected.x(),
             posReflected.y() + (diagReflected.y() < 0) * diagReflected.y()));
};

int Rectangle::area() const {
  return this->width() * this->height();
};

typedef std::pair<Rectangle, Rectangle> rectanglePair;

rectanglePair Rectangle::split_horizontally(int place) {
  assert(place <= this->height());
  assert(place >= 0);
  return rectanglePair(Rectangle(this->width(), place, this->bottomLeft),
                       Rectangle(this->width(), this->height()-place, this->bottomLeft));
};

rectanglePair Rectangle::split_vertically(int place) {
  assert(place < this->width());
  assert(place > 0);
  return rectanglePair(Rectangle(place, this->height(), this->bottomLeft),
                       Rectangle(this->width()-place, this->height()-place, this->bottomLeft));
};


//DEBUG DO TESTÓW
int main() {
  Position a = Position(0,0), b = Position::origin();
  assert(a==b);
  Position c = a.reflection();
  assert(a.x() == c.y() && a.y() == c.x());
  c = b.reflection();
  if(DEBUG) std::cerr << "Done :)\n";
  return 0;
}

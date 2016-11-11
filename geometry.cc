#include <cassert>
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
Position::Position(const int xx, const int yy) : coorX(xx), coorY(yy) {
  if(DEBUG) std::cerr << "Position constructor\n";
};

/* Position ma metody x() i y(), które wyciągają odpowiednie współrzędne. */
int Position::x() const { return coorX; };
int Position::y() const { return coorY; };

/* Position ma metodę reflection(), która zwraca pozycję odbitą względem osi x = y. */
Position Position::reflection() const {
  if(DEBUG) std::cerr << "Position reflection\n";
  return Position(coorY, coorX);
};

/* Position można porównywać za pomocą operatora ==. */
inline bool Position::operator==(const Position& rhs) { return coorX==rhs.x() && coorY==rhs.y(); };

/* Position implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator
powinien zwrócić referencję do wołanego obiektu*/
Position& Position::operator+=(const Vector& vec) {
  coorX += vec.x();
  coorY += vec.y();
  return *this;
};

/* Position implementuje statyczną metodę origin(), która zwraca
niemodyfikowalny obiekt Position(0, 0). */
Position const& Position::origin() {
  static const Position posOrigin = Position(0,0);
  return posOrigin;
};

/* VECTOR */

/* Vector - wektor na płaszczyźnie. */
Vector::Vector(const int xx, const int yy) : coorX(xx), coorY(yy) {
  if(DEBUG) std::cerr << "Vector constructor\n";
};

/* Vector ma metody x() i y(), które wyciągają odpowiednie współrzędne. */
int Vector::x() const { return coorX; };
int Vector::y() const { return coorY; };

/* Vector ma metodę reflection(), która zwraca pozycję odbitą względem osi x = y. */
Vector Vector::reflection() const {
  if(DEBUG) std::cerr << "Vector reflection\n";
  return Vector(coorY, coorX);
};

/* Vector można porównywać za pomocą operatora ==. */
inline bool Vector::operator==(const Vector& rhs) { return coorX==rhs.x() && coorY==rhs.y(); };

/* Vector implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator
powinien zwrócić referencję do wołanego obiektu*/
Vector& Vector::operator+=(const Vector& vec) {
  coorX += vec.x();
  coorY += vec.y();
  return *this;
};


/* RECTANGLE */

/* Rectangle można stworzyć, przekazując jego rozmiar i pozycję lewego dolnego
rogu: Rectangle(width, height, pos) lub Rectangle(width, height) - wtedy
pozycja jest ustalona na (0, 0). Nie powinno być możliwe skonstruowanie
obiektu Rectangle bez podawania argumentów (t.j.Rectangle()). */
Rectangle::Rectangle(int width, int height, const Position& pos) : diag(Vector(width,height)), bottomLeft(pos) {};
Rectangle::Rectangle(int width, int height) : diag(Vector(width,height)), bottomLeft(Position::origin()) {};
Rectangle::Rectangle(const Vector& diagonal, const Position& pos) : diag(diagonal), bottomLeft(pos) {};

/* Rectangle ma metody width(),  height() i pos(), które wyciągają odpowiednie
współrzędne i pozycję lewego dolnego rogu. */
int Rectangle::width() const { return diag.x(); };
int Rectangle::height() const { return diag.y(); };
Position Rectangle::pos() const { return bottomLeft; };

/* Rectangle ma metodę reflection(), która zwraca prostokąt odbity względem osi x = y. */
Rectangle Rectangle::reflection() const {
  return Rectangle(diag.reflection(), bottomLeft.reflection());
};

/* Rectangle można porównywać za pomocą operatora ==. */
inline bool Rectangle::operator==(const Rectangle& rhs) {
  return this->width() == rhs.width() && this->height() == rhs.height() && this->pos() == rhs.pos();
}

/* Rectangle implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator
powinien zwrócić referencję do wołanego obiektu. */
Rectangle& Rectangle::operator+=(const Vector& vec) {
  this->pos() += vec;
  return *this;
};

/* Rectangle implementuje metodę area(), która wylicza jego pole powierzchni. */
int Rectangle::area() const { return this->width()*this->height(); };

/* Rectangle implementuje metodę split_horizontally(place), która zwraca
parę prostokątów powstałą z rozcięcia prostokąta wzdłuż osi X, tak że
pierwszy prostokąt ma wysokość place, np. prostokąt Rectangle(100, 200)
rozcięty z wartością place = 20 da nam dwa prostokąty:
 * pierwszy o lewym dolnym rogu (0, 0), szerokości 100 i wysokości 20,
 * drugi o lewym dolnym rogu (0, 20), szerokości 100 i  wysokości 180. */
// std::pair<Rectangle, Rectangle> Rectangle::split_horizontally(int place);

/* Rectangle implementuje metodę split_vertically(place) działającą
analogicznie do split_horizontally(). */
// std::pair<Rectangle, Rectangle> Rectangle::split_vertically(int place);





int main() {
  Position a = Position(0,0), b = Position::origin();
  assert(a==b);
  Position c = a.reflection();
  assert(a.x() == c.y() && a.y() == c.x());
  c = b.reflection();
  if(DEBUG) std::cerr << "Done :)\n";
  return 0;
}

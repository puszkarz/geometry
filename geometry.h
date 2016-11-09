#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <utility>

class Position;
class Vector;
class Rectangle;
class Rectangles;


/* Position - punkt (pozycja) na płaszczyźnie. */
class Position {
  /* Współrzędne na płaszczyźnie. */
  int posX, posY;

public:
  /* Position można stworzyć, przekazując współrzędne, np. Position(100, 200). Nie
  powinno być możliwe skonstruowanie obiektu Position bez podawania argumentów
  (t.j.  Position()). */
  Position(int xx, int yy);

  /* Position ma metody x() i y(), które wyciągają odpowiednie współrzędne. */
  int x();
  int y();

  /* Position ma metodę reflection(), która zwraca pozycję odbitą względem osi x = y. */
  Position reflection();

  /* Position można porównywać za pomocą operatora ==. */
  inline bool operator==(const Position& rhs);

  /* Position implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator */
  Position& operator+=(const Vector& vec);

  /* Position implementuje statyczną metodę origin(), która zwraca
  niemodyfikowalny obiekt Position(0, 0). */
  static Position const& origin();
};


/* Vector - wektor na płaszczyźnie. */
class Vector {
  /* Współrzędne wektora. */
  int vecX, vecY;

public:
  /* Vector można stworzyć, przekazując współrzędne, np. Vector(100, 200). Nie
  powinno być możliwe skonstruowanie obiektu Vector bez podawania argumentów
  (t.j.  Vector()). */
  Vector(int xx, int yy);

  /* Vector ma metody x() i y(), które wyciągają odpowiednie współrzędne. */
  int x();
  int y();

  /* Vector ma metodę reflection(), która zwraca wektor odbity względem osi x = y. */
  Vector reflection();

  /* Vector można porównywać za pomocą operatora ==. */
  inline bool operator==(const Vector& rhs);

  /* Vector implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator
  powinien zwrócić referencję do wołanego obiektu. */
  Vector& operator+=(const Vector& vec);

};

/* Rectangle  - prostokąt. */
class Rectangle {
  /* Lewy dolny róg prostokąta */
  Position bottomLeft;

  /* Przekątna prostokątna wychodząca z lewego dolnego rogu. */
  Vector diag;

public:
  /* Rectangle można stworzyć, przekazując jego rozmiar i pozycję lewego dolnego
  rogu: Rectangle(width, height, pos) lub Rectangle(width, height) - wtedy
  pozycja jest ustalona na (0, 0). Nie powinno być możliwe skonstruowanie
  obiektu Rectangle bez podawania argumentów (t.j.Rectangle()). */
  Rectangle(int width, int height, int pos);
  Rectangle(int width, int height);

  /* Rectangle ma metody width(),  height() i pos(), które wyciągają odpowiednie
  współrzędne i pozycję lewego dolnego rogu. */
  int width();
  int height();
  Position pos();

  /* Rectangle ma metodę reflection(), która zwraca prostokąt odbity względem osi x = y. */
  Rectangle reflection();

  /* Rectangle można porównywać za pomocą operatora ==. */
  inline bool operator==(const Rectangle& rhs);

  /* Rectangle implementuje operator "+=(vec)", gdzie vec jest wektorem. Operator
  powinien zwrócić referencję do wołanego obiektu. */
  Rectangle& operator+=(const Vector& vec);

  /* Rectangle implementuje metodę area(), która wylicza jego pole powierzchni. */
  int area();

  /* Rectangle implementuje metodę split_horizontally(place), która zwraca
  parę prostokątów powstałą z rozcięcia prostokąta wzdłuż osi X, tak że
  pierwszy prostokąt ma wysokość place, np. prostokąt Rectangle(100, 200)
  rozcięty z wartością place = 20 da nam dwa prostokąty:
   * pierwszy o lewym dolnym rogu (0, 0), szerokości 100 i wysokości 20,
   * drugi o lewym dolnym rogu (0, 20), szerokości 100 i  wysokości 180. */
  std::pair<Rectangle, Rectangle> split_horizontally(int place);

  /* Rectangle implementuje metodę split_vertically(place) działającą
  analogicznie do split_horizontally(). */
  std::pair<Rectangle, Rectangle> split_vertically(int place);

};

/* Rectangles - kolekcja prostokątów. */
class Rectangles {
  public:
};

/* Dodatkowo powinny być możliwe są następujące operacje arytmetyczne:
  Position = Position + Vector
  Position = Vector + Position
  Vector = Vector + Vector
  Rectangle = Rectangle + Vector
  Rectangle = Vector + Rectangle
  Rectangles = Rectangles + Vector
  Rectangles = Vector + Rectangles
z naturalną semantyką. Jeżeli jeden z argumentów jest przekazany przez r-value,
należy wykorzystać przekazaną pamięć zaalokowaną dynamicznie do stworzenia
obiektu wynikowego.*/
Position& operator+(const Position& pos, const Vector& vec);
Position& operator+(const Vector& vec, const Position& pos);
Vector& operator+(const Vector& vec1, const Vector& vec2);
Rectangle& operator+(const Rectangle& rec, const Vector& vec);
Rectangle& operator+(const Vector& vec, const Rectangle& rec);
Rectangles& operator+(const Rectangles& recs, const Vector& vec);
Rectangles& operator+(const Vector& vec, const Rectangles& recs);

/* Operacje merge_horizontally(rect1, rect2) i merge_vertically(rect1, rect2)
łączą dwa prostokąty odpowiednio wzdłuż osi X i Y. Przykładowo
merge_horizontally łączy dwa prostokąty ze wspólną krawędzią (górną krawędzią
pierwszego prostokąta i dolną krawędzią drugiego prostokąta). Jeżeli dało się
skleić dwa prostokąty r1 i r2, to odpowiednia operacja split na wynikowym
prostokącie powinna dać z powrotem r1 i r2. */
Rectangle merge_horizontally(Rectangle rect1, Rectangle rect2);
Rectangle merge_vertically(Rectangle rect1, Rectangle rect2);

#endif // GEOMETRY_H

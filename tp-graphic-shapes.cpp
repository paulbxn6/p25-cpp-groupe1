/* implement graphic shapes and an editor

the graphic shapes:
     - are Circle (radius), Rectangle (width, height) ...
     - have a position: x, y
     - can be moved
     - have member function that check if a shape is at a given position
     (juste check that the given point is inside the smallest rectangular bounding box englobing the shape)
     - have a member function that compute the area of the shape (fix a value for PI)

the editor:
  - contains a list of graphic shapes
  - can add/remove an existing graphic-shape to the list
  - has a member function find that returns the (first) graphic shape at a given position
  - can remove the graphic-shape found at a given position
  - can compute the area of the shape found at a given position

We can add a new shape to your code (Square) WITHOUT modifying your classes !
Only by adding some code and modifying the main function.

*/

#include <iostream>
#include <vector>

class Shape {
  int x;
  int y;
protected:
  Shape(int posx, int posy) : x(posx), y(posy) {};
public:
  void move(int dx, int dy) {
    x = x + dx;
    y = y + dy;
  }
  virtual double area() = 0;
};

class Circle : public Shape {
  double radius;
public:
  Circle(int x, int y, double r) : Shape(x, y), radius(r) {};
  double area() {
    return 3.14159 * radius * radius;
  }
};

class Rectangle : public Shape {
public :
  double width; double height;
  Rectangle(int x, int y, double w, double h) : Shape(x, y), width(w), height(h) {};
  double area() {
    return width * height;
  }
};


int main()
{
    Circle c1(100, 50, 12.4);
    c1.move(15, 67);
    std::cout << c1.area() << std::endl;

    Circle c2(30, 120, 45.89);

    Rectangle r1(30, 40, 60, 50);
    std::cout << r1.area() << std::endl;

    Rectangle r2(70, 80, 100, 67);

    std::vector<Shape*> shapes;
    shapes.push_back(&c1);
    shapes.push_back(&r1);

    for (int i = 0; i < shapes.size(); i++) {
      std::cout << shapes[i]->area() << std::endl;
    }
    // Editor ed;
    // ed.add(c1);
    // ed.add(c2);
    // ed.add(r1);
    // ed.add(r2);

    // ed.find(71, 81).area();
    // ed.find(30, 120).move(10, 80);

    return 0;
}
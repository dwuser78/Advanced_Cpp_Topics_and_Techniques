#define _USE_MATH_DEFINES

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

typedef enum {
    CIRCLE,
    SQUARE,
    TRIANGLE,
    RECTANGLE,
    ALL_SHAPES
} shapes;

typedef enum {
    WHITE,
    BLACK,
    RED,
    BLUE,
    GREEN,
    YELLOW,
    ALL_COLORS
} colors;

const static struct {
    shapes      val;
    const char *str;
} shapes_enum_conv [] = {
    {CIRCLE, "circle"},
    {SQUARE, "square"},
    {TRIANGLE, "triangle"},
    {RECTANGLE, "rectangle"}
};

const static struct {
    colors      val;
    const char *str;
} colors_enum_conv [] = {
    {WHITE, "white"},
    {BLACK, "black"},
    {RED, "red"},
    {BLUE, "blue"},
    {GREEN, "green"},
    {YELLOW, "yellow"}
};

shapes str2shape (const string *str)
{
    for (int i = 0; i < ALL_SHAPES; ++i)
        if (*str == shapes_enum_conv[i].str)
            return shapes_enum_conv[i].val;

    throw invalid_argument("Such shape " + *str + " are not found.");

    return ALL_SHAPES;
}

colors str2color (const string *str)
{
    for (int i = 0; i < ALL_COLORS; ++i)
        if (*str == colors_enum_conv[i].str)
            return colors_enum_conv[i].val;

    throw invalid_argument("Such color " + *str + " are not found.");

    return ALL_COLORS;
}

class Rectangle;

class Shape {
protected:
    double centerX;
    double centerY;
    colors color;

public:
    Shape(double x, double y, colors c) : centerX(x), centerY(y), color(c) {}

    virtual double getArea() = 0;

    virtual Rectangle *getBoundingRectangle() = 0;
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double x, double y, colors c, double w, double h) :
                                        Shape(x, y, c), width(w), height(h) {}

    double getArea() override {
        return this->width * this->height;
    }

    Rectangle *getBoundingRectangle() override {
        return this;
    }

    void printInfo() {
        cout << "Color: " << colors_enum_conv[this->color].str << ", area: "
            << fixed << setprecision(2) << getArea() << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, colors c, double r) : Shape(x, y, c), radius(r) {}

    double getArea() override {
        return M_PI * this->radius * this->radius;
    }

    Rectangle *getBoundingRectangle() override {
        double side;

        side = 2 * this->radius;

        return new Rectangle(this->centerX, this->centerY, this->color, side,
                             side);
    }

    void printInfo() {
        cout << "Color: " << colors_enum_conv[this->color].str << ", area: "
            << fixed << setprecision(2) << getArea() << endl;
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double x, double y, colors c, double s) : Shape(x, y, c), side(s) {}

    double getArea() override {
        return this->side * this->side;
    }

    Rectangle *getBoundingRectangle() override {

        return new Rectangle(this->centerX, this->centerY, this->color,
                             this->side, this->side);
    }

    void printInfo() {
        cout << "Color: " << colors_enum_conv[this->color].str << ", area: "
            << fixed << setprecision(2) << getArea() << endl;
    }
};

class Triangle : public Shape {
private:
    double side;

public:
    Triangle(double x, double y, colors c, double s) : Shape(x, y, c), side(s) {}

    double getArea() override {
        return this->side * this->side / 2;
    }

    Rectangle *getBoundingRectangle() override {

        return new Rectangle(this->centerX, this->centerY, this->color,
                             this->side, this->side);
    }

    void printInfo() {
        cout << "Color: " << colors_enum_conv[this->color].str << ", area: "
            << fixed << setprecision(2) << getArea() << endl;
    }
};

void processCommand(const shapes shape, double x, double y, colors color,
                    double sideA, double sideB) {
    if (shape == CIRCLE){
        Circle circle(x, y, color, sideA);
        circle.printInfo();
    } else if (shape == SQUARE) {
        Square square(x, y, color, sideA);
        square.printInfo();
    } else if (shape == TRIANGLE) {
        Triangle triangle(x, y, color, sideA);
        triangle.printInfo();
    } else if (shape == RECTANGLE) {
        Rectangle rectangle(x, y, color, sideA, sideB);
        rectangle.printInfo();
    }
}

int main() {
    string x;
    string y;
    string sideA;
    string sideB;
    string shape;
    string color;

    try {
        cout << "Enter the name of the shape: ";
        getline (cin, shape);

        cout << "Enter the shape color: ";
        getline (cin, color);

        cout << "Enter the X coordinate of the center of the shape: ";
        getline (cin, x);

        cout << "Enter the Y coordinate of the center of the shape: ";
        getline (cin, y);

        cout << "Enter the size of one side of the shape: ";
        getline (cin, sideA);

        cout << "Enter the size of the second side of the shape (or nothing): ";
        getline (cin, sideB);

        processCommand(str2shape(&shape), strtod(x.c_str(), nullptr),
                       strtod(y.c_str(), nullptr), str2color(&color),
                       strtod(sideA.c_str(), nullptr),
                       (sideB != "")? strtod(sideB.c_str(), nullptr) : 0);
    }
    catch (const invalid_argument& err) {
        cerr << "Invalid argument: " << err.what() << endl;
    }

    return 0;
}

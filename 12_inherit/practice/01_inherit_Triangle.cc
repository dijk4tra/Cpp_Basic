#include <iostream>
#include <cmath>
#include <cstring>

using std::cout;
using std::endl;

class Point
{
public:
    Point(float a = 0, float b = 0)
    {
        x = a;
        y = b;
    }

    float getX() const
    {
        return x;
    }

    float getY() const
    {
        return y;
    }

private:
    float x;
    float y;
};

class Color
{
public:
    Color(const char* c = "unknown")
    {
        color = new char[strlen(c) + 1];
        strcpy(color, c);
    }

    Color(const Color& other)
    {
        color = new char[strlen(other.color) + 1];
        strcpy(color, other.color);
    }

    Color& operator=(const Color& other)
    {
        if (this != &other)
        {
            delete[] color;

            color = new char[strlen(other.color) + 1];
            strcpy(color, other.color);
        }

        return *this;
    }

    ~Color()
    {
        delete[] color;
    }

    const char* getColor() const
    {
        return color;
    }

private:
    char* color;
};

class Line
{
public:
    Line(Point p1 = Point(), Point p2 = Point())
        : start(p1), end(p2)
    {
    }

    float getLength() const
    {
        float dx = start.getX() - end.getX();
        float dy = start.getY() - end.getY();

        return sqrt(dx * dx + dy * dy);
    }

    void showLine() const
    {
        cout << "Start point: (" << start.getX() << ", " << start.getY() << ")" << endl;
        cout << "End point: (" << end.getX() << ", " << end.getY() << ")" << endl;
    }

private:
    Point start;
    Point end;
};

class Triangle : public Line, public Color
{
public:
    Triangle(Point p1, Point p2, const char* c, float h)
        : Line(p1, p2), Color(c)
    {
        height = h;
    }

    float getArea() const
    {
        return getLength() * height / 2;
    }

    float getPerimeter() const
    {
        float bottom = getLength();
        float hypotenuse = sqrt(bottom * bottom + height * height);

        return bottom + height + hypotenuse;
    }

    void show() const
    {
        cout << "Triangle information:" << endl;

        showLine();

        cout << "Color: " << getColor() << endl;
        cout << "Bottom length: " << getLength() << endl;
        cout << "Height: " << height << endl;
        cout << "Perimeter: " << getPerimeter() << endl;
        cout << "Area: " << getArea() << endl;
    }

private:
    float height;
};

int main()
{
    Point p1(0, 0);
    Point p2(3, 4);

    Triangle t(p1, p2, "red", 6);

    t.show();

    return 0;
}
#include <iostream>
#include <string>
#include <cmath>


class Point {
public:
    int x, y;
public:
    Point() :x(0), y(0) { 
        printf("Point() %d \n", (int)this%1000); 
    }
    Point(int x, int y):x(x), y(y) { 
        printf("Point(int x, int y) %d \n", (int)this%1000); 
    }
    Point(const Point& other) : x(other.x), y(other.y) { 
        printf("Point(Point) %d \n", (int)this%1000); 
    }
    virtual ~Point() { 
        printf("~Point() %d \n", (int)this%1000); 
    }

    double dist_to(const Point& p) {
        return pow((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y), 0.5);
    }

    void get_coords() {
        printf("Point coords: (%d, %d) \n", x, y);
    }
};


class ColoredPoint: public Point{
private:
    std::string color;
public:
    ColoredPoint(): Point(), color("null") {
        printf("ColoredPoint() %d \n", int(this)%1000); 
    }
    ColoredPoint(int x, int y, std::string color): Point(x, y), color(color) {
        printf("ColoredPoint(int x, int y, int color) %d \n", int(this)%1000); 
    }
    ColoredPoint(const ColoredPoint& other) : Point(other), color(other.color) { 
        printf("ColoredPoint(ColoredPoint) %d \n", int(this)%1000); 
    }
    ~ColoredPoint(){
        printf("~ColoredPoint() %d \n", int(this)%1000);
    }
    void change_color(std::string color) {
        this->color = color;
    }
};


class Section {
protected:
    Point p1;
    Point p2;
public:
    Section() { 
        printf("Section() %d \n", (int)this % 1000); 
    }
    Section(int x1, int y1, int x2, int y2): p1(x1,y1), p2(x2,y2) {
        printf("Section(int x1, int y1, int x2, int y2) %d \n", (int)this % 1000);
    }
    Section(const Section& other) {
        p1 = other.p1;
        p2 = other.p2;
        printf("Section(const Section&) %d, \n", (int)this % 1000);
    }
    ~Section() {
        printf("~Section() %d, \n", (int)this % 1000);
    }
    double Section_Length() {
        return p1.dist_to(p2);
    }
    void get_coords();
};


class Section2 {
protected:
    Point* p1;
    Point* p2;
public:
    Section2() :p1(new Point), p2(new Point) {
        printf("Section2() %d \n", int(this) % 1000);
    }
    Section2(int x1, int y1, int x2, int y2) {
        p1 = new Point(x1, y1);
        p2 = new Point(x2, y2);
        printf("Section2(int x1, int y1, int x2, int y2) %d \n", int(this) % 1000);
    }
    Section2(const Section2& other) {
        p1 = new Point(*other.p1);
        p2 = new Point(*other.p2);
        printf("Section2(const Section2&) %d \n", int(this) % 1000);
    }
    ~Section2() {
        delete p1;
        delete p2;
        printf("~Section() %d, \n", (int)this % 1000);
    }
    void get_coords();
};

//Вызов метода класса Section, у которого поля - объекты
void Section::get_coords() {
    p1.get_coords();
    p2.get_coords();
}

//Вызов метода класса Section, у которого поля - указатели
void Section2::get_coords() {
    p1->get_coords();
    p2->get_coords();
}


void Points() {
   
    Point p1; //Создание объекта статически с вызовом конструктора по умолчанию
    Point p2(5, 2); //Создание объекта статически с вызовом конструктора с параметрами
    Point p3(p2); //Создание объекта статически с вызовом конструктора копирования

    Point* p1d = new Point(); //Создание объекта динамически с вызовом конструктора по умолчанию
    Point* p2d = new Point(2, 5); //Создание объекта динамически с вызовом конструктора с параметрами
    Point* p3d = new Point(*p2d); //Создание объекта динамически с вызовом конструктора копирования

    printf("%f \n", p2d->dist_to(p2)); //Вызов метода объекта класса Point, созданного динамически
   
    //Удаление динамически созданных объектов
    delete p1d; //Point
    delete p2d; //Point
    delete p3d; //Point
}


void ColoredPoints() {
    
    ColoredPoint cp1;
    ColoredPoint cp2(5, 2, "Red");
    ColoredPoint cp3(cp2);

    ColoredPoint* cp1d = new ColoredPoint();
    ColoredPoint* cp2d = new ColoredPoint(2, 5, "Blue");
    ColoredPoint* cp3d = new ColoredPoint(*cp2d);

    printf("%f \n", cp2.dist_to(*cp2d)); //Вызов метода у объекта, созданного статически
   
    delete cp1d;
    delete cp2d;
    delete cp3d;
}


void Sections() {
    Section* s1 = new Section(2, 5, 5, 2);
    s1->Section_Length();
    s1->get_coords();
    delete s1;
}


void Sections2() {
    Section2* s1 = new Section2(2, 5, 5, 2);
    s1->get_coords();
    delete s1;
}

void other() {
    Point* p = new ColoredPoint(1, 3, "red");
    //p->change_color("green") - не скомпилируется, т. к объект класса потомка помещается в базовый класс
    p->get_coords(); // скомпилируется, т. к в базовом классе есть метод get_coords()
    delete p;
}

int main()
{
   //Points();
   //ColoredPoints();
   //Sections();
   //Sections2();
    other();
    
}


#include <iostream>
#include <memory>


//����� ���������

//auto ptr, weak ptr, unique ptr, shared ptr

class A {
public:
    A() {
        std::cout << "Constructor A()" << std::endl;
    }
    ~A() {
        std::cout << "Destructor A()" << std::endl;
    }
};

class Point {
public:
    Point(int x, int y) : _x(x), _y(y) {
        std::cout << "Constructor Point" << std::endl;
    }
    int getX() const {
        return _x;
    }
    int getY() const {
        return _y;
    }

    ~Point() {
        std::cout << "Destructor Point" << std::endl;
    }
private:
    int _x;
    int _y;
};

//��������� unique ptr
template <class T>
class SmartPtr {
    T* _ptr;
public:
    SmartPtr(T*t): _ptr(t){}
    T* operator ->() {
        return _ptr;        
    }
    ~SmartPtr() {
        delete _ptr;
    }
};

//unique_ptr ����� ��� � ����� ���������������� ��� ����� ���������� � ��������� ������� �� ������
void basicFunc(const std::unique_ptr<Point>& p) {
    std:: cout << p->getX() << std::endl;
}

class Parent {};
class Child: public Parent{} ;

std::shared_ptr<Parent> SomeMethod() {
    Child b;
    std::shared_ptr<Parent> a = std::make_shared<Parent>(b);
    return a;
}

//dinamic_cast <Point*>

class IVehicle {
public:
    virtual int getSpeed() const = 0;
    virtual const std::string& getType() const = 0;
    virtual ~IVehicle(){}
};

class Car : public IVehicle {
public:
    Car(int speed) : _speed(speed) {}
        int getSpeed() const override {
            return _speed;
        }
        const std::string &getType() const override {
            return _type;
        }
private:
    int _speed;
    std::string _type = "Car";
    
};

class Van : public Car {
public:
    Van(int speed) : Car(speed) {}
    const std::string& getType() const override {
        return _type;
    }
private:
    std::string _type = "Van";
};

void funcCar(std::shared_ptr<Car> carPtr) {

    std::cout << "Inside funcCar" << std::endl;
    std::cout <<carPtr->getSpeed() << std::endl;
    std::cout << carPtr->getType() << std::endl;
}

int main() {

    std::shared_ptr<Van> v = std::make_shared<Van>(30);
    std::cout << v->getSpeed()<< std::endl;
    std::cout << v->getType() << std::endl;
    std::cout << "==================" << std::endl;
    // std::dynamic_pointer_cast<new-type>(object to cast)
    std::shared_ptr<Car> c = std::dynamic_pointer_cast<Car>(v); // Car* c = dinamic_cast<Car*>(v)
    std::cout << c->getSpeed() << std::endl;
    std::cout << c->getType() << std::endl;
    std::cout << "==================" << std::endl;
    funcCar(c);



    //auto ptr - ������� � 2017 ���� ������ �� �����
//    std::auto_ptr<A> p(new A()); //���������� ��� delete, auto_ptr ��������
////A* a = new A(); //����� ����� delete - ������� ���������
//std::auto_ptr<A> p2=p; // p ��� �� ������� � - �� �������� ��������� (��� � ����� ��������� �� ���� ������)

    //shared ptr ����� ����������� ���� � ������� ����� ������� ���������� 

    //unique ptr  - �����������, ��� ������ ���� ��������� ������� ����� ��������
  //  std::unique_ptr<A> uptr(new A());
////std::unique_ptr<A> uptr2 = uptr; // ������ ������, ����������� ����������� ������


/*//std::unique_ptr<Point> pPoint(new Point(5, 4));
    std::cout << pPoint->getX() << std::endl;*/
    //std::cout << pPoint.get()->getX(); ����� � ��� �� �� �����
   // pPoint.release(); �� ccpreference
   // pPoint.reset(); �� ccpreference
   
    
   /* SmartPtr<Point> sm(new Point(5, 4));
    std::cout << sm->getX() << std::endl; // sm-> ������� �������� �� Point, ���� ���������� �������� ���������� ���������
                                          //�� � ���� ������ �� ��������� ����� ���������� ���������� �������� ���������� �� ��� ��� ���� �� �������� ������
    */
    //std::unique_ptr<Point> pPoint(new Point(5, 4));// ������� �������� ������ ���������
    /*std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4); //���������� �������� ������ ���������

    std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);
    std::shared_ptr<Point> sp2 = sp1;*/

    return 0;
}
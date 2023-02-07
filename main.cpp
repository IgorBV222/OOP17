#include <iostream>
#include <memory>


//”мные указатели

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

//концепци€ unique ptr
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

//unique_ptr почти как и любой пользовательский тип можно передавать в параметры функции по ссылке
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



    //auto ptr - опасный с 2017 года удален из €зыка
//    std::auto_ptr<A> p(new A()); //отработает без delete, auto_ptr сработал
////A* a = new A(); //здесь нужен delete - обычный указатель
//std::auto_ptr<A> p2=p; // p уже не владеет ј - не логичное поведение (два и более указател€ на один объект)

    //shared ptr имеет контрольный блок в котором лежит счетчик указателей 

    //unique ptr  - гарантирует, что только один указатель владеет одним объектом
  //  std::unique_ptr<A> uptr(new A());
////std::unique_ptr<A> uptr2 = uptr; // выдает ошибку, конструктор копировани€ удален


/*//std::unique_ptr<Point> pPoint(new Point(5, 4));
    std::cout << pPoint->getX() << std::endl;*/
    //std::cout << pPoint.get()->getX(); можно и так но не нужно
   // pPoint.release(); см ccpreference
   // pPoint.reset(); см ccpreference
   
    
   /* SmartPtr<Point> sm(new Point(5, 4));
    std::cout << sm->getX() << std::endl; // sm-> вернули уазатель на Point, если стрелочный оператор возвращает указатель
                                          //то в этом случае на указатель снова вызываетс€ стрелочный оператор рекурсивно до тех пор пока не вернетс€ объект
    */
    //std::unique_ptr<Point> pPoint(new Point(5, 4));// обычное создание умного указател€
    /*std::unique_ptr<Point> p5 = std::make_unique<Point>(5, 4); //правельное создание умного указател€

    std::shared_ptr<Point> sp1 = std::make_shared<Point>(1, 2);
    std::shared_ptr<Point> sp2 = sp1;*/

    return 0;
}
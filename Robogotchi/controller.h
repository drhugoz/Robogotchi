#ifndef CONTROLLER_H
#define CONTROLLER_H

//class scene;
//class robot;

class controller {
public:
    static controller* create() { return new controller(); }
    controller() = default;
    controller(const controller&) = delete;
    ~controller() = default;

private:
    //scene _scene;
    //robot _robot;
};

#endif // CONTROLLER_H

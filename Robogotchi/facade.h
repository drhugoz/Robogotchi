#ifndef FACADE_H
#define FACADE_H

#include "command.h"
#include "controller.h"

class facade {
public:
    facade();
    facade(const facade&) = delete;
    facade(facade&&) = delete;
    ~facade();

    void ExecuteCommand(command& command);

private:
    controller* _controller;
};

#endif // FACADE_H

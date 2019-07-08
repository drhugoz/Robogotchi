#include "facade.h"

facade::facade() {
    _controller = controller::create();
}

facade::~facade() {
    delete _controller;
}

void facade::ExecuteCommand(command& input) {
    input.execute(_controller);
}

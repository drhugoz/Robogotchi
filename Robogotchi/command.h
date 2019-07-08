#ifndef COMMAND_H
#define COMMAND_H

class controller;
class command {
public:
    command() = default;
    command(const command&) = delete;
    command(command&&) = delete;
    virtual ~command() = default;

    virtual void execute(controller*&) = 0;
};

#endif // COMMAND_H

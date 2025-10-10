#pragma once
#include <memory>

// Abstract base class for all commands
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual std::unique_ptr<Command> clone() const = 0;
};
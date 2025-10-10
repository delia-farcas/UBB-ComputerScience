#pragma once
#include "command.h"
#include <stack>
#include <memory>

class CommandManager {
private:
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

public:
    void executeCommand(std::unique_ptr<Command> command);
    bool canUndo() const;
    bool canRedo() const;
    void undo();
    void redo();
    void clear();
};

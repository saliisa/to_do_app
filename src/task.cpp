//Task Behaviour
#include "task.h"

//constructor
Task::Task(
    int id, 
    std::string title, 
    bool isCompleted, 
    int priority, 
    std::chrono::system_clock::time_point dueDate)
{
    this->id=id;
    this->title=title;
    this->isCompleted=isCompleted;
    this->priority=priority;
    this->dueDate = dueDate;
}

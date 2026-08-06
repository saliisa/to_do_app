//Task Behaviour
#include "task.hpp"
#include <iostream>

//!!Input validation


//constructor
Task::Task()
    : id(0),
      title(""),
      isCompleted(false),
      priority(0),
      dueDate("") 
{}

Task::Task(
    int id, 
    std::string title, 
    bool isCompleted, 
    int priority, 
    std::string dueDate)
{
    this->id=id;
    this->title=title;
    this->isCompleted=isCompleted;
    this->priority=priority;
    this->dueDate = dueDate;
}

//getters + setters
int Task::getId() const{
    return id;
}

void Task::setId(int id){
    this->id =id;
}

std::string Task::getTitle() const{
    return title;
}

void Task::setTitle(const std::string &title){
    if(!title.empty()){
        this->title = title;
    }
  
}

bool Task::getIsCompleted() const{
    return isCompleted;
}

void Task::setIsCompleted(bool status) {
    this->isCompleted = status;
}

int Task::getPriority() const{
    return priority;
}

void Task::setPriority(int priority){
    this->priority = priority;
}

std::string Task::getDueDate() const{
    return dueDate;
}

void Task::setDueDate(std::string dueDate){
    this->dueDate = dueDate;
}

std::ostream& operator<<(std::ostream& os, const Task& task) {
    os << "Task { "
       << "ID: " << task.id << ", "
       << "Title: " << task.title << ", "
       << "Completed: " << task.isCompleted << ", "
       << "Priority: " << task.priority << ", "
       << "Due Date: " << task.dueDate
       << " }";
    return os;
}

json Task::toJson() const{ //converts a Task in a json Object
    return json{
        {"id", id},
        {"title", title},
        {"isCompleted", isCompleted},
        {"priority", priority},
        {"dueDate", dueDate},

    };
}

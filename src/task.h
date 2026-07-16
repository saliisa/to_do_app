//defines what a task is
//function declaration done here
#include <string>
#include <chrono>
#ifndef TASK_H
#define TASK_H

class Task{ //automatically  private
    int id; 
    std::string title;
    bool isCompleted;
    int priority;
    std::chrono::system_clock::time_point dueDate;

   public:
    //constructors
    Task();

    Task(int id, 
        std::string title, 
        bool isCompleted, 
        int priority, 
        std::chrono::system_clock::time_point dueDate);

   //getters
    int getId() const;
    std::string getTitle() const;
    bool getIsCompleted() const;
    int getPriority() const;
    std::chrono::system_clock::time_point getDueDate() const;

   //setters
    void setId(int id);
    void setTitle(const std::string& title);
    void setIsCompleted(bool status);
    void setPriority(int priority) ;
    void setDueDate(std::chrono::system_clock::time_point dueDate);
};

#endif
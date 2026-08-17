//defines what a task is
//function declaration done here
#include <string>
#include <chrono>
#ifndef TASK_HPP
#define TASK_HPP
//#include "json.hpp"
//using json = nlohmann::json;

class Task{ //automatically  private
    int id; 
    std::string title;
    bool isCompleted;
    int priority;
    std::string dueDate;

   public:
    //constructors
    Task(); //default

    Task(int id, 
        std::string title, 
        bool isCompleted, 
        int priority, 
        std::string dueDate);

   //getters
    int getId() const;
    std::string getTitle() const;
    bool getIsCompleted() const;
    int getPriority() const;
    std::string getDueDate() const;

   //setters
    void setId(int id);
    void setTitle(const std::string &title);
    void setIsCompleted(bool status);
    void setPriority(int priority) ;
    void setDueDate(std::string dueDate);

    //toString
    friend std::ostream& operator<<(std::ostream& os, const Task& task);

    //json
    //json toJson() const;
};

#endif
//manages tasks

#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP

#include <vector>
#include <optional>
#include "task.hpp" 

//structs are better for partial updates
struct TaskUpdate{
    // std::optional<T> is a small object that contains either a value 
    //of type T or nothing 
    // not a pointer but behaves pointer-like
    std::optional<std::string> title;
    std::optional<bool> status;
    std::optional<int> priority;
    std::optional<std::string> dueDate;
};

class TaskManager{
    public:
        void addTask(Task task);
        void editTask(int id,  std::string title, bool status, int priority, std::string dueDate);
        void deleteTask(int id);
        void listAllTasks();
        void listCompletedTasks();

        bool editTask(int id, const TaskUpdate& update);

        void saveToJson();

    private:
        std::vector<Task> tasks; //resizeable array
        int nextId = 1;
};



#endif
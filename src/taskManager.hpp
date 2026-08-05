//manages tasks
#include <vector>
#include "task.hpp" 
#ifndef TASKMANAGER_HPP
#define TASKMANAGER_HPP
class TaskManager{
    public:
        void addTask(Task task);
        void editTask(int id,  std::string title, bool status, int priority, std::string dueDate);
        void deleteTask(int id);
        void listAllTasks();
        void listCompletedTasks();

        void saveToJson();

    private:
        std::vector<Task> tasks; //resizeable array
        int nextId = 1;
};



#endif
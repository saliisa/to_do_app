//manages tasks
#include <vector>
#include "task.h" 
#ifndef TASKMANAGER_H
#define TASKMANAGER_H
class TaskManager{
    public:
        void addTask(Task task);
        void editTask(int id,  std::string title, bool status, int priority, std::string dueDate);
        void deleteTask(int id);
        void listAllTasks();
        void listCompletedTasks();

    private:
        std::vector<Task> tasks; //resizeable array
};



#endif
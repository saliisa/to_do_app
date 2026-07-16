//manages tasks
#include <vector>
#include "task.h"
#ifndef TASKMANAGER_H
#define TASKMANAGER_H
class TaskManager{
    public:
        void addTask();
        void editTask();
        void deleteTask();
        void listAllTasks();
        void listCompletedTasks();

    private:
        std::vector<Task> tasks; //resizeable array
};



#endif
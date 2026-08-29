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

        //sqlite --> move to database.cpp?
       // bool openDatabase(); //needed? 
       // void createTable(); //needed? --> is the DB schema created?
        bool insertTask(Task& task);
        bool getAllTasks();
        bool updateTask(int id, TaskUpdate& update);
        bool removeTask(int id);
        bool getCompletedTasks();
       // bool getUncompletedTasks();

       // static int callback(void* data, int argc, char **argv, char **colNames );


        bool addTask(Task& task);
        void editTask(int id,  std::string title, bool status, int priority, std::string dueDate);
        bool deleteTask(int id);
        void listAllTasks();
        void listCompletedTasks();

        bool editTask(int id, const TaskUpdate& update);
        bool taskExists(int id);

        //void saveToJson();
        //void loadFromJson();
        //void removeFromJson(int id);

    private:
        std::vector<Task> tasks; //resizeable array //remove once SQLite is implemented
};



#endif
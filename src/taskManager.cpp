#include <iostream>
#include "taskManager.h"
#include <algorithm>

void TaskManager:: addTask(Task task){
    tasks.push_back(task);
}

void TaskManager:: deleteTask(int id){
   tasks.erase(
    std::remove_if(tasks.begin(), tasks.end(), //scans vector from beginning to end; moves all elements that should NOT be removed to the front; moves all elements that should be removed to the back; returns an iterator pointing to the first element that should be erased; this returned iterator becomes the start of the erase range
        [id](const Task& t){ // [id] captures variable ID from outside the lambda so you can use it inside
            return t.getId() == id; //tells remove_if to remove this task if its ID matches the one we're looking for 
        }),
    tasks.end() // removes everything from the first removed element to the end of the vector
   );
}

void TaskManager::editTask(int id, std::string title, bool status, int priority, std::string dueDate){ //to be implemented
    for(auto& i: tasks){ //& - references the actual task stored inside the vector
        if(i.getId() == id){
            i.setTitle(title);
            i.setIsCompleted(status);
            i.setPriority(priority);
            i.setDueDate(dueDate);
        }
    }
}

void TaskManager::listAllTasks(){
    for(auto i: tasks){
        std::cout << i << std::endl;
    }
}

void TaskManager::listCompletedTasks(){
    for(auto i: tasks){
        if(i.getIsCompleted() == true){
            std::cout << i << std::endl;
        } 
    }
}
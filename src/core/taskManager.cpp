#include <iostream>
#include "../utils/utils.hpp"
#include <algorithm>
#include <fstream>

//#include "json.hpp"
//using json = nlohmann::json;

sqlite3* db;











bool TaskManager:: addTask(Task task){

    if(!validateTitle(task.getTitle()) || !validateDate(task.getDueDate()) || 
        task.getPriority() < 1 || task.getPriority() > 3){
        return false;
    }

    if(task.getId() == 0){
        task.setId(nextId++);
    }
    tasks.push_back(task);
    return true;
}
// void TaskManager:: addTask(int id, std::string title, bool status, int priority, std::string dueDate){ //to be implemented){



bool TaskManager::deleteTask(int id){
   auto newEnd =  std::remove_if(
        tasks.begin(), 
        tasks.end(), //scans vector from beginning to end; moves all elements that should NOT be removed to the front; moves all elements that should be removed to the back; returns an iterator pointing to the first element that should be erased; this returned iterator becomes the start of the erase range
        [id](const Task& t){ // [id] captures variable ID from outside the lambda so you can use it inside
            return t.getId() == id; //tells remove_if to remove this task if its ID matches the one we're looking for 
        }
    );

    if(newEnd == tasks.end()){
        return false; // nothing was found
    }

    tasks.erase(newEnd, tasks.end());
    return true; // task was deleted

}

//needed?
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

bool TaskManager::editTask(int id, const TaskUpdate& update){
    for(auto& i : tasks){
        if(i.getId() == id){

            if(update.title){
                i.setTitle(*update.title); //gives the actual string inside the optional  
            }

            if(update.status){
                i.setIsCompleted(*update.status);
            }

            if(update.priority){
                i.setPriority(*update.priority);
            }

            if(update.dueDate){
                i.setDueDate(*update.dueDate);
            }

            return true;

        }
        

    }
    return false;
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

bool TaskManager::taskExists(int id){
    for(auto& t : tasks){
        if(t.getId() == id){
            return true;
        }
       
    }
    return false;
} 

/*void TaskManager::saveToJson(){
    json j; //empty json array
    
    for(auto& t : tasks){
        j.push_back(t.toJson());
    }

    std::ofstream file("tasks.json");
    file << j.dump(4); // writes the JSON array into the file
    // converts json to string
    //format it with 4 spaces indentation
}*/

/*void TaskManager::loadFromJson(){
   std::ifstream file("tasks.json");

   json data = json::parse(file);

   if(!file.is_open()){
        //returns nothing if file doesnt exist 
        return;
   }

   file >> data;

   tasks.clear();
}*/

//void removeFromJson(int id){}
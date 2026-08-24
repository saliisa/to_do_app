#include <iostream>
#include "../utils/utils.hpp"
#include <algorithm>
#include <fstream>
#include <string>


sqlite3* db;
sqlite3_stmt* stmt;

bool TaskManager::insertTask(Task& task){
    //insert into sqlite db 
    //TBD prepared statements to prevent SQL injection

    //open db
    if(sqlite3_open("./data/tasks.db", &db) != SQLITE_OK){
        std::cout << "failed to open tasks db\n";
        return false;
    }

    //sql 
   std::string insertSql = "INSERT INTO tasks ( title, completed, priority, due_date) VALUES ('" +
    task.getTitle() + "', " +
    std::to_string(task.getIsCompleted()) + ", " +
    std::to_string(task.getPriority()) + ", '" +
    task.getDueDate() + "');";

    std::cout << "DEBUG SQL: " << insertSql << std::endl;


    //complies SQL into a prepared stmt; stores this complied stmt into "stmt"
    if(sqlite3_prepare(db, insertSql.c_str(), -1, &stmt, NULL) !=SQLITE_OK){ //prepare stmt
        std::cout << "Failed to prepare statement" << std::endl;
        sqlite3_close(db);
        return false;
    } 

 
    //executing prepared stmt
    if(sqlite3_step(stmt) != SQLITE_DONE){
        std::cout << "Failed to execute insert" << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }
    

    sqlite3_finalize(stmt); //frees prepared stmt
    sqlite3_close(db); // closes db connection

    return true;

}
       
 /*
    bool getAllTasks();
    void updateTask(Task& task);
    void removeTask(int id);*/


bool TaskManager:: addTask(Task& task){

    if(!validateTitle(task.getTitle()) || !validateDate(task.getDueDate()) || 
        task.getPriority() < 1 || task.getPriority() > 3){
        return false;
    }

    tasks.push_back(task);
    return true;
}


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

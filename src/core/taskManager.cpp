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
bool updateTask(Task& task);
bool removeTask(int id);
bool getCompletedTasks();
bool getUncompletedTasks();
*/
   
bool TaskManager::getAllTasks(){
    //open db
    if(sqlite3_open("./data/tasks.db", &db) != SQLITE_OK){
        std::cout << "failed to open tasks db\n";
        return false;
    }

    std::string sql = "SELECT * FROM tasks;";

    //complies SQL into a prepared stmt; stores this complied stmt into "stmt"
    if(sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL) !=SQLITE_OK){ //prepare stmt
        std::cout << "Failed to prepare statement" << std::endl;
        sqlite3_close(db);
        return false;
    } 

    std::cout <<"\n\n";
    std::cout << "== Tasks ==" << std::endl;

    //print column names
    int colCount = sqlite3_column_count(stmt);
    for(int i =0; i < colCount; i++){
        std::cout << sqlite3_column_name(stmt,i) << " | ";
    }
    std::cout <<"\n-------------------------------------\n";

    //print row values 
    while(sqlite3_step(stmt) == SQLITE_ROW){ //return one row per call
        for(int i = 0; i < colCount; i++){
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)); //values from row
            std::cout << (value ? value: "NULL") << " | ";

        }
        std::cout <<"\n\n";
    }
    sqlite3_finalize(stmt); //frees prepared stmt
    sqlite3_close(db); // closes db connection
    return true;

}


bool TaskManager::removeTask(int id){
    //TBD sql injection prevention

    //open db
    if(sqlite3_open("./data/tasks.db", &db) != SQLITE_OK){
        std::cout << "failed to open tasks db\n";
        return false;
    }


    std::string deleteSql = "DELETE FROM tasks where id = ?";

    if(sqlite3_prepare(db, deleteSql.c_str(), -1, &stmt, NULL) !=SQLITE_OK){ //prepare stmt
        std::cout << "Failed to prepare statement" << std::endl;
        sqlite3_close(db);
        return false;
    } 

    sqlite3_bind_int(stmt,1,id);
    //what if ID doesnt exist?


    if(sqlite3_step(stmt) != SQLITE_DONE){
        std::cout << "Failed to execute delete" <<std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    int changes = sqlite3_changes(db);

    if(changes == 0){
        std::cout << "No task with that ID exists.\n";
        return false;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db); 
    return true;


}


bool TaskManager::getCompletedTasks(){
     //open db
    if(sqlite3_open("./data/tasks.db", &db) != SQLITE_OK){
        std::cout << "failed to open tasks db\n";
        return false;
    }

    std::string sql = "SELECT * FROM tasks WHERE completed = 1;";

    //complies SQL into a prepared stmt; stores this complied stmt into "stmt"
    if(sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL) !=SQLITE_OK){ //prepare stmt
        std::cout << "Failed to prepare statement" << std::endl;
        sqlite3_close(db);
        return false;
    } 

    std::cout <<"\n\n";
    std::cout << "== Completed Tasks ==" << std::endl;

    //print column names
    int colCount = sqlite3_column_count(stmt);
    for(int i =0; i < colCount; i++){
        std::cout << sqlite3_column_name(stmt,i) << " | ";
    }
    std::cout <<"\n-------------------------------------\n";

    //print row values 
    while(sqlite3_step(stmt) == SQLITE_ROW){ //return one row per call
        for(int i = 0; i < colCount; i++){
            const char* value = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)); //values from row
            std::cout << (value ? value: "NULL") << " | ";

        }
        std::cout <<"\n\n";
    }
    sqlite3_finalize(stmt); //frees prepared stmt
    sqlite3_close(db); // closes db connection
    return true;
}



bool TaskManager::updateTask(int id, TaskUpdate& update){ // redo database.cpp structure to avoid opening db everytime functions are called
    if(sqlite3_open("./data/tasks.db", &db) != SQLITE_OK){
        std::cout << "failed to open tasks db\n";
        return false;
    }
 

    std::vector<std::string> setClauses; //dynamic setClause sql

    if(update.title.has_value()){
        setClauses.push_back("title = ?");
    }

    if(update.status.has_value()){
        setClauses.push_back("completed = ?");
    }

    if(update.priority.has_value()){
        setClauses.push_back("priority = ?");
    }

    if(update.dueDate.has_value()){
        setClauses.push_back("due_date = ?");
    }

    if(setClauses.empty()){
        std::cout << "No fields to update" << std::endl;
        sqlite3_close(db);
        return false;
    }

    std::string updateSql = "UPDATE tasks SET ";

    for(size_t i = 0; i < setClauses.size(); ++i){ //size_t unsigned type 
       if (i > 0) {
            updateSql += ", ";   //sql string separator except before the first clause
        }
      updateSql += setClauses[i];
    }
    updateSql += " WHERE id = ?;";

    //complies SQL into a prepared stmt; stores this complied stmt into "stmt"
    if(sqlite3_prepare_v2(db, updateSql.c_str(), -1, &stmt, nullptr) !=SQLITE_OK){ //prepare stmt
       std::cout << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        //std::cout << "SQL was: " << updateSql << std::endl;
        sqlite3_close(db);
        return false;
    } 

    int idx = 1; //counter that only increments when a field is actually bound

    if (update.title.has_value()){
        sqlite3_bind_text(stmt, idx++, update.title->c_str(), -1, SQLITE_TRANSIENT);
    }
       
    if (update.status.has_value()){
        sqlite3_bind_int(stmt, idx++, update.status.value());
    }

    if (update.priority.has_value()){
        sqlite3_bind_int(stmt, idx++, update.priority.value());
    }

    if (update.dueDate.has_value()){
        sqlite3_bind_text(stmt,idx++, update.dueDate->c_str(), -1, SQLITE_TRANSIENT);
    }

    sqlite3_bind_int(stmt, idx, id); //WHERE id = ?


    //executing prepared stmt
    if(sqlite3_step(stmt) != SQLITE_DONE){
        std::cout << "Failed to execute update" << sqlite3_errmsg(db) << std::endl;
        //std::cout << "SQL was: " << updateSql << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return false;
    }

    bool rowUpdated = sqlite3_changes(db) > 0;
    if (!rowUpdated) {
        std::cout << "No task found with id " << id << std::endl;
    }
    
    sqlite3_finalize(stmt); //frees prepared stmt
    sqlite3_close(db); // closes db connection

    return rowUpdated;
}




















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

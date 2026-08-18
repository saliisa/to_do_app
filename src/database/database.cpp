#include "Database.hpp"
#include <iostream>


//construtor that creates the SQLite connection pointer
Database::Database(const std::string& filename) : db(nullptr){
    //opens the database, if 'filename' doesnt exist, it creates it
    int result = sqlite3_open(filename.c_str(), &db);

    if(result != SQLITE_OK){
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        db = nullptr;

    }

}


//destructor closes the database when your Database object is destroyed
Database::~Database(){
    if(db != nullptr){
        sqlite3_close(db);
    }
}


//initialize creates the table
bool Database::initialize(){
    //R("") is a raw string literal 
    // lets us write without having to worry about escaping every quotation mark or newline
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS tasks (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            completed INTEGER NOT NULL DEFAULT 0,
            priority INTEGER NOT NULL,
            due_date TEXT NOT NULL
        );
    )";

    //pointer where SQLite can put an error message if something goes wrong
    char* errorMessage = nullptr;

    //telling SQLite to take the SQL string and execute it against my database
    int result = sqlite3_exec(db, sql, nullptr, nullptr, &errorMessage);
    //db - database connection from sqlite3* db; execute this command on this database
    //sql - sql statement made earlier
    // nullptr - callabck function; with CREATE TABLE a callback function is not needed as it isnt returning rows to us
    // (other) nullptr - extra data that can be passed to the callback
    // &errorMessage - SQlite can change it to point to an error msg if sth goes wrong

    if(result != SQLITE_OK){
        std::cerr << "Failed to create tasks table: " << errorMessage << std::endl;
        sqlite3_free(errorMessage); // frees allocated memory for error msg
        return false;
    }
    return true;
}


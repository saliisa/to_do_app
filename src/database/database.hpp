#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../third_party/sqlite3.h"
#include <string>

class Database{
    private:
        sqlite3* db;


    public: 
        //constructor
        Database(const std::string& filename);

        //destructor
        ~Database();

        //method
        bool initialize();

};


#endif
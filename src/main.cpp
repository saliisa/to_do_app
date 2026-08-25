//entry point of the program
#include <iostream>
#include <limits>
#include "./utils/utils.hpp"
#include "./database/database.hpp"

using namespace std;
void displayMenu();
//int DatabaseTest();
int main(){
    int option = 0;

    TaskManager manager;

    string title;
    string dueDate;
    int inputId;
    string status;
    string priority;

   // DatabaseTest();
  //  Database database("./data/tasks.db");


  
    while(option != 6){
        displayMenu();

        std::cout << "Choose an option (1 - 6): " <<endl;
       while(!(cin >> option) || !validateInt(option,1,6)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::cout << "Please input a valid number:  " <<endl;
        }

     switch(option){
            case 1: { //add task
                Task task;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //Title
                std::cout << "Title of task: " <<endl;
                std::getline(cin,title);

                while(!validateTitle(title)){
                    std::cout << "Title is invalid. Please try again: ";
                    std::getline(cin,title);
                }

                task.setTitle(title);
            
                //Priority
                std::cout << "\nPriority of task ((1) Urgent, (2) Important, (3) Routine): " <<endl;
                std::getline(cin,priority);
                
                while(!validatePriority(priority)){
                    std::cout << "Priority is invalid. Please try again: ";
                    std::getline(cin,priority);
                }

                task.setPriority(stoi(priority));

                //Due date
                std::cout << "\nDue date of task (YYYY-MM-DD): " <<endl;
                std::getline(cin,dueDate);

                while(!validateDate(dueDate)){
                    std::cout << "Due date is invalid. Please try again: ";
                    std::getline(cin,dueDate);
                }

                task.setDueDate(dueDate);
                
                //adding task 
               if(manager.addTask(task)){
                    std::cout << "\n== Task added successfully ==" <<endl;  //delete?
                } else{
                    std::cout << "\n== Failed to add task ==" <<endl;
                }


                //insert in sqlite
               if(manager.insertTask(task)) {
                    std::cout << "\nInserted task into tasks table successfully" << std::endl; //delete?
               } else{
                    std::cout << "\nFailed to insert task into tasks table" << std::endl;
               }
                
                break;
            }
              
            case 2:{
                // edit task
                TaskUpdate update;
                std::cout << "Please input the ID you want to edit: " <<endl;
                cin >> inputId;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
               if(!manager.taskExists(inputId)){
                    std::cout << "ID does not exist." << endl;
                    break;
                }

                //title
                std::cout << "New title (leave empty to keep): " ;
                std::getline(cin, title); 
                if(!title.empty()){
                    while(!validateTitle(title)){
                        std::cout << "Invalid title. Try again: ";
                        std::getline(cin,title);
                    }
                    update.title = title;
                }

                //status
                std::cout << "Completed? (Input number: 0 - No / 1 - Yes / leave empty to keep): " ;
                std::getline(cin, status);
                while(!status.empty() && !validateStatus(status)){
                   std::cout << "Invalid input. Enter 0, 1, or leave empty: ";
                   std::getline(cin,status);
                }

                if(!status.empty()){
                    update.status = (status == "1");
                }

                //priority
                std::cout << "Priority ((1) Urgent / (2) Important / (3) Routine / leave empty to keep): " ;
                std::getline(cin, priority);

                while(!priority.empty() && !validatePriority(priority)){
                    std::cout << "Invalid priority. Enter 1, 2, 3, or leave empty: ";
                    std::getline(cin,priority);
                }
                if(!priority.empty()){
                    update.priority = stoi(priority);
                }

                //due date
                std::cout << "Due Date (leave empty to keep):  " ;
                std::getline(cin, dueDate);

                while(!dueDate.empty() && !validateDate(dueDate)){
                    std::cout << "Invalid due date. Use YYYY-MM-DD or leave empty: ";
                    std::getline(cin,dueDate);
                }
              
                if(!dueDate.empty()){
                   update.dueDate = dueDate;
                }

                if(manager.editTask(inputId, update)){
                    std::cout << "Task updated successfully!." <<endl;
                } else{
                    std::cout << "Error updating task. " <<endl;
                }

                break;
            }
               
            case 3: 
               //remove task
               std::cout << "Input ID of task you want to delete:  " <<endl;

                while(!(cin >> inputId)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    std::cout << "Please input a valid number " <<endl;
                }

              /*if(!manager.taskExists(inputId)){
                    std::cout << "ID does not exist." << endl;
                    break;
                }*/  

               /* if(manager.deleteTask(inputId)){
                    std::cout << "Task deleted successfully!" <<endl;
                } else{
                    std::cout << "Error deleting task" << endl;
                }*/


                if(manager.removeTask(inputId)){
                    std::cout << "Task removed from database" << endl;
                } else{
                    std::cout << "Error removing task" <<endl;
                }
               
                break;
            case 4:
               //Show list of tasks
             //  manager.listAllTasks();
                manager.getAllTasks();
                break;
            case 5:
               //Show completed list of tasks
               //manager.listCompletedTasks();
               manager.getCompletedTasks();
                break;
            
            default:
                break; 
        }
    }
   // database.~Database(); //closes db


    std::cout << "Goodbye!" <<endl;
    
    return 0;
}

/*int DatabaseTest(){
    Database database("data/tasks.db"); //creates and opens database
    if(!database.initialize()){ // checks if initlization works 
        cerr << "Database initialization failed" << endl;
        return 1;
    }

    std::cout << "Database initialized successfully" <<endl;
    return 0;
}*/

void displayMenu(){
    std::cout << "===== TO DO =====" <<endl;
    std::cout << "1. Add Task" << endl;
    std::cout << "2. Edit Task" << endl;
    std::cout << "3. Delete Task" << endl;
    std::cout << "4. Show List of Tasks" << endl;
    std::cout << "5. Show Completed List of Tasks" << endl;
    std::cout << "6. Exit" << endl;
}
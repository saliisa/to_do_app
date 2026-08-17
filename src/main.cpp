//entry point of the program
#include <iostream>
#include <limits>
#include "./utils/utils.hpp"

using namespace std;
void displayMenu();
int main(){
    int option = 0;

    TaskManager manager;

    string title;
    string dueDate;
    int inputId;
    string status;
    string priority;

    while(option != 6){
        displayMenu();

        cout << "Choose an option (1 - 6): " <<endl;
       while(!(cin >> option) || !validateInt(option,1,6)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a valid number:  " <<endl;
        }

     switch(option){
            case 1: { //add task
                Task task;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //Title
                cout << "Title of task: " <<endl;
                getline(cin,title);

                while(!validateTitle(title)){
                    cout << "Title is invalid. Please try again: ";
                    getline(cin,title);
                }

                task.setTitle(title);
            
                //Priority
                cout << "\nPriority of task ((1) Urgent, (2) Important, (3) Routine): " <<endl;
                getline(cin,priority);
                
                while(!validatePriority(priority)){
                    cout << "Priority is invalid. Please try again: ";
                    getline(cin,priority);
                }

                task.setPriority(stoi(priority));

                //Due date
                cout << "\nDue date of task (YYYY-MM-DD): " <<endl;
                getline(cin,dueDate);

                while(!validateDate(dueDate)){
                    cout << "Due date is invalid. Please try again: ";
                    getline(cin,dueDate);
                }

                task.setDueDate(dueDate);
                
               if(manager.addTask(task)){
                    cout << "\n== Task added successfully ==" <<endl; 
                } else{
                    cout << "\n== Failed to add task ==" <<endl;
                }
                
                break;
            }
              
            case 2:{
                // edit task
                TaskUpdate update;
                cout << "Please input the ID you want to edit: " <<endl;
                cin >> inputId;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
               if(!manager.taskExists(inputId)){
                    cout << "ID does not exist." << endl;
                    break;
                }

                //title
                cout << "New title (leave empty to keep): " ;
                getline(cin, title); 
                if(!title.empty()){
                    while(!validateTitle(title)){
                        cout << "Invalid title. Try again: ";
                        getline(cin,title);
                    }
                    update.title = title;
                }

                //status
                cout << "Completed? (Input number: 0 - No / 1 - Yes / leave empty to keep): " ;
                getline(cin, status);
                while(!status.empty() && !validateStatus(status)){
                   cout << "Invalid input. Enter 0, 1, or leave empty: ";
                   getline(cin,status);
                }

                if(!status.empty()){
                    update.status = (status == "1");
                }

                //priority
                cout << "Priority ((1) Urgent / (2) Important / (3) Routine / leave empty to keep): " ;
                getline(cin, priority);

                while(!priority.empty() && !validatePriority(priority)){
                    cout << "Invalid priority. Enter 1, 2, 3, or leave empty: ";
                    getline(cin,priority);
                }
                if(!priority.empty()){
                    update.priority = stoi(priority);
                }

                //due date
                cout << "Due Date (leave empty to keep):  " ;
                getline(cin, dueDate);

                while(!dueDate.empty() && !validateDate(dueDate)){
                    cout << "Invalid due date. Use YYYY-MM-DD or leave empty: ";
                    getline(cin,dueDate);
                }
              
                if(!dueDate.empty()){
                   update.dueDate = dueDate;
                }

                if(manager.editTask(inputId, update)){
                    cout << "Task updated successfully!." <<endl;
                } else{
                    cout << "Error updating task. " <<endl;
                }

                break;
            }
               
            case 3: 
               //remove task
               cout << "Input ID of task you want to delete:  " <<endl;

                while(!(cin >> inputId)){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please input a valid number " <<endl;
                }

                if(!manager.taskExists(inputId)){
                    cout << "ID does not exist." << endl;
                    break;
                }

                if(manager.deleteTask(inputId)){
                    cout << "Task deleted successfully!" <<endl;
                } else{
                    cout << "Error deleting task" << endl;
                }
               
                break;
            case 4:
               //Show list of tasks
               manager.listAllTasks();
                break;
            case 5:
               //Show completed list of tasks
               manager.listCompletedTasks();
                break;
            
            default:
                break; 
        }
    }

    cout << "Goodbye!" <<endl;
    
    return 0;
}

void displayMenu(){
    cout << "===== TO DO =====" <<endl;
    cout << "1. Add Task" << endl;
    cout << "2. Edit Task" << endl;
    cout << "3. Delete Task" << endl;
    cout << "4. Show List of Tasks" << endl;
    cout << "5. Show Completed List of Tasks" << endl;
    cout << "6. Exit" << endl;
}
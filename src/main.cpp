//entry point of the program
#include <iostream>
#include <limits>
#include "utils.hpp"

using namespace std;
void displayMenu();
int main(){
    int option = 0;

    Task task;
    TaskManager manager;
    TaskUpdate update;

    string title;
    string dueDate;
    int inputId;
    string status;
    string priority;

    while(option != 6){
        displayMenu();

        cout << "Choose an option (1 - 6): " <<endl;
       while(!(cin >> option)){ //getline()??
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a number " <<endl;
        }

     switch(option){
            case 1: //fix?
               //add task
              cin.ignore(numeric_limits<streamsize>::max(), '\n');

                //title
                cout << "Title of task: " <<endl;
                getline(cin,title);

                //priority
                cout << "Priority of task ((1) Urgent, (2) Important, (3) Routine): " <<endl;
                getline(cin,priority); //validation needed
                
                //due date
                cout << "Due date of task (YYYY-MM-DD): " <<endl;
                getline(cin,dueDate); //validation needed

                task.setTitle(title);
                task.setPriority(stoi(priority));
                task.setDueDate(dueDate);

                manager.addTask(task);
                break;
            case 2:
                // edit task
                cout << "Please input the ID you want to edit: " <<endl;
                cin >> inputId;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                //title
                cout << "New title (leave empty to keep): " ;
                getline(cin, title); 
                if(!title.empty()){
                    update.title = title;
                }

                //status
                cout << "Completed? (Input number: 0 - No / 1 - Yes / leave empty to keep): " ;
                getline(cin, status); //validation needed
                if(!status.empty()){
                   update.status = (status == "1");
                }

                //priority
                cout << "Priority ((1) Urgent / (2) Important / (3) Routine / leave empty to keep): " ;
                getline(cin, priority); //validation needed
                if(!priority.empty()){
                   update.priority = stoi(priority);
                }

                //due date
                cout << "Due Date (leave empty to keep):  " ;
                getline(cin, dueDate); //validation needed
                if(!dueDate.empty()){
                   update.dueDate = dueDate;
                }

                if(manager.editTask(inputId, update)){
                    cout << "Task updated successfully!." <<endl;
                } else{
                    cout << "Error updating task. " <<endl;
                }

                break;

            case 3:
               //remove task
               cout << "Input ID of task you want to delete:  " <<endl;
               //ID validation needed
                while(!(cin >> inputId)){ 
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please input a valid number " <<endl;
                }

                manager.deleteTask(inputId);
               
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
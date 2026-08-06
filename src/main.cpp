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
    bool isCompleted;
    int priority;
    string dueDate;
    int inputId;

    string newTitle;
    string status;
    string prio;
    string date;

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
                cout << "Priority of task ((1) Urgent, (2) Important, (3) Routine ): " <<endl;
                while(!(cin >> priority)){ 
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Please input a valid number " <<endl;
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                //due date
                cout << "Due date of task (YYYY-MM-DD): " <<endl;
                getline(cin,dueDate); //------validation needed

                task.setTitle(title);
                task.setPriority(priority);
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
                getline(cin, newTitle);
                if(!newTitle.empty()){
                    update.title = newTitle;
                }

                //status
                cout << "Completed? (0 - No / 1 - Yes / leave empty to keep): " ;
                getline(cin, status);
                if(!status.empty()){
                   update.status = (status == "1");
                }

                //priority
                cout << "Priority ((1) Urgent / (2) Important / (3) Routine / leave empty to keep): " ;
                getline(cin, prio);
                if(!prio.empty()){
                   update.priority = stoi(prio);
                }

                //due date
                cout << "Due Date (leave empty to keep):  " ;
                getline(cin, date);
                if(!date.empty()){
                   update.dueDate = date;
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
    

  /*  Task t1;
    Task t2;

    TaskManager manager;

    t1.setId(1);
    cout << t1.getId() << endl;
    t1.setTitle("Buy groceries");
    t1.setIsCompleted(true);
    t1.setPriority(2);
    t1.setDueDate("2026-07-20");

    t2.setId(2);
    t2.setTitle("Do laundry");
    t2.setIsCompleted(false);
    t2.setPriority(3);
    t2.setDueDate("2026-07-21");

    //cout << t1 <<endl;

    manager.addTask(t1);
    manager.addTask(t2);
    cout << "all tasks:" <<endl;
    manager.listAllTasks();


   cout << "Pick an ID: " << endl;
    
    int id;

    cin >> id;

    manager.deleteTask(id);

    //cout << "all tasks after deletion:" <<endl;
   // manager.listAllTasks();
   cout << "list of completed tasks: " <<endl;
   manager.listCompletedTasks();

   manager.editTask(2, "Do laundry", true, 3, "2026-07-21" );

   cout << "all tasks after editing: " << endl;
   manager.listAllTasks();
*/
    cout << "all tasks:" <<endl;
    manager.listAllTasks();
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
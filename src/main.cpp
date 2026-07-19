//entry point of the program
#include <iostream>
#include <limits>
#include "utils.h"

using namespace std;
int main(){
   /* int option = 0;
    Task task;
    string title;


    while(option != 6){
        displayMenu();

        cout << "Choose an option (1 - 6): " <<endl;
        while(!cin << option){ //getline()??
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please input a number " <<endl;
        }

     switch(option){
            case 1:
                //add task
                getline(cin,title);
                break;
            case 2:
                // edit task
                break;
            case 3:
               //remove task
                break;
            case 4:
               //Show list of tasks
                break;
            case 5:
               //Show completed list of tasks
                break;
            default:
                break; 
        }
    }

    cout << "Goodbye!" <<endl;
    */

    Task t1;
    t1.setId(1);

    cout << t1.getId() << endl;
    t1.setTitle("Buy groceries");
    t1.setIsCompleted(false);
    t1.setPriority(2);
    t1.setDueDate("2026-07-20");

    cout << t1 <<endl;
    
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
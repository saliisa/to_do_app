#include "validators.hpp"


bool validateTitle(std::string title){
   return !title.empty();
}

bool validatePriority(std::string priority){ 
    //or is it better with
    // return priority == "1" ||  priority == "2" ||  priority == "3" ;


    if(priority.empty()){
        return false;
    }

    for(char c : priority){
        if(!isdigit(c)){
            return false;
        }
    }

    int p = stoi(priority);
    return p >= 1 && p<=3;
}

bool checkLeapYear(int year){
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0){
        return true;
    }
    return false;
}

bool validateDate(std::string date){

    if(!date.empty()){
        if(date.size() == 10){
            if(date[4] == '-' && date[7] == '-'){
                std::string yearStr = date.substr(0,4);
                std::string monthStr = date.substr(5,2); //substr(posiition, length)
                std::string dayStr = date.substr(8,2);

                int year = stoi(yearStr);
                int month = stoi(monthStr);
                int day = stoi(dayStr);

                if(year > 0 ){
                    if(month > 0 && month <= 12){
                        if(day > 0 && day <= 31){
                            if(month == 2){
                                if(checkLeapYear(year) == true && (day >= 28 && day < 30)){
                                    return true;
                                } else if(checkLeapYear(year) == false && day < 29){
                                    return true;
                                }else{
                                    return false;
                                }
                            }  
                            
                            if((month == 4 || month == 6 || month == 9 || month == 11) && day > 30){
                                return false;
                            }
                            return true;
                        }
                    }

                }
            }
            
        }
        
    }
    return false;

}

bool validateStatus(std::string status){
    return status == "0" || status == "1";
}


bool validateInt(int value, int min, int max){
    return value >= min && value <= max;
}
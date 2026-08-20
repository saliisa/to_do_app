# To Do App in C++

## Project Plan (Work in Progress)

### Implementation
#### Stage 1: Console Application
The first stage would be to create a console "To-Do" application
Focus is on making the program work
- Classes
- File handling
- Algorithms
- Program structure


Project Structure:
- main.cpp --> entry point for the program
- Task.h --> attribute and method declaration for a task
- Task.cpp --> task behaviour
- TaskManager.h --> attribute and method declaration for managing tasks
- TaskManager.cpp --> task manager behaviour 
- tasks.json --> save data into json file; database


#### Stage 2: Separating the Logic
Then I would separate the logic 

Architecture:

```
       CLI

        ↓

    TaskManager

        ↓

    File Storage

```


#### Stage 3: Save data to Json file

- Using **nlohmann/json** `json.hpp` to save tasks into json format

Example:
```
[
    {
        "title":"Buy milk",
        "completed":false,
        "priority":3
    }
]
```

#### Stage 4: SQL database
Replace JSON files with a proper SQL database (SQLite or PostgreSQL)
Introducing:
- Persistent storage
- Querying
- Better scalability

#### Stage 5: Add a GUI
GUI library:
- QT

GUI goals:
- Task list display
- Buttons for add/edit/delete
- Visual indicators for priority, categories, etc.

#### Stage 6: Testing
Writing test cases for:
- Task logic
- TaskManager operations
- File/database interactions

#### Stage 7: Better Features
Add:
- Categories
- Due dates
- Priority
- Search
- Tags
- Sorting
- Dark mode
- Notifications


#### Stage 8: Networking

Architecture:

```
        GUI

        ↓

        REST API

        ↓

        Database


```

Now tasks can sync.
- Example:
     - POST /tasks
    - GET /tasks
    - DELETE /tasks/5


#### Stage 9: Backend

Write the backend in:
- C++
- Go
- Python
- Java


Architecture:
```
        Qt App

        ↓

        HTTP

        ↓

        REST Server

        ↓

        SQL

```


#### Stage 10: Hosting

You can deploy the backend on:
- a VPS running Linux,
- a cloud VM,
- or a small home server if you just want to learn.

The Qt application simply connects to your server's API.


Architecture:
```
        Qt App

        ↓

        Internet

        ↓

        Cloud Server

        ↓

        Database

```


#### Stage 11: Professional Features
Add:
- User accounts
- Login
- Password hashing
- Encryption
- Multiple task lists
- Team collaboration
- File attachments
- Undo/redo
- Automatic backups





## Final Architecture
By the end, your project might look like this:
```
        Qt Desktop App
                │
            HTTP Requests
                │
            C++ REST Server
                │
        Business Logic Layer
                │
        SQLite/PostgreSQL
``` 

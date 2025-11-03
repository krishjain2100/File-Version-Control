# **File Version Control System**

This project is a command-line application written in C++ that provides a simplified file version control system. It allows users to create files, manage their content, and track changes through a history of versions and snapshots. The system uses a tree-like data structure to manage file versions and utilizes a hash map and priority queues for efficient data retrieval and organization.

## **Features**

- **File Creation & Management:** Create, read, insert content into, and update files.
- **Snapshots:** Create "snapshots" of a file's content at a specific point in time, marked with a custom message. Snapshots are a key part of the version history.
- **Rollback:** Revert a file's active content to a previous version, either the immediate parent version or a specific version ID.
- **Version History:** View a chronological history of a file's snapshots.
- **File Metrics:**
  - List the most recently modified files.
  - List files with the largest number of versions

## **Requirements**

To compile and run this program, you will need to have a C++ compiler that supports the C++17 standard or a later version.

## **How to Compile and Run**

To compile the program, you will need a C++ compiler that supports C++17 or later. You can use a command like the following with g++:

```console
g++ -std=c++17 -o file_version_control assignment.cpp
```

Once compiled, you can run the executable:

```console
./file_version_control
```

The program will enter an interactive mode. Type END to exit the program.

## **Command-Line Interface**

The application accepts a variety of commands. Commands are case-sensitive.

| Command       | Description                                                   | Example Usage                                          |
| :------------ | :------------------------------------------------------------ | :----------------------------------------------------- |
| CREATE        | Creates a new file.                                           | CREATE my_document.txt                                 |
| READ          | Reads and prints the content of the active version of a file. | READ my_document.txt                                   |
| INSERT        | Appends content to a file.                                    | INSERT my_document.txt "new text"                      |
| UPDATE        | Replaces the entire content of a file.                        | UPDATE my_document.txt "new content"                   |
| SNAPSHOT      | Creates a snapshot of the active version.                     | SNAPSHOT my_document.txt "Initial commit"              |
| ROLLBACK      | Rolls back to the previous version or a specified version ID. | ROLLBACK my_document.txt or ROLLBACK my_document.txt 5 |
| HISTORY       | Displays the snapshot history of a file.                      | HISTORY my_document.txt                                |
| RECENT_FILES  | Lists the most recently modified files.                       | RECENT_FILES 5                                         |
| BIGGEST_TREES | Lists files with the largest version history.                 | BIGGEST_TREES 3                                        |

## **Data Structures**

The program utilizes the following data structures to implement its functionality:

- **TreeNode:** Represents a single version of a file. Each node stores content, a version ID, a timestamp, and a pointer to its parent version.
- **File:** Manages the entire version tree for a single file. It holds the root node and a pointer to the current active version.
- **HashMap:** A custom hash map stores files, mapping file names to File objects for quick lookup.
- **FilePriorityQueue:** A templated max-heap implementation used to keep track of the most recently modified files and the files with the biggest version trees.

##

## **Edge Cases and Error Handling**

The application includes robust error handling to manage various invalid commands and edge cases. Below is a list of common errors and their corresponding outputs:

| Condition                                                                              | Command Example                    | Output                                                                |
| :------------------------------------------------------------------------------------- | :--------------------------------- | :-------------------------------------------------------------------- |
| **Invalid command or insufficient arguments.**                                         | CREATE                             | Error: Invalid command or insufficient arguments.                     |
| **Insufficient arguments for commands requiring two arguments (INSERT, UPDATE, etc.)** | INSERT my_document.txt             | Error: Invalid command or insufficient arguments.                     |
| **Attempt to create a file that already exists.**                                      | CREATE my_document.txt             | Error: File with name 'my_document.txt' already exists.               |
| **File not found.**                                                                    | READ my_missing_file.txt           | Error: File 'my_missing_file.txt' not found.                          |
| **Attempt to SNAPSHOT an existing snapshot.**                                          | SNAPSHOT my_document.txt "New msg" | Error: The active version is already a Snapshot.                      |
| **Attempt to ROLLBACK a file with no history.**                                        | ROLLBACK my_document.txt           | Error: No previous version to rollback to for file 'my_document.txt'. |
| **Attempt to ROLLBACK to an invalid version ID.**                                      | ROLLBACK my_document.txt 99        | Error: Version ID 99 not found for file 'my_document.txt'.            |
| **Invalid version ID format.**                                                         | ROLLBACK my_document.txt "abc"     | Error: Invalid Version ID format.                                     |
| **Invalid number of files for RECENT_FILES or BIGGEST_TREES.**                         | RECENT_FILES \-5                   | Error: Number of files must be positive.                              |
| **Input string with a single space after the filename.**                               | INSERT my_document.txt             | Success: Appended content to file 'my_document.txt'.                  |

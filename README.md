# Time-Travelling File System

## Overview
This project implements a simplified, in-memory version control system inspired by Git. The system manages versioned files with support for branching and historical inspection using custom implementations of Trees, HashMaps, and Heaps.

## Project Structure

### Core Files

**Hash_Map.hpp**
- Contains implementations of hash maps for both integer and string keys
- `hashmap_int<T>`: Hash map with integer keys using simple modulo hashing
- `hashmap_string<T>`: Hash map with string keys using the djb2 hash function
- Provides O(1) average-time lookups for version management

**Heap.hpp**
- Implementation of a max heap data structure.
- Used for effeciently tracking system-wide metrics like most recently modified files and files with the most versions
- Contains operations for building heaps, inserting elements and popping the max element.

**Tree.hpp** 
- Implements the version tree structure for individual files
- Each tree node (`treenode`) represents a file version with content, timestamps, and parent-child relationships.
- The `tree` class manages the entire version history with operations for reading, inserting, updating, snapshotting, and rolling back
- Maintains an active version pointer and tracks all versions through the hash map


**System_Files.hpp**
- Main system coordinator that manages multiple files
- Each file is represented by a `file_info` structure containing the file name, version tree, and last modification time
- Implements all system-wide operations and coordinates between individual file trees
- Uses heaps to efficiently provide analytics about recent files and biggest trees

**IO_Parser.cpp**
- Main entry point and command parser
- Reads commands from standard input and sends them to appropriate system functions
- Supports all specified commands with proper input parsing and error handling


## Compilation
Run : 
```bash
chmod +x bash.sh
```
in the terminal followed by :
```bash
./bash.sh
```

### Execution
On successful compilation run :
```bash
./tt_file_system
```

The program will start and wait for commands from standard input. 

## Supported Commands

### File Operations
- `CREATE <filename>` - Creates a new file with empty content and initial snapshot
- `READ <filename>` - Displays the content of the currently active version
- `INSERT <filename> <content>` - Appends content to the file
- `UPDATE <filename> <content>` - Replaces the file's content entirely
- `SNAPSHOT <filename> <message>` - Creates an immutable snapshot with a message
- `ROLLBACK <filename> [versionID]` - Rolls back to specified version or parent version
- `HISTORY <filename>` - Shows chronological history of all snapshots

### System Analytics  
- `RECENT_FILES <num>` - Lists the most recently modified files
- `BIGGEST_TREES <num>` - Lists files with the most versions

### Exit
- `EXIT` - Terminates the program


## Error Handling

The system implements comprehensive error handling for various invalid operations and inputs:

### File Management Errors
- **Duplicate File Creation**: `CREATE filename` throws `runtime_error("already a file with same name exists!")` if a file with the same name already exists
- **Non-existent File Operations**: All file operations (`READ`, `INSERT`, `UPDATE`, `SNAPSHOT`, `ROLLBACK`, `HISTORY`) throw `runtime_error("no such file exists!")` when performed on files that don't exist

### Version Control Errors  
- **Invalid Version Rollback**: `ROLLBACK filename versionID` throws `runtime_error("This ID DNE!")` if the version ID is negative or greater than or equal to total versions
- **Parent Rollback Error**: `ROLLBACK filename` (without version ID) throws `runtime_error("No parent exists!")` if attempting to rollback from the root version which has no parent
- **Double Snapshot Error**: `SNAPSHOT filename message` throws `runtime_error("already a snapshot!")` if attempting to snapshot a version that is already marked as a snapshot

### Input Parsing and Validation Errors
- **Invalid ROLLBACK Format**: ROLLBACK command throws various errors:
  - `runtime_error("invalid command : filename required!!")` if no filename is provided
  - `runtime_error("Invalid version ID : must be a number!!")` if version ID contains non-numeric characters
  - `runtime_error("Invalid command format!!")` if more than 2 arguments are provided
- **Invalid Numeric Arguments**: 
  - `RECENT_FILES` throws `runtime_error("Invalid input : must be a number!!")` if the number argument contains non-numeric characters
  - `BIGGEST_TREES` throws `runtime_error("Invalid input : must be a number!!")` if the number argument contains non-numeric characters
- **Invalid Command**: Any unrecognized command throws `runtime_error("Invalid inp")`

### System Analytics Errors
- **Insufficient Files for RECENT_FILES**: `RECENT_FILES num` throws `runtime_error("these many files aren't even available!")` if requesting more files than exist in the system
- **Insufficient Files for BIGGEST_TREES**: `BIGGEST_TREES num` throws `runtime_error("these many files aren't even available!")` if requesting more files than exist in the system
- **Heap Overflow**: Max heap operations throw `runtime_error("Heap is empty!")` when attempting to pop from or get top of an empty heap



##  Example Session  

**Input**  
```txt
CREATE notes
INSERT notes Hello_World
SNAPSHOT notes "Initial_version"
INSERT notes Adding_more_content
SNAPSHOT notes "Extended_notes"
READ notes
HISTORY notes
RECENT_FILES 1
BIGGEST_TREES 1
EXIT
```

**Output (sample)**  
```txt
Adding_more_content
Version_ID : 2, Snapshotted Timestamp : Mon Sep  8 17:32:55 2025
, Message : "Extended_notes"
Version_ID : 1, Snapshotted Timestamp : Mon Sep  8 17:32:55 2025
, Message : "Initial_version"
Version_ID : 0, Snapshotted Timestamp : Mon Sep  8 17:32:55 2025
, Message : this is a snapshot!
Most recently modified files:
notes
Files with most versions:
notes (versions: 3)
Exiting the Loop. Programme Termninated
```

## Key Features and Semantics

**Version Management**
- Each file starts with version 0 as the root snapshot
- Version IDs are assigned sequentially and are unique per file
- Only snapshots are immutable; non-snapshot versions can be modified in-place

**Branching Support**
- Creating new versions from snapshots automatically creates child nodes
- The tree structure allows for complex branching and merging scenarios
- Active version tracking enables seamless navigation through version history

**Efficient Operations**
- Hash maps provide O(1) average lookup time for versions
- Heaps enable efficient sorting for system analytics
- Tree structure allows for natural parent-child version relationships

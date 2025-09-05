# Time-Travelling File System

## Overview
This project implements a simplified, in-memory version control system inspired by Git. The system manages versioned files with support for branching and historical inspection using custom implementations of Trees, HashMaps, and Heaps.

## Project Structure

### Core Files

**Hash_Map.hpp**
- Contains custom implementations of hash maps for both integer and string keys
- `hashmap_int<T>`: Hash map with integer keys using simple modulo hashing
- `hashmap_string<T>`: Hash map with string keys using the djb2 hash function
- Provides O(1) average-time lookups for version management

**Tree.hpp** 
- Implements the version tree structure for individual files
- Each tree node (`treenode`) represents a file version with content, timestamps, and parent-child relationships
- The `tree` class manages the entire version history with operations for reading, inserting, updating, snapshotting, and rolling back
- Maintains an active version pointer and tracks all versions through the hash map

**Heap.hpp**
- Custom implementation of a max heap data structure
- Used for efficiently tracking system-wide metrics like most recently modified files and files with the most versions
- Provides operations for building heaps, inserting elements, and extracting sorted results

**System_Files.hpp**
- Main system coordinator that manages multiple files
- Each file is represented by a `file_info` structure containing the file name, version tree, and last modification time
- Implements all system-wide operations and coordinates between individual file trees
- Uses heaps to efficiently provide analytics about recent files and biggest trees

**IO_Parser.cpp**
- Main entry point and command parser
- Reads commands from standard input and routes them to appropriate system functions
- Supports all specified commands with proper input parsing and error handling

## Compilation Instructions

To compile the project, run the following command in your terminal:

```bash
g++ -o file_system IO_Parser.cpp
```

Make sure all header files (Hash_Map.hpp, Tree.hpp, Heap.hpp, System_Files.hpp) are in the same directory as IO_Parser.cpp.

## Running the Program

After compilation, run the executable:

```bash
./file_system
```

The program will start and wait for commands from standard input. You can either type commands interactively or redirect input from a file.

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
- `exit` - Terminates the program

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

## Error Handling

The system handles various error conditions appropriately:
- Attempting to create duplicate files
- Operations on non-existent files
- Rolling back to invalid version IDs
- Taking snapshots of already snapshotted versions
- Requesting more files than available in analytics


## 🖥️ Example Session  

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
exit
```

**Output (sample)**  
```txt
Adding_more_content
Version_ID : 0, Created Timestamp : Fri Sep  5 23:36:21 2025
, Message : this is a snapshot!
Version_ID : 1, Created Timestamp : Fri Sep  5 23:36:21 2025
, Message : "Initial_version"
Version_ID : 2, Created Timestamp : Fri Sep  5 23:36:21 2025
, Message : "Extended_notes"
Most recently modified files:
notes
Files with most versions:
notes (versions: 3)
exiting the loop. programme termninated
```


## Technical Implementation Notes

- All data structures are implemented from scratch without using STL containers
- Memory management is handled through proper allocation and deallocation
- Timestamps use chrono library for precise time tracking
- String parsing handles edge cases with whitespace and empty inputs

The system provides a solid foundation for understanding version control concepts while demonstrating practical applications of fundamental data structures.

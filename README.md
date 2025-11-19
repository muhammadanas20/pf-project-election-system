# PF Online Election System

## Overview
This project is a **Console-Based Online Election System** developed in C.  
It allows **administrators** to manage students and candidates and enables **students** to log in and cast their vote securely.  

The system uses **file handling** to store student and candidate data persistently.

---

## Features

### Admin Panel
- Register new students (with random or custom password)
- Add new candidates
- View election results, including current winner
- Secure login with admin credentials

### Student Panel
- Student login using ID and password
- Cast vote for a candidate
- Prevent multiple voting
- View confirmation after successful voting

### Password Generation
- Passwords can be user-defined or auto-generated  
- Auto-generated passwords include the student’s name + ID + 4 random characters

---

## Project Structure
- `students.txt` – stores student information (ID, name, password, hasVoted)
- `candidate.txt` – stores candidate information (ID, name, votes)
- `main.c` – main program file containing all functions

---

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/pf-online-election-system.git
2.compile and run:
 ```bash
   gcc main.c -o main.exe
   ./main.exe



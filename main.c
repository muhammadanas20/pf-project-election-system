#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> 


#define clear_screen "cls"
#define students_file "students.txt"
#define candidate_file "candidate.txt"

const char ADMIN_USERNAME[] = "admin";
const char ADMIN_PASSWORD[] = "1234";

struct students{
    char name[50];
    char password[30];
    char ID[20];
    int hasvoted;
};

struct candidates{
    char name[50];
    int ID;
    int votes;
};

//function prototypes 
void adminLogin();
void studentLogin();
void addNewstudent();
void addCandidates();
void viewResult();
void voteCasting(struct students loggedInStudent);

//helper functions
char* passwordgenerator(char name[],char ID[]);
void pressEnter();



//main func
 int main(){
    srand(time(NULL));
   int choice;
   while(1){
    system(clear_screen);
    printf("---------------------------------------\n");
    printf("        ONLINE ELECTION SYSTEM         \n");
     printf("---------------------------------------\n");
     printf("1.Admin login menu\n");
     printf("2.Students login menu\n");
      printf("0.Exit\n");
      printf("Enter your choice:");
      if(scanf("%d",&choice) != 1){
          while(getchar() != '\n');
          continue;
      }
      switch(choice){
        case 1:
        adminLogin();
        break;
        case 2:
        studentLogin();
        break;
        case 0:
        printf("Program exiting......\n");
        exit(0);
        break;
        default:
        printf("Invalid Input choice!\n");
        pressEnter();
      }
     
   }
   return 0;
 }
void pressEnter(){
    printf("press Enter to continue...");
    while(getchar() != '\n');
    getchar();
}
char* passwordgenerator(char name[], char ID[]) {
    static char password[50]; 
    const char chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
    
    // name + id first
    sprintf(password, "%s%s", name, ID);

    int len = strlen(password);

    // Add 4 random characters
    for (int i = 0; i < 4; i++) {
        password[len + i] = chars[rand() % (sizeof(chars) - 1)];
    }

    password[len + 4] = '\0';
    return password;
}



void adminLogin(){
    int choice;
    char username[50];
    char password[30];
    system(clear_screen);
    printf("---------------------------------------\n");
    printf("          ADMIN LOGIN MENU             \n");
    printf("---------------------------------------\n");
    printf("Enter admin username:");
    scanf("%s", username);
    printf("Enter admin password:");
    scanf("%s",password);

    // admin username and password checker
    if(strcmp(username,ADMIN_USERNAME) != 0 || strcmp(password,ADMIN_PASSWORD) != 0){
        printf("Incorrect Admin crecidenrials.\n");
        pressEnter();
        return;
    }
    while(1){
    system(clear_screen);
    printf("---------------------------------------\n");
    printf("             ADMIN PANEL               \n");
    printf("---------------------------------------\n");
    printf("1. Register New students\n");
    printf("2. Add new Candidates\n");
    printf("3. View Election Results\n");
    printf("0. Logout\n");
    printf("Enter your choice:");
    // invalid input filter 
    if(scanf("%d", &choice) != 1){
        while(getchar() != '\n');
        continue;
    }
   switch(choice){
    case 1:
    addNewstudent();
    break;
    case 2:
    addCandidates();
    break;
    case 3:
    viewResult();
    break;
    case 0:
    printf("logging out.....");
    return;
    break;
    default:
    printf("Invalid choice.");
    pressEnter();
   }
}
}

void addNewstudent(){
    FILE* fp;
    struct students newStudent;
    fp = fopen(students_file,"ab");
    if (fp == NULL){
        printf("Error: Cannot open file %s\n", students_file);
        pressEnter();
        return;
    }
    system(clear_screen);
    printf("---------------------------------------\n");
    printf("         REGISTER NEW STUDENTS         \n");
    printf("---------------------------------------\n");
    while( getchar() != '\n');
    printf("Enter student ID:");
    fgets(newStudent.ID,sizeof(newStudent.ID),stdin);
    newStudent.ID[strcspn(newStudent.ID, "\n")] = 0;
    printf("Enter student name:");
    fgets(newStudent.name,sizeof(newStudent.name),stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0;
    int choice;
    printf("1.create your own password for students or 2.generate randomly:");
    scanf("%d",&choice);
    while(getchar() != '\n');
    switch(choice){
        case 1:
        printf("Enter :");
        fgets(newStudent.password,sizeof(newStudent.password),stdin);
        newStudent.password[strcspn(newStudent.password, "\n")] = 0;
        break;
        case 2:
        strcpy(newStudent.password, passwordgenerator(newStudent.name, newStudent.ID));
        break;
        default:
       printf("Invalid Input! Generating randomly.\n");
       strcpy(newStudent.password, passwordgenerator(newStudent.name, newStudent.ID));
    }

    newStudent.hasvoted = 0;//initially student didn't vote
    fwrite(&newStudent, sizeof(struct students), 1, fp);
    fclose(fp);
    printf("\nStudent '%s' registered successfully!\n", newStudent.name);
    printf("Password is: %s\n", newStudent.password);
    pressEnter(); 
}



void addCandidates(){
    system(clear_screen);
    struct candidates newcandidates;
    struct candidates temp;
    int max_id =0;
    FILE* fp;
    fp = fopen(candidate_file,"rb");
    if(fp != NULL){
        while(fread(&temp,sizeof(struct candidates),1,fp)){
            if(temp.ID> max_id){
                max_id = temp.ID;
            }
        }
        fclose(fp);
    }
    fp = fopen(candidate_file, "ab"); 
    if (fp == NULL) {
        printf("Error: Cannot open file for writing!\n");
        pressEnter();
        return;
    }
    newcandidates.ID = max_id + 1;
    newcandidates.votes = 0;

    system(clear_screen);
    printf("---------------------------------------\n");
    printf("          ADD NEW CANDIDATE            \n");
    printf("---------------------------------------\n");
    while(getchar() != '\n');
    printf("Enter candidate full name: ");
    fgets(newcandidates.name,sizeof(newcandidates.name),stdin);
    newcandidates.name[strcspn(newcandidates.name, "\n")] = 0;
    fwrite(&newcandidates,sizeof(struct candidates),1,fp);
    fclose(fp);
   printf("Candidate '%s' with ID %d successfully added!\n", newcandidates.name, newcandidates.ID);
   pressEnter();
}




 void studentLogin(){
      char studentID [20];
      char password[30];
      FILE* fp;
      int found = 0;
      struct students currentStudent;
      fp = fopen(students_file,"rb");
      if(fp == NULL){
        printf("Error: cannot open a file %s",students_file);
        pressEnter();
        return;
      }
      system(clear_screen);
      printf("---------------------------------------\n");
      printf("             STUDENT LOGIN             \n");
      printf("---------------------------------------\n");
      while(getchar() != '\n');
      printf("Enter student ID: ");
      scanf("%s", studentID);
      printf("Enter password: ");
      scanf("%s", password);
      while(fread(&currentStudent,sizeof(struct students),1,fp)){
        if(strcmp(currentStudent.ID,studentID) == 0  && strcmp(currentStudent.password,password) == 0 ){
            found = 1;
            break;
        }
      }
      fclose(fp);
      if(found){
        printf("Login sucessfull\n");
        if (currentStudent.hasvoted){
            printf("You already cast a vote!\nNothing changes happen again");
            pressEnter();
            return;
        }
        else{
             voteCasting(currentStudent);
             pressEnter();
        }
      }
      else{
        printf("Invalid student ID or Password\n");
        pressEnter();
        return;
      }
 }
 void voteCasting(struct students loggedInStudent){
       struct candidates candidate;
       FILE* fp;
       int voteID;;
       int foundcandidate = 0;
       system(clear_screen);
       printf("---------------------------------------\n");
       printf("          VOTE CASTING                 \n");
       printf("---------------------------------------\n");
       printf("Hello %s choose a candidate.\n",loggedInStudent.name);

       fp = fopen(candidate_file,"rb");
       if(fp == NULL){
        printf("Error: cannot open a %s file.\n",candidate_file);
        pressEnter();
        return;
       }
       printf("---------------------------------------\n");
       printf("| ID  | Candidate Name       |\n");
       printf("---------------------------------------\n");
       while(fread(&candidate,sizeof(struct candidates),1,fp)){
        printf("| %-3d | %-20s |\n", candidate.ID, candidate.name);
       }
       fclose(fp);
       printf("---------------------------------------\n");
       printf("Enter a ID of a Candidate :");
       scanf("%d",&voteID);
       fp = fopen(candidate_file,"r+b");
       if (fp == NULL) {
        printf("Error processing vote.\n");
        pressEnter();
        return;
    }
    while(fread(&candidate,sizeof(struct candidates),1,fp)){
        if(candidate.ID == voteID){
            candidate.votes++;
            foundcandidate = 1;
            fseek(fp, -(long)sizeof(struct candidates), SEEK_CUR);
            fwrite(&candidate, sizeof(struct candidates), 1, fp);
            break;
        }
       
    }
    fclose(fp);
    if (!foundcandidate) {
        printf("\nInvalid Candidate ID. Your vote was not cast.\n");
        pressEnter();
        return;
    }
    FILE* fpstudent;
    fpstudent = fopen(students_file,"r+b");
    if(fpstudent == NULL ){
        printf("Error finalizing vote.\n");
        pressEnter();
        return;
    }
    struct students tempstudent;
    while(fread(&tempstudent,sizeof(struct students),1,fpstudent)){
        if(strcmp(tempstudent.ID,loggedInStudent.ID) == 0){
            tempstudent.hasvoted = 1;
            fseek(fpstudent, - (long)sizeof(struct students), SEEK_CUR);
            fwrite(&tempstudent, sizeof(struct students), 1, fpstudent);
            break;
        }
    }
    fclose(fpstudent);
    printf("\nThank you! Your vote has been cast successfully.\n");
    pressEnter();
 }
void viewResult(){
    FILE* fp;
    struct candidates candidate;
    struct candidates winner;
    int total_votes = 0;
    int max_votes = -1;
    int winner_found = 0;
    system(clear_screen);
    printf("---------------------------------------\n");
    printf("             ELECITON RESULT           \n");
    printf("---------------------------------------\n");
    fp = fopen(candidate_file,"rb");
    if(fp == NULL ){
        printf("No candidate found.please add a candidates first\n");
        pressEnter();
        return;
    }

    printf("Candidates List\n");
    printf("---------------------------------------\n");
    printf("| ID  | Name                 | Votes   |\n");
    printf("---------------------------------------\n");
    while(fread(&candidate,sizeof(struct candidates),1,fp)){
        printf("| %-3d | %-20s | %-7d |\n",candidate.ID,candidate.name,candidate.votes);
        total_votes += candidate.votes;
        if(candidate.votes > max_votes){
            max_votes = candidate.votes;
            winner = candidate;
            winner_found = 1;
        }
    }
    fclose(fp);
    printf("---------------------------------------\n");
    if(total_votes == 0){
        printf("No votes is being cast\n");
        pressEnter();
        return;
    }
    else{
        printf("Total vote Cast: %d\n",total_votes);
        if(winner_found){
        printf("Current winner is %s , ID %d with %d votes\n",winner.name,winner.ID,max_votes);
        pressEnter();
        }
        else if (winner_found == 0){
            printf("Two or more candidate have same number of votes:\n");
            pressEnter();
        }
    }
}
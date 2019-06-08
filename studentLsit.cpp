//inports
#include <iostream>
#include <vector>
#include <string.h>
#include <iomanip>
#include <stdlib.h>     /* atoi */



//including the namespace
using namespace std;

struct Student{//creates a struct that has a first and last name, an int, and a gpa
  char firstName[50];
  char lastName[50];
  int id;
  float gpa;
  Student* next = NULL;
};
//function init
Student* ADD();
void HASHADD(int, Student*, Student* students[]);
void PRINT(int size, Student* students[]);
void DELETE(int size, Student* students[], int id);

int CHAINL(Student* students[], int index){
  int count = 0;
  if(students[index] == NULL){
    return count;
  }
  else{
    count++;
    Student* current = students[index];
    while(current->next != NULL){
      count++;
      current = current->next;
    }
  }
  return count;
}

int HASH(int size, Student* str){
  int hash = 0;
  int index;
  index = strlen(str->firstName);
  for(int i = 0; i < index; i++){
    hash += (int)str->firstName[i];
  }
  index = strlen(str->lastName);
  for(int i = 0; i < index; i++){
    hash += (int)str->lastName[i];
  }
  return hash % size;
}

int PHASH(int size, Student* str){
  int hash = 0;
  int index;
  index = strlen(str->firstName);
  for(int i = 0; i < index; i++){
    hash += (int)str->firstName[i];
  }
  index = strlen(str->lastName);
  for(int i = 0; i < index; i++){
    hash += (int)str->lastName[i];
  }
  return hash;
}

void clear(int size, Student* students[]){
  for(int i = 0; i < size; i++){
    students[i] = NULL;
  }
}

int main()//main method
{
  char names[10][10] = {"John","Sara","Olivia","Ava","Matt","Molly","Alex","Brendon","Andrew","Sally"};
  char lastNames[10][10] = {"Jo","Sra","Olvia","Av","Mat","Mlly","Lex","Brndn","Anre","Sly"};
  int maxID = 100000;
  bool exit = false;//determines if the code should continue running
  char input[50];// input for the add print delete exit
  int tableSize = 100;
  Student** students;//vector of student pointers
  students = new Student*[tableSize];
  for(int i = 0; i < tableSize; i++){
    students[i] = NULL;
  }
  int idInput;// input for delete
  int index = 0;
  while(!exit){// main running loop
    cout << "Do you want to add, rand, print, delete, or exit?" << endl;
    cin.get(input, 7);//getting 7 characters from the cin
    cin.clear();
    cin.ignore(100000, '\n');
    if(strcmp(input, "add") == 0){//if the input is add...
      Student* stud = ADD();//run ADD function and put he output into students
      //students[HASH(100, stud->firstName)] = stud;
      students[index] = stud;
      index++;
    }
	else if(strcmp(input, "rand") == 0){//if the input is print...
		cout << "How many students? : ";
    cin >> input;//what is first name?
		cin.clear();
		cin.ignore(100000, '\n');
		int num = (atoi(input));
		for(int i = 0; i < num; i++){
			Student* newStud = new Student();//alocate to heap
			int b = rand() % 10;
      strcpy(newStud->firstName, names[b]);//what is first name?
      b = rand() % 10;
  		strcpy(newStud->lastName, lastNames[b]);//what is last name?
  		newStud->id = maxID;//wthat is the student id?
  		newStud->gpa = rand() % 1000 / 200.0;//what is the gpa
      HASHADD(tableSize, newStud, students);
      maxID++;
		}
	}
    else if(strcmp(input, "print") == 0){//if the input is print...
      PRINT(tableSize, students);//run print function
    }
    else if(strcmp(input, "delete") == 0){//if input is delete...
      cout << "You entered the Delete queue" << endl;
      cout << "Enter student id:";
      cin >> idInput;//get the id you want to delete
      cin.clear();
      cin.ignore(100000, '\n');
      DELETE(tableSize, students, idInput);//run delete function with input if adress of students
    }
    else if(strcmp(input, "exit") == 0){//if input is exit...
      exit = true;//change the value of exit to true to stop the program
    }
    else {
      cout << "Sorry I dont know what you mean" << endl;
    }
  }
  return 0;
}

void HASHADD(int tableSize, Student* newStud, Student* students[]){
  int ind = HASH(tableSize, newStud); //gets hash of function
  if(students[ind] == NULL){//if the value at hash is null
   students[ind] = newStud;//put at hash
  }
  else{//if not empty
    /*if(PHASH(tableSize, students[ind]) == PHASH(tableSize, newStud)){//if the value at hash is same as input 
      strcat(newStud->lastName, " 2");//add the string " 2" to the end of last name
      HASHADD(tableSize, newStud, students);//add that to the list
    }
    /*else if(CHAINL(students, ind) < 2){*/
    Student* current = students[ind];
    while(current->next != NULL){
      current = current->next;
    }
    /*students[ind]*/current->next = newStud;
    cout << current->next->firstName << " " << current->next->lastName << " placed before " << current->firstName << " " << current->lastName << endl;

          //cout << students[ind]->next->firstName << " " << students[ind]->next->lastName << " placed before " << students[ind]->firstName << " " << students[ind]->lastName << endl;
  }
  /*      else{
          Student** OLD;
          OLD = students;
          tableSize = tableSize*2;
          Student* NEW[tableSize];//vector of student pointers
          clear(tableSize, NEW);
          for(int i = 0; i < tableSize / 2; i++){//iterates through the student vector
            Student* current = students[i];
            while(current != NULL){
              HASHADD(tableSize, current, NEW);
              current = current->next;
            }
          }
          students = NEW;
        }*/
}

Student* ADD(){//add function
  cout << "You entered Add queue" << endl;
  Student* newStud = new Student();//alocate to heap
  cout << "Enter first name: ";
  cin >> newStud->firstName;//what is first name?
  cin.clear();
  cin.ignore(100000, '\n');
  cout << "Enter last name: ";
  cin >> newStud->lastName;//what is last name?
  cin.clear();
  cin.ignore(100000, '\n');
  cout << "Enter id: ";
  cin >> newStud->id;//wthat is the student id?
  cin.clear();
  cin.ignore(100000, '\n');
  cout << "Enter gpa: ";
  cin >> newStud->gpa;//what is the gpa
  cin.clear();
  cin.ignore(100000, '\n');
  return newStud;//return a student pointer
}
void PRINT(int size, Student* students[]){//print function
  cout << "You entered the Print queue" << endl;
  for(int i = 0; i < size; i++){//iterates through the student vector
    //following lines print out the students vector
    Student* current = students[i];
    while(current != NULL){
      cout << "Student name: " << current->firstName << " " << current->lastName << endl;
      cout << "Student ID: " << current->id << endl;
      cout << "Student GPA: " << fixed << setprecision(2) << current->gpa << endl;
      cout << "Student Hash: " << HASH(size, current) << endl;
      cout << "Index: " << i << endl;
      cout << endl;
      current = current->next;
    }
  }
}

void DELETE(int size, Student* students[], int id){
  for(int i = 0; i < size; i++){//iterates through the student vector
    Student* current = students[i];
    while(current != NULL){
        if(current->id == id){//if the id of the student is eaqual to the one priviously entered...
            Student* poop = students[i];
            students[i] = NULL;//delete the memory of it in heap
            delete poop;
            return;//return if found
        }
        current = current->next;
    }
  }
  cout << "Invalid ID" << endl;//if the function reaches here the id was invalid.
}
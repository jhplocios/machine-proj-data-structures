#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fname_size 31
#define lname_size 41
#define bdate_size 9
#define color_size 16

typedef struct friend {
  char *firstname;
  char *lastname;
  char *birthdate;
  int age;
  char gender;
  char *color; 
} Friend;

int list_size = 2;
Friend *friends_list;
int total_friends = 0;

void menu();
void instructions();
void add_friend();
void delete_friend();
void display_friends();
void invalid_input(); 

int main() 
{
  friends_list = (Friend*) malloc(list_size*sizeof(Friend));

  if (friends_list == NULL) 
  {
    printf("Error! memory not allocated.");
    exit(0);
  }

  menu();

  if (friends_list) free(friends_list);
  return 0;
}

void add_friend()
{  
  Friend temp;
  temp.firstname = (char*) malloc(fname_size*sizeof(char));
  temp.lastname = (char*) malloc(lname_size*sizeof(char));
  temp.birthdate = (char*) malloc(bdate_size*sizeof(char));
  temp.color = (char*) malloc(color_size*sizeof(char));

  // system("clear");
  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", temp.firstname);
  printf("Enter last name: ");
  scanf(" %[^\n]s", temp.lastname);
  printf("Enter birth date (MMDDYYYY): ");
  scanf(" %[^\n]s", temp.birthdate);

  char year[4];
  int c = 0;
  while (c < 4) 
  {
    year[c] = temp.birthdate[4+c];
    c++;
  }
  int byear;
  sscanf(year, "%d", &byear);
  temp.age = 2019 - byear;

  printf("Enter gender (M/F): ");
  scanf(" %c", &temp.gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", temp.color);
  
  if (total_friends == list_size) 
  {
    friends_list = realloc(friends_list, list_size*2 * sizeof(Friend));
    list_size *= 2;
    printf("\nreallocating memory, new size of list is %d\n", list_size);
  }
  // system("clear");
  printf("\nSuccessfully added %s\n\n", temp.firstname);

  friends_list[total_friends] = temp;
  total_friends++;

  int input;
  printf("1 - Add more friends\n");
  printf("2 - Back to main menu\n");
  printf("Enter action: ");
  scanf("%d", &input);

  if (input == 1) 
  {
    add_friend();
  } 
  else if (input == 2) 
  {
    menu();
  } 
  else 
  {
    printf("\nInvalid input!\n\n");
    menu();
  }
}

void delete_friend()
{
  char *temp = (char*) malloc(50*sizeof(char));
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", temp);

  int index = -1;
  for (int i=0; i<total_friends; ++i)
  {
    if (strcmp(friends_list[i].lastname, temp) == 0)
    {
      index = i;
    }
  }

  int confirm_delete, delete_another;
  if (index != -1)
  {
    printf("delete %s?\n", friends_list[index].lastname);
    printf("1 - yes\n");
    printf("2 - cancel\n");
    printf("Enter action: ");
    scanf("%d", &confirm_delete);

    if (confirm_delete == 1)
    {
      for (int i=index; i<total_friends-1; ++i)
      {
        friends_list[i] = friends_list[i+1];
      }
      total_friends--;
      printf("\nsuccessfully deleted %s\n", temp);
      menu();
    }
    else
    {
      printf("1 - delete another friend\n");
      printf("2 - back to main menu\n");
      printf("Enter action: ");
      scanf("%d", &delete_another);

      if (delete_another == 1)
      {
        delete_friend();
      }
      else 
      {
        menu();
      }
    }
  } 
  else 
  {
    printf("friend not found\n\n");
    printf("1 - delete another friend\n");
    printf("2 - back to main menu\n");
    printf("Enter action: ");
    scanf("%d", &delete_another);

    if (delete_another == 1)
    {
      delete_friend();
    }
    else 
    {
      menu();
    }
  }
}

void display_friends()
{
  if (total_friends == 0) 
  {
    // system("clear");
    printf("\nNo friends yet.\n");
  } else 
  {
    // system("clear");
    printf("\nFriends:\n\n");
    for (int i=0; i < total_friends; i++)
    {
      printf("friend #%d\n", i+1);
      printf("first name: %s\n", friends_list[i].firstname);
      printf("last name: %s\n", friends_list[i].lastname);
      printf("birthdate: %s\n", friends_list[i].birthdate);
      printf("age: %d\n", friends_list[i].age);
      printf("gender: %c\n", friends_list[i].gender);
      printf("favourite color: %s\n\n", friends_list[i].color);
    }
  }
  menu();
}

void menu() 
{
  int input;
  instructions();
    
  scanf("%d", &input);
  switch (input)
  { 
    case 1:
      add_friend();
      break;
    case 2:
      delete_friend();
      break;
    case 3:
      printf("update");
      break;
    case 4:
      display_friends();
      break;
    case 5:
      break;
    default:
      invalid_input();
  }
}

void instructions()
{ 
  // system("clear");
  printf("\nMain menu:\n\n");
  printf("1 - Add a friend\n");
  printf("2 - Delete a friend\n");
  printf("3 - Update friend's info\n");
  printf("4 - Display friends\n");
  printf("5 - Exit program\n\n");
  printf("Enter action: ");
}

void invalid_input() 
{
  // system("clear");
  printf("Invalid input!\n-----\n");
  menu();
}
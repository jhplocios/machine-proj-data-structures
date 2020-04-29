#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum attributes {
  fname_a,
  lname_a,
  bdate_a,
  age_a,
  gender_a,
  color_a
};

typedef struct dbData_t { 
  void *data;
} dbData, *pdbData;

dbData db[10][6];

int fcount = 0;

void Initialize();
void Menu();
void Instructions();
void InvalidInput();
void AddMore();

int main()
{  
  Menu();
  return 0;
}

void AddFriend()
{
  char *temp = (char*) malloc(31*sizeof(char));
  db[fcount][fname_a].data = (char*) malloc(31*sizeof(char));

  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", temp);

  memcpy(db[fcount][fname_a].data, temp, 31*sizeof(char));
  printf("Copied string is %s\n", &(*(db+fcount)+fname_a)->data); 


  // printf("Enter last name: ");
  // scanf(" %[^\n]s", friend_table[lname_a][total_friend]);
  // printf("Enter birth date (MMDDYYYY): ");
  // scanf(" %[^\n]s", friend_table[bdate_a][total_friend]);

  // char year[4];
  // int c = 0;
  // while (c < 4) 
  // {
  //   year[c] = friend_table[bdate_a][total_friend][4+c];
  //   c++;
  // }
  // int byear;
  // scanf(year, "%d", &byear);
  // friend_table[age_a][total_friend] = 2019 - byear;

  // printf("Enter gender (M/F): ");
  // scanf(" %c", friend_table[gender_a][total_friend]);
  // printf("Enter favourite color: ");
  // scanf(" %[^\n]s", friend_table[color_a][total_friend]);

  fcount++;
  printf("\nSuccessfully added %p\n\n", db[fcount][fname_a].data);
  free(temp);
  AddMore();
}

void AddMore()
{
  int input;
  printf("1 - Add more friends\n");
  printf("2 - Back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &input);

  if (input == 1) 
  {
    AddFriend();
  } 
  else if (input == 2) 
  {
    Menu();
  } 
  else 
  {
    printf("\nInvalid input!\n\n");
    AddMore();
  }
}

void DisplayFriends()
{
  printf("\nFriends:\n\n");

  for (int i=0; i<fcount; i++)
  {
    printf("%p\n", db[i][fname_a].data);
  }

  // while (fread(ptr, sizeof(friend_t), 1, fp1) == 1) 
  // {
  //   printf("%s\n", ptr->firstname);
  //   printf("%s\n", ptr->lastname);
  //   printf("%s\n", ptr->birthdate);
  //   printf("%d\n", ptr->age);
  //   printf("%c\n", ptr->gender);
  //   printf("%s\n\n", ptr->color);
  // }

  Menu();
}

void Menu() 
{
  int input;
  Instructions();
    
  scanf("%d", &input);
  switch (input)
  { 
    case 1:
      AddFriend();
      break;
    case 2:
      // delete_friend();
      break;
    case 3:
      // update_friend();
      break;
    case 4:
      DisplayFriends();
      break;
    case 5:
      break;
    default:
      InvalidInput();
  }
}

void Instructions()
{ 
  printf("\nMain menu:\n\n");
  printf("1 - Add a friend\n");
  printf("2 - Delete a friend\n");
  printf("3 - Update friend's info\n");
  printf("4 - Display friends\n");
  printf("5 - Exit program\n\n");
  printf("Enter action: ");
}

void InvalidInput() 
{
  printf("Invalid input!\n\n");
  Menu();
}
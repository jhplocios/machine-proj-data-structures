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

typedef struct {
  char *s;
  int n;
  char c;
  int count;
} data;

typedef struct {
  data **ptr;
  int length;
  int count;
} matrix;

matrix table;

void Initialize();
void Menu();
void Instructions();
void InvalidInput();
void AddMore();
void DeleteMore();
int ConfirmDelete();
void UpdateMore();

int main()
{  
  table.length = 2;
  table.ptr = (data**) malloc(table.length*sizeof(data));
  int i;
  for (i=0; i<6; i++)
  {
    *(table.ptr + i) = (data*) malloc(6*sizeof(data));
  } 

  Menu();

  for (i=0; i<table.count; i++)
  {
    free(*(table.ptr + i));
  }  
  free(table.ptr);
  return 0;
}

void AddFriend()
{
  char fname[31];
  char lname[41];
  int bdate;
  char gender;
  char color[16];

  table.ptr[table.count][fname_a].s = (char*) malloc(31*sizeof(char));
  table.ptr[table.count][lname_a].s = (char*) malloc(41*sizeof(char));
  table.ptr[table.count][color_a].s = (char*) malloc(16*sizeof(char));

  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", fname);
  printf("Enter last name: ");
  scanf(" %[^\n]s", lname);
  printf("Enter birth date (MMDDYYYY): ");
  scanf(" %d", &bdate);
  // compute age
  int year = bdate % 10000;
  printf("Enter gender (M/F): ");
  scanf(" %c", &gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", color);

  if (table.length == table.count) 
  {
    table.ptr = realloc(table.ptr, table.length*2*sizeof(data));
    table.length *= 2;
    printf("\nreallocating memory, new size of table is %d\n", table.length);

    for (int i=table.count+1; i<table.length; i++) 
    {
      *(table.ptr + i) = (data*) malloc(6*sizeof(data));
    }
  }

  strcpy(table.ptr[table.count][fname_a].s, fname);
  strcpy(table.ptr[table.count][lname_a].s, lname);
  table.ptr[table.count][bdate_a].n = bdate;
  table.ptr[table.count][age_a].n = 2019 - year;
  table.ptr[table.count][gender_a].c = gender;
  strcpy(table.ptr[table.count][color_a].s, color);

  printf("\nSuccessfully added %s\n\n", table.ptr[table.count][fname_a].s);

  table.count++;
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
    AddFriend();
  else if (input == 2) 
    Menu();
  else 
  {
    printf("\nInvalid input!\n\n");
    AddMore();
  }
}

void SearchByName(int *index)
{
  char lname[41];
  char fname[31];

  printf("\nEnter last name: ");
  scanf(" %[^\n]s", lname);
  printf("Enter first name: ");
  scanf(" %[^\n]s", fname);

  for (int i=0; i<table.count; ++i)
  {
    if (strcmp(table.ptr[i][lname_a].s, lname) == 0)
      if (strcmp(table.ptr[i][fname_a].s, fname) == 0)
      {
        *index = i;
        break;
      }
  }
}

void DeleteFriend()
{
  int friend_index = -1;
  int confirm, delete_another;

  SearchByName(&friend_index);

  if (friend_index != -1)
  {
    printf("\ncontinue deleting?\n");
    confirm = ConfirmDelete();

    if (confirm == 1)
    {
      for (int i=friend_index; i<table.count-1; ++i)
      {
        table.ptr[i] = table.ptr[i+1];
      }
      table.count--;
      printf("\nsuccessfully deleted a friend\n\n");
      
      DeleteMore();
    }
    else if (confirm == 2)
      DeleteMore();
    else 
    {
      printf("\nInvalid input!\n\n");
      DeleteMore();
    }
  } 
  else 
  {
    printf("\nfriend not found\n\n");
    DeleteMore();
  }
}

int ConfirmDelete()
{
  int u_input;
  printf("1 - yes\n");
  printf("2 - cancel\n\n");
  printf("Enter action: ");
  scanf("%d", &u_input);
  return u_input;
}

void DeleteMore()
{
  int delete_another;
  printf("1 - delete another friend\n");
  printf("2 - back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &delete_another);
  
  if (delete_another == 1)
    DeleteFriend();
  else if (delete_another == 2) 
    Menu();
  else 
  {
    printf("\nInvalid input!\n\n");
    DeleteMore();
  }
}

void UpdateFriend()
{
  int friend_index = -1;
  int confirm_update, update_another;

  SearchByName(&friend_index);

  if (friend_index != -1)
  {
    printf("\nwhat will you update?\n");
    printf("1 - last name\n");
    printf("2 - first name\n");
    printf("3 - birtdate\n");
    printf("4 - gender\n");
    printf("5 - favourite color\n");
    printf("6 - cancel\n\n");
    printf("Enter action: ");
    scanf("%d", &confirm_update);

    if (confirm_update == 1)
    {
      char lname[41];
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", lname);
      strcpy(table.ptr[friend_index][lname_a].s, lname);
      printf("\nUpdated last name to %s\n\n", lname);
    }
    else if (confirm_update == 2)
    {
      char fname[31];
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", fname);
      strcpy(table.ptr[friend_index][fname_a].s, fname);
      printf("\nUpdated first name to %s\n\n", fname);
    } 
    else if (confirm_update == 3)
    {
      int bdate; 
      printf("\nEnter new birthdate (MMDDYYYY): ");
      scanf(" %d", &bdate);
        // compute age
      int year = bdate % 10000;
      table.ptr[friend_index][bdate_a].n = bdate;
      table.ptr[friend_index][age_a].n = 2019 - year;
      printf("\nUpdated birthdate to %d\n\n", bdate);
    } 
    else if (confirm_update == 4)
    {
      if (table.ptr[friend_index][gender_a].c == 'M')
        table.ptr[friend_index][gender_a].c = 'F';
      else 
        table.ptr[friend_index][gender_a].c = 'M';

      printf("\nUpdated gender\n");
    }
    else if (confirm_update == 5)
    {
      char color[16];
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", color);
      strcpy(table.ptr[friend_index][color_a].s, color);
      printf("\nUpdated favourite color to %s\n\n", color);
    }
    else if (confirm_update == 6)
      UpdateMore();
    else 
    {
      printf("\nInvalid input!\n\n");
      UpdateMore();
    }

    UpdateMore();
  } 
  else 
  {
    printf("\nfriend not found\n\n");
    UpdateMore();
  }
}

void UpdateMore()
{
  int update_another;
  printf("1 - update another friend\n");
  printf("2 - back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &update_another);
  
  if (update_another == 1)
    UpdateFriend();
  else if (update_another == 2) 
    Menu();
  else 
  {
    printf("\nInvalid input!\n\n");
    UpdateMore();
  }
}

void DisplayFriends()
{
  if (table.count == 0) 
    printf("\nNo friends yet.\n");
  else 
  {
    printf("\nFriends:\n\n");
    for (int i=0; i<table.count; i++)
    {
      printf("friend #%d\n", i+1);
      printf("first name: %s\n", table.ptr[i][fname_a].s);
      printf("last name: %s\n", table.ptr[i][lname_a].s);
      printf("birthdate: %d\n", table.ptr[i][bdate_a].n);
      printf("age: %d\n", table.ptr[i][age_a].n);
      printf("gender: %c\n", table.ptr[i][gender_a].c);
      printf("favourite color: %s\n\n", table.ptr[i][color_a].s);
    }
  }
  Menu();
}

void swap(data *x,data *y)
{
  data temp = *x;
  *x = *y;
  *y = temp;
}

void BubbleSort() 
{
  int i,j,flag=0;
  for(i=0; i<table.count-1; i++)
  {
    flag=0;
    for(j=0; j<table.count-i-1; j++)
    {
      if(table.ptr[j][lname_a].s[0] > table.ptr[j+1][lname_a].s[0])
      {
        swap(&table.ptr[j][lname_a], &table.ptr[j+1][lname_a]);
        swap(&table.ptr[j][fname_a], &table.ptr[j+1][fname_a]);
        swap(&table.ptr[j][bdate_a], &table.ptr[j+1][bdate_a]);
        swap(&table.ptr[j][age_a], &table.ptr[j+1][age_a]);
        swap(&table.ptr[j][gender_a], &table.ptr[j+1][gender_a]);
        swap(&table.ptr[j][color_a], &table.ptr[j+1][color_a]);
        flag=1;
      }
      else if (table.ptr[j][lname_a].s[0] == table.ptr[j+1][lname_a].s[0])
        if (table.ptr[j][lname_a].s[1] > table.ptr[j+1][lname_a].s[1]) 
        {  
          swap(&table.ptr[j][lname_a], &table.ptr[j+1][lname_a]);
          swap(&table.ptr[j][fname_a], &table.ptr[j+1][fname_a]);
          swap(&table.ptr[j][bdate_a], &table.ptr[j+1][bdate_a]);
          swap(&table.ptr[j][age_a], &table.ptr[j+1][age_a]);
          swap(&table.ptr[j][gender_a], &table.ptr[j+1][gender_a]);
          swap(&table.ptr[j][color_a], &table.ptr[j+1][color_a]);
          flag=1;
        }
    }
    if(flag==0)
      break;
  }

  printf("\nSuccessfully sorted your friend's list\n");
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
      DeleteFriend();
      break;
    case 3:
      UpdateFriend();
      break;
    case 4:
      DisplayFriends();
      break;
    case 5:
      BubbleSort();
      break;
    case 6:
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
  printf("5 - Sort friends\n");
  printf("6 - Exit program\n\n");
  printf("Enter action: ");
}

void InvalidInput() 
{
  printf("\nInvalid input!\n");
  Menu();
}
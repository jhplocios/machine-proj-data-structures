#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define fname_size 31
#define lname_size 41
#define bdate_size 9
#define color_size 16
#define file_path "friends.txt"
#define temp_path "temp.txt"

FILE *fp, *fp1;

typedef struct {
  char fname[31];
  char lname[41];
  int bdate;
  int age;
  char gender;
  char color[16]; 
} friend_t;

char *firstname;
char *lastname;
char *birthdate;
int age;
char gender;
char *color; 

void Menu();
void Instructions();
void AddFriend();
void DeleteFriend();
void UpdateFriend();
void DisplayFriends();
void InvalidInput();
void AddMore();
void DeleteMore();
int ConfirmDelete();
void UpdateMore();
int ConfirmUpdate();

int main() 
{
  Menu();
  return 0;
}

void GetFriendInfo(friend_t *p)
{
  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", p->fname);
  printf("Enter last name: ");
  scanf(" %[^\n]s", p->lname);
  printf("Enter birth date (MMDDYYYY): ");
  scanf(" %d", &p->bdate);

  // compute age
  int year = p->bdate % 10000;
  p->age = 2019 - year;

  printf("Enter gender (M/F): ");
  scanf(" %c", &p->gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", p->color);
}

void AddFriend()
{  
  fp = fopen(file_path, "a");
  if (fp == NULL) printf("\nFile not open for reading");

  friend_t *ptr = (friend_t*) malloc(sizeof(friend_t));
  GetFriendInfo(ptr);

  fwrite(ptr, sizeof(friend_t), 1, fp);

  printf("\nSuccessfully added %s\n\n", ptr->fname);

  fclose(fp);
  free(ptr);

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

void SearchFriend(int *f, int *i)
{
  friend_t *buffer = (friend_t*) malloc(sizeof(friend_t));
  fp = fopen(file_path, "r");
  if (fp == NULL) printf("\nError reading file");

  char *lname = (char*) malloc(41*sizeof(char));
  char *fname = (char*) malloc(31*sizeof(char));

  printf("\nEnter last name: ");
  scanf(" %[^\n]s", lname);
  printf("Enter first name: ");
  scanf(" %[^\n]s", fname);

  while (fread(buffer, sizeof(friend_t), 1, fp) == 1)
  {
    if (strstr(buffer->lname, lname) != NULL) 
      if (strstr(buffer->fname, fname) != NULL)
      {
        *f = 1;
        break;
      }
    
    (*i)++;
  }

  free(buffer);
  free(lname);
  free(fname);
  fclose(fp);
}

void DeleteFriend()
{
  int found = -1;
  int friend_index = 0;

  SearchFriend(&found, &friend_index);

  if (found != -1)
  {
    printf("\ncontinue deleting?\n");
    int confirm = ConfirmDelete();

    if (confirm == 1)
    {
      fp = fopen(file_path, "rb");
      fp1 = fopen(temp_path, "wb");
      friend_t *buffer = (friend_t*) malloc(sizeof(friend_t));
      int ctr = 0;

      while (fread(buffer, sizeof(friend_t), 1, fp) == 1) 
      {
        /* skip the line at given line number */
        if (ctr != friend_index)  
        {
          fwrite(buffer, sizeof(friend_t), 1, fp1);
        }
        ctr++;
      }
      printf("\nsuccessfully deleted\n\n");

      fclose(fp);
      fclose(fp1);
      free(buffer);
      remove(file_path);  		
      rename(temp_path, file_path);

      DeleteMore();
    }
    else if (confirm == 2)
    {
      DeleteMore();
    }
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

int ConfirmDelete()
{
  int u_input;
  printf("1 - yes\n");
  printf("2 - cancel\n\n");
  printf("Enter action: ");
  scanf("%d", &u_input);
  return u_input;
}

void UpdateFriend()
{
  int found = -1;
  int friend_index = 0;

  SearchFriend(&found, &friend_index);

  if (found != -1)
  {
    friend_t *temp = (friend_t*) malloc(sizeof(friend_t));
    printf("\nwhat will you update?\n");
    int confirm = ConfirmUpdate();

    if (confirm == 1)
    {
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", temp->lname);
    }
    else if (confirm == 2)
    {
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", temp->fname);
    }
    else if (confirm == 3)
    {
      printf("\nEnter new birthdate: ");
      scanf("%d", &temp->bdate);
    }
    else if (confirm == 4)
    {}
    else if (confirm == 5)
    {
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", temp->color);
    }
    else
    {
      UpdateMore();
    }
    
    fp = fopen(file_path, "r");
    fp1 = fopen(temp_path, "w");
    friend_t *buffer = (friend_t*) malloc(sizeof(friend_t));
    int ctr = 0;
    while (fread(buffer, sizeof(friend_t), 1, fp) == 1) 
    {
      if (ctr == friend_index)  
      { 
        if (confirm == 1) 
          strcpy(buffer->lname, temp->lname);
        else if (confirm == 2) 
          strcpy(buffer->fname, temp->fname);
        else if (confirm == 3) 
        {
          buffer->bdate = temp->bdate;
          int year = temp->bdate % 10000;
          buffer->age = 2019 - year;
        }
        else if (confirm == 4) 
        {
          if (buffer->gender == 'M')
            buffer->gender = 'F';
          else 
            buffer->gender = 'M';
        }
        else if (confirm == 5) 
          strcpy(buffer->color, temp->color);

        fwrite(buffer, sizeof(friend_t), 1, fp1);
      } else {
        fwrite(buffer, sizeof(friend_t), 1, fp1);
      }
      ctr++;
    }
    printf("\nsuccessfully updated\n\n");
    
    fclose(fp);
    fclose(fp1);
    free(buffer);
    remove(file_path);  		
    rename(temp_path, file_path);
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

int ConfirmUpdate()
{
  int u_input;
  printf("1 - last name\n");
  printf("2 - first name\n");
  printf("3 - birtdate\n");
  printf("4 - gender\n");
  printf("5 - favourite color\n");
  printf("6 - cancel\n\n");
  printf("Enter action: ");
  scanf("%d", &u_input);
  return u_input; 
}

void DisplayFriends()
{  
  fp1 = fopen(file_path, "r");
  if (fp1 == NULL) printf("\nFile not open for reading");
  
  friend_t *ptr = (friend_t*) malloc(sizeof(friend_t));
  
  if (fread(ptr, sizeof(friend_t), 1, fp1) == 1)
  {
    fclose(fp1);
    fp1 = fopen(file_path, "r+");
    if (fp1 == NULL) printf("\nFile not open for reading");
    
    printf("\nFriends:\n");

    int count = 1;
    while (fread(ptr, sizeof(friend_t), 1, fp1) == 1) 
    {
      printf("friend #%d\n", count);
      printf("first name: %s\n", ptr->fname);
      printf("last name: %s\n", ptr->lname);
      printf("birthdate: %d\n", ptr->bdate);
      printf("age: %d\n", ptr->age);
      printf("gender: %c\n", ptr->gender);
      printf("favourite color: %s\n\n", ptr->color);
      count++;
    }
  }
  else
    printf("\nNo friends yet.\n");

  fclose(fp1);
  free(ptr);
  Menu();
}

void BubbleSort()
{}

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
  printf("Invalid input!\n\n");
  Menu();
}
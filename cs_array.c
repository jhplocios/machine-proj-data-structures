#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char fname[31];
  char lname[41];
  int bdate;
  int age;
  char gender;
  char color[16]; 
} friend_t;

typedef struct {
  friend_t *ptr;
  int length;
  int count;
} arr_t;

arr_t friends;

void Menu();
void Instructions();
void AddFriend();
void DeleteFriend();
void UpdateFriend();
void DisplayFriends();
void InvalidInput(); 
void AddMore();
int ConfirmDelete();
void DeleteMore();
void UpdateMore();

int main() 
{
  friends.count = 0;
  friends.length = 2;
  friends.ptr = (friend_t*) malloc(friends.length*sizeof(friend_t));

  if (friends.ptr == NULL) 
  {
    printf("Error! memory not allocated.");
    exit(0);
  }

  Menu();

  if (friends.ptr) free(friends.ptr);
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
  friend_t *temp = (friend_t*)malloc(sizeof(friend_t));
  GetFriendInfo(temp);
  
  if (friends.length == friends.count) 
  {
    friends.ptr = realloc(friends.ptr, friends.length*2*sizeof(friend_t));
    friends.length *= 2;
    printf("\nreallocating memory, new size of array is %d\n", friends.length);
  }

  printf("\nSuccessfully added %s\n\n", temp->fname);

  friends.ptr[friends.count] = *temp;
  friends.count++;

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
  char *lname = (char*) malloc(41*sizeof(char));
  char *fname = (char*) malloc(31*sizeof(char));

  printf("\nEnter last name: ");
  scanf(" %[^\n]s", lname);
  printf("Enter first name: ");
  scanf(" %[^\n]s", fname);

  for (int i=0; i<friends.count; ++i)
  {
    if (strcmp(friends.ptr[i].lname, lname) == 0)
      if (strcmp(friends.ptr[i].fname, fname) == 0)
      {
        *index = i;
        break;
      }
  }
  
  free(lname);
  free(fname);
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
      for (int i=friend_index; i<friends.count-1; ++i)
      {
        friends.ptr[i] = friends.ptr[i+1];
      }
      friends.count--;
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
      char *new_lname = (char*)malloc(41*sizeof(char));
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", new_lname);
      memcpy(friends.ptr[friend_index].lname, new_lname, 41*sizeof(char));
      printf("\nUpdated last name to %s\n\n", new_lname);
      free(new_lname);
    }
    else if (confirm_update == 2)
    {
      char *new_fname = (char*)malloc(31*sizeof(char));
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", new_fname);
      memcpy(friends.ptr[friend_index].fname, new_fname, 31*sizeof(char));
      printf("\nUpdated first name to %s\n\n", new_fname);
      free(new_fname);
    } 
    else if (confirm_update == 3)
    {
      int new_bdate; 
      printf("\nEnter new birthdate (MMDDYYYY): ");
      scanf(" %d", &new_bdate);
        // compute age
      int year = new_bdate % 10000;
      friends.ptr[friend_index].age = 2019 - year;
      friends.ptr[friend_index].bdate = new_bdate;
      printf("\nUpdated birthdate to %d\n\n", new_bdate);
    } 
    else if (confirm_update == 4)
    {
      if (friends.ptr[friend_index].gender == 'M')
        friends.ptr[friend_index].gender = 'F';
      else 
        friends.ptr[friend_index].gender = 'M';

      printf("\nUpdated gender\n");
    }
    else if (confirm_update == 5)
    {
      char *new_color = (char*)malloc(16*sizeof(char));
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", new_color);
      memcpy(friends.ptr[friend_index].color, new_color, 16*sizeof(char));
      printf("\nUpdated favourite color to %s\n\n", new_color);
      free(new_color);
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
  if (friends.count == 0) 
    printf("\nNo friends yet.\n");
  else 
  {
    printf("\nFriends:\n\n");
    for (int i=0; i < friends.count; i++)
    {
      printf("friend #%d\n", i+1);
      printf("first name: %s\n", &(*(friends.ptr+i)->fname));
      printf("last name: %s\n", &(*(friends.ptr+i)->lname));
      printf("birthdate: %d\n", friends.ptr[i].bdate);
      printf("age: %d\n", friends.ptr[i].age);
      printf("gender: %c\n", friends.ptr[i].gender);
      printf("favourite color: %s\n\n", &(*(friends.ptr+i)->color));
    }
  }
  Menu();
}

void swap(friend_t *x,friend_t *y)
{
  friend_t temp = *x;
  *x = *y;
  *y = temp;
}

void BubbleSort() 
{
  int i,j,flag=0;
  for(i=0; i<friends.count-1; i++)
  {
    flag=0;
    for(j=0; j<friends.count-i-1; j++)
    {
      if(friends.ptr[j].lname[0] > friends.ptr[j+1].lname[0])
      {
        swap(&friends.ptr[j], &friends.ptr[j+1]);
        flag=1;
      }
      else if (friends.ptr[j].lname[0] == friends.ptr[j+1].lname[0])
        if (friends.ptr[j].lname[1] > friends.ptr[j+1].lname[1]) 
        {  
          swap(&friends.ptr[j], &friends.ptr[j+1]);
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
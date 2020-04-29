#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define file_path "friend.bin"
#define temp_path "temp.bin"

typedef struct friend {
  char firstname[31];
  char lastname[41];
  char birthdate[9];
  int age;
  char gender;
  char color[16];
} friend_t;

void menu();
void instructions();
void invalid_input();
void add_friend();
void display_friends();
void add_more();
void delete_more();
int confirm_delete();
void update_more();
int confirm_update();

int main() {
  menu();
  return 0;
}

void add_friend()
{  
  FILE *fp = fopen(file_path, "ab");
  if (fp == NULL) printf("\nFile not open for reading");

  friend_t *ptr = (friend_t*) malloc(sizeof(friend_t));

  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", ptr->firstname);
  printf("Enter last name: ");
  scanf(" %[^\n]s", ptr->lastname);
  printf("Enter birth date (MMDDYYYY): ");
  scanf(" %[^\n]s", ptr->birthdate);

  char year[4];
  int c = 0;
  while (c < 4) 
  {
    year[c] = ptr->birthdate[4+c];
    c++;
  }
  int byear;
  scanf(year, "%d", &byear);
  ptr->age = 2019 - byear;

  printf("Enter gender (M/F): ");
  scanf(" %c", &ptr->gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", ptr->color);
  
  fwrite(ptr, sizeof(friend_t), 1, fp);

  printf("\nSuccessfully added %s\n\n", ptr->firstname);

  fclose(fp);
  free(ptr);

  add_more();
}

void add_more()
{
  int input;
  printf("1 - Add more friends\n");
  printf("2 - Back to main menu\n\n");
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
    add_more();
  }
}

void search_friend(int *f, int *f_i)
{
  friend_t *buffer = (friend_t*) malloc(sizeof(friend_t));
  FILE *fp = fopen(file_path, "rb");
  if (fp == NULL) printf("\nError reading file");

  char *lname = (char*) malloc(41*sizeof(char));
  char *fname = (char*) malloc(31*sizeof(char));

  printf("\nEnter last name: ");
  scanf(" %[^\n]s", lname);
  printf("Enter first name: ");
  scanf(" %[^\n]s", fname);

  while (fread(buffer, sizeof(friend_t), 1, fp) == 1)
  {
    if (strstr(buffer->lastname, lname) != NULL) 
    {
      if (strstr(buffer->firstname, fname) != NULL)
      {
        *f = 1;
        break;
      }
    }
    (*f_i)++;
  }

  free(buffer);
  fclose(fp);
}

void delete_friend()
{
  FILE *fp1, *fp;
  int found = -1;
  int friend_index = 0;

  search_friend(&found, &friend_index);

  if (found != -1)
  {
    printf("\ncontinue deleting?\n");
    int confirm = confirm_delete();

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

      delete_more();
    }
    else if (confirm == 2)
    {
      delete_more();
    }
    else
    {
      printf("\nInvalid input!\n\n");
      delete_more();
    }
  } 
  else 
  {
    printf("\nfriend not found\n\n");
    delete_more();
  }
}

int confirm_delete()
{
  int u_input;
  printf("1 - yes\n");
  printf("2 - cancel\n\n");
  printf("Enter action: ");
  scanf("%d", &u_input);
  return u_input;
}

void delete_more()
{
  int delete_another;
  printf("1 - delete another friend\n");
  printf("2 - back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &delete_another);
  
  if (delete_another == 1)
  {
    delete_friend();
  }
  else if (delete_another == 2) 
  {
    menu();
  } 
  else 
  {
    printf("\nInvalid input!\n\n");
    delete_more();
  }
}

void update_friend()
{
  FILE *fp1, *fp;
  int found = -1;
  int friend_index = 0;

  search_friend(&found, &friend_index);

  if (found != -1)
  {
    friend_t *temp = (friend_t*) malloc(sizeof(friend_t));
    printf("\ncontinue updating?\n");
    int confirm = confirm_update();

    if (confirm == 1)
    {
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", temp->lastname);
    }
    else if (confirm == 2)
    {
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", temp->firstname);
    }
    else if (confirm == 3)
    {
      printf("\nEnter new birthdate: ");
      scanf(" %[^\n]s", temp->birthdate);
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
      update_more();
    }
    
    fp = fopen(file_path, "rb");
    fp1 = fopen(temp_path, "wb");
    friend_t *buffer = (friend_t*) malloc(sizeof(friend_t));
    int ctr = 0;
    while (fread(buffer, sizeof(friend_t), 1, fp) == 1) 
    {
      if (ctr == friend_index)  
      { 
        if (confirm == 1) 
        {
          strcpy(buffer->lastname, temp->lastname);
        } 
        else if (confirm == 2) 
        {
          strcpy(buffer->firstname, temp->firstname);
        }
        else if (confirm == 3) 
        {
          strcpy(buffer->birthdate, temp->birthdate);
        }
        else if (confirm == 4) 
        {
          if (buffer->gender == 'M')
          {
            buffer->gender = 'F';
          }
          else 
          {
            buffer->gender = 'M';
          }
        }
        else if (confirm == 5) 
        {
          strcpy(buffer->color, temp->color);
        }

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
    update_more();
  }
  else
  {
    printf("\nfriend not found\n\n");
    update_more();
  }
}

int confirm_update()
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

void update_more()
{
  int update_another;
  printf("1 - update another friend\n");
  printf("2 - back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &update_another);
  
  if (update_another == 1)
  {
    update_friend();
  }
  else if (update_another == 2) 
  {
    menu();
  } 
  else 
  {
    printf("\nInvalid input!\n\n");
    update_more();
  }
}

void display_friends()
{  
  FILE *fp1 = fopen(file_path, "rb");
  if (fp1 == NULL) printf("\nFile not open for reading");

  friend_t *ptr = (friend_t*) malloc(sizeof(friend_t));
    
  printf("\nFriends:\n\n");

  while (fread(ptr, sizeof(friend_t), 1, fp1) == 1) 
  {
    printf("%s\n", ptr->firstname);
    printf("%s\n", ptr->lastname);
    printf("%s\n", ptr->birthdate);
    printf("%d\n", ptr->age);
    printf("%c\n", ptr->gender);
    printf("%s\n\n", ptr->color);
  }

  fclose(fp1);
  free(ptr);
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
      update_friend();
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
  printf("Invalid input!\n\n");
  menu();
}
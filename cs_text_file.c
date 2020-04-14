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

char *firstname;
char *lastname;
char *birthdate;
int age;
char gender;
char *color; 

void menu();
void instructions();
void add_friend();
void delete_friend();
void update_friend();
void display_friends();
void invalid_input(); 

int main() 
{
  menu();
  return 0;
}

void add_friend()
{  
  fp = fopen(file_path, "a");
  if (fp == NULL) printf("\nFile not open for reading");

  firstname = (char*) malloc(fname_size*sizeof(char));
  lastname = (char*) malloc(lname_size*sizeof(char));
  birthdate = (char*) malloc(bdate_size*sizeof(char));
  color = (char*) malloc(color_size*sizeof(char));

  printf("\nEnter friend information:\n");
  printf("Enter first name: ");
  scanf(" %[^\n]s", firstname);
  printf("Enter last name: ");
  scanf(" %[^\n]s", lastname);
  printf("Enter birth date (MMDDYYYY): ");
  scanf(" %[^\n]s", birthdate);

  char year[4];
  int c = 0;
  while (c < 4) 
  {
    year[c] = birthdate[4+c];
    c++;
  }
  int byear;
  scanf(year, "%d", &byear);
  age = 2019 - byear;

  printf("Enter gender (M/F): ");
  scanf(" %c", &gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", color);
  
  fprintf(fp, "\n%s", firstname);
  fprintf(fp, "\n%s", lastname);
  fprintf(fp, "\n%s", birthdate);
  fprintf(fp, "\n%d", age);
  fprintf(fp, "\n%c", gender);
  fprintf(fp, "\n%s\n", color);

  printf("\nSuccessfully added %s\n\n", firstname);

  int input;
  printf("1 - Add more friends\n");
  printf("2 - Back to main menu\n\n");
  printf("Enter action: ");
  scanf("%d", &input);

  fclose(fp);
  free(firstname);
  free(lastname);
  free(birthdate);
  free(color);

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
  fp = fopen(file_path, "r+");
  if (fp == NULL) printf("\nError reading file");

  char *buffer = (char*) malloc(50*sizeof(char));
  char *temp = (char*) malloc(50*sizeof(char));
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", temp);

  int index = -1;
  int line = 0;
  while (fgets(buffer, 50*sizeof(char), fp) != NULL)
  {
    if (strstr(buffer, temp) != NULL) 
    {
      index = 1;
      break;
    }
    line++;
  }

  fclose(fp);

  int confirm_delete, delete_another;
  int ctr = 0;
  if (index != -1)
  {
    printf("delete friend %s?\n", temp);
    printf("1 - yes\n");
    printf("2 - cancel\n\n");
    printf("Enter action: ");
    scanf("%d", &confirm_delete);

    if (confirm_delete == 1)
    {
      fp = fopen(file_path, "r+");
      fp1 = fopen(temp_path, "w");

      while (fgets(buffer, 50*sizeof(char), fp) != NULL) 
      {
        ctr++;
        /* skip the line at given line number */
        if (ctr < line-1 || ctr > line+4)  
        {
          fprintf(fp1, "%s", buffer);
        }
      }
      printf("\nsuccessfully deleted %s\n", temp);
      fclose(fp);
      fclose(fp1);
      free(temp);
      free(buffer);
      remove(file_path);  		
      rename(temp_path, file_path);
      menu();
    }
    else
    {
      printf("1 - delete another friend\n");
      printf("2 - back to main menu\n\n");
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
    printf("\nfriend not found\n\n");
    printf("1 - delete another friend\n");
    printf("2 - back to main menu\n\n");
    printf("Enter action: ");
    scanf("%d", &delete_another);

    free(temp);
    free(buffer);
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

void update_friend()
{
  fp = fopen(file_path, "r+");
  if (fp == NULL) printf("\nError reading file");

  char *buffer = (char*) malloc(50*sizeof(char));
  char *temp = (char*) malloc(50*sizeof(char));
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", temp);

  int index = -1;
  int line = 0;
  while (fgets(buffer, 50*sizeof(char), fp) != NULL)
  {
    if (strstr(buffer, temp) != NULL) 
    {
      index = 1;
      break;
    }
    line++;
  }
  
  fclose(fp);

  int confirm_update, update_another;
  int ctr = 0;
  if (index != -1)
  {
    printf("\nupdate friend %s?\n", temp);
    printf("1 - last name\n");
    printf("2 - first name\n");
    printf("3 - birtdate\n");
    printf("4 - gender\n");
    printf("5 - favourite color\n");
    printf("6 - cancel\n\n");
    printf("Enter action: ");
    scanf("%d", &confirm_update);

    char *temp2 = (char*) malloc(50*sizeof(char));

    if (confirm_update == 1)
    {
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", temp2);
      line = line + 1;
    }
    else if (confirm_update == 2)
    {
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", temp2);
    } 
    else if (confirm_update == 3)
    {
      printf("\nEnter new birthdate (MMDDYYYY): ");
      scanf(" %[^\n]s", temp2);
      line = line + 2;
    } 
    else if (confirm_update == 4)
    {
      line = line + 4;
    }
    else if (confirm_update == 5)
    {
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", temp2);
      line = line + 5;
    } 
    else if (confirm_update > 5)
    {
      printf("1 - update another friend\n");
      printf("2 - back to main menu\n\n");
      printf("Enter action: ");
      scanf("%d", &update_another);

      if (update_another == 1)
      {
        update_friend();
      }
      else 
      {
        menu();
      }
    }

    fp = fopen(file_path, "r+");
    fp1 = fopen(temp_path, "w");

    while (fgets(buffer, 50*sizeof(char), fp) != NULL) 
    {
      ctr++;
      /* skip the line at given line number */
      if (ctr != line)  
      {
        fprintf(fp1, "%s", buffer);
      }
      else 
      {
        fprintf(fp1, "%s\n", temp2); 
      }
    }
    printf("\nsuccessfully updated a friend\n");
    fclose(fp);
    fclose(fp1);
    free(temp);
    free(temp2);
    free(buffer);
    remove(file_path);  		
    rename(temp_path, file_path);

    printf("\n1 - update another friend\n");
    printf("2 - back to main menu\n\n");
    printf("Enter action: ");
    scanf("%d", &update_another);

    if (update_another == 1)
    {
      update_friend();
    }
    else 
    {
      menu();
    }
  } 
  else 
  {
    printf("\nfriend not found\n\n");
    printf("1 - update another friend\n");
    printf("2 - back to main menu\n");
    printf("Enter action: ");
    scanf("%d", &update_another);

    if (update_another == 1)
    {
      update_friend();
    }
    else 
    {
      menu();
    }
  }
}

void display_friends()
{  
  fp1 = fopen(file_path, "r+");
  if (fp1 == NULL) printf("\nFile not open for reading");
  
  char *buffer = (char*) malloc(50*sizeof(char));
  
  printf("\nFriends:\n");

  while (fgets(buffer, 50*sizeof(char), fp1) != NULL)
  {
    printf("%s", buffer);
  }

  fclose(fp1);
  free(buffer);
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
      fp1 = fopen(file_path, "rb");
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
  printf("Invalid input!\n-----\n");
  menu();
}
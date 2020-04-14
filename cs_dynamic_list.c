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
} friend_t;

typedef struct node {
  friend_t val;
  struct node *next;
} node_t;

node_t *head, *tail = NULL;

void menu();
void instructions();
void add_friend();
void delete_friend();
void update_friend();
void display_friends();
void invalid_input(); 
void add_to_tail(friend_t f);
void print_list();
friend_t remove_head();
friend_t remove_tail();
int search_list(char *lname);

int main() 
{
  menu();
  return 0;
}

void add_to_tail(friend_t f) 
{ 
  node_t *current;
  node_t *new_node = (node_t*) malloc(sizeof(node_t));

  new_node->val = f;
  new_node->next = NULL;

  if (head == NULL) 
  {
    head = tail = new_node;
  }
  else
  {
    current = tail;
    current->next = new_node;
    tail = new_node;
  }
}

friend_t remove_tail()
{
  friend_t retval;
  
  if (head->next == NULL)
  {
    retval = head->val;
    free(head);
    return retval;
  }
  
  node_t *current = head;
  while (current->next->next != NULL)
  {
    current = current->next;
  }

  retval = current->next->val;
  free(current->next);
  current->next = NULL;
  tail = current;
  return retval;
}

friend_t remove_head()
{
  friend_t retval;
  node_t *next_node = NULL;

  next_node = head->next;
  retval = head->val;
  free(head);
  head = next_node;
  return retval;
}

void search_and_update(int n, char *s, int t)
{ 
  node_t *current = head;

  for (int i=0; i<n; i++)
  {
    if (current->next == NULL) return;
    
    current = current->next;
  }

  if (t == 1) 
  {
    current->val.lastname = s;
  }
  else if (t == 2)
  {
    current->val.firstname = s;
  }
  else if (t == 3)
  {
    current->val.birthdate = s;
  }
  else if (t == 4)
  {
    if (current->val.gender == 'M')
    {
      current->val.gender = 'F';
      printf("\nUpdated friend #%d gender to F\n\n", n+1);
    }
    else 
    {
      current->val.gender = 'M';
      printf("\nUpdated friend #%d gender to M\n\n", n+1);
    }
  }
  else if (t == 5)
  {
    current->val.color = s;
  }
}

int search_list(char *lname)
{
  int index = -1, found = -1;
  node_t *current = head;

  while (current != NULL)
  {
    ++index;
    if (strcmp(current->val.lastname, lname) == 0)
    { 
      found = index;
      break;
    }
    current = current->next;
  } 
  return found;
}

void print_list()
{
  node_t *current = head;
  int count = 1;
  while (current != NULL)
  {
    printf("friend #%d\n", count);
    printf("first name: %s\n", current->val.firstname);
    printf("last name: %s\n", current->val.lastname);
    printf("birthdate: %s\n", current->val.birthdate);
    printf("age: %d\n", current->val.age);
    printf("gender: %c\n", current->val.gender);
    printf("favourite color: %s\n\n", current->val.color);
    current = current->next;
    count++;
  }
}

void add_friend()
{  
  friend_t temp;
  temp.firstname = (char*) malloc(fname_size*sizeof(char));
  temp.lastname = (char*) malloc(lname_size*sizeof(char));
  temp.birthdate = (char*) malloc(bdate_size*sizeof(char));
  temp.color = (char*) malloc(color_size*sizeof(char));

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
  scanf(year, "%d", &byear);
  temp.age = 2019 - byear;

  printf("Enter gender (M/F): ");
  scanf(" %c", &temp.gender);
  printf("Enter favourite color: ");
  scanf(" %[^\n]s", temp.color);
  
  add_to_tail(temp);
  printf("\nSuccessfully added %s\n\n", temp.firstname);

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
    menu();
  }
}

void delete_friend()
{
  char *temp = (char*) malloc(50*sizeof(char));
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", temp);

  int index = search_list(temp);

  int confirm_delete, delete_another;
  if (index != -1)
  {
    printf("delete friend %s?\n", temp);
    printf("1 - yes\n");
    printf("2 - cancel\n\n");
    printf("Enter action: ");
    scanf("%d", &confirm_delete);

    if (confirm_delete == 1)
    {
      friend_t del;
      if (strcmp(head->val.lastname, temp) == 0)
      {
        del = remove_head();    
      }
      else if (strcmp(tail->val.lastname, temp) == 0)
      {
        del = remove_tail();
      }
      else
      {
        node_t *current = head;
        while (current->next != NULL)
        {
          if (strcmp(current->next->val.lastname, temp) == 0)
          { 
            node_t *temp_node = current->next->next;
            del = current->next->val;
            free(current->next);
            current->next = temp_node;
            break;
          }
        }
      }

      printf("\nsuccessfully deleted %s\n", del.lastname);
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

    if (delete_another == 1)
    {
      delete_friend();
    }
    else 
    {
      menu();
    }
  }
  free(temp);
}

void update_friend()
{
  char *temp = (char*) malloc(50*sizeof(char));
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", temp);

  int index = search_list(temp);

  int confirm_update, update_another;
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

      search_and_update(index, temp2, confirm_update);
      printf("\nUpdated friend #%d last name to %s\n", index+1, temp2);
    }
    else if (confirm_update == 2)
    {
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", temp2);

      search_and_update(index, temp2, confirm_update);
      printf("\nUpdated friend #%d first name to %s\n\n", index+1, temp2);
    } 
    else if (confirm_update == 3)
    {
      printf("\nEnter new birthdate (MMDDYYYY): ");
      scanf(" %[^\n]s", temp2);

      search_and_update(index, temp2, confirm_update);
      printf("\nUpdated friend #%d birthdate to %s\n\n", index+1, temp2);
    } 
    else if (confirm_update == 4)
    {
      search_and_update(index, temp2, confirm_update);
    }
    else if (confirm_update == 5)
    {
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", temp2);

      search_and_update(index, temp2, confirm_update);
      printf("\nUpdated friend#%d's favourite color to %s\n\n", index+1, temp2);
    } 

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
  free(temp);
}

void display_friends()
{
  if (head == NULL) 
  {
    printf("\nNo friends yet.\n");
  } else 
  {
    printf("\nFriends:\n\n");
    print_list();
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
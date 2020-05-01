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

typedef struct node {
  friend_t val;
  struct node *next;
} node_t;

node_t *head, *tail = NULL;

void Menu();
void Instructions();
void AddFriend();
void DeleteFriend();
void UpdateFriend();
void DisplayFriends();
void InvalidInput(); 
void AddToTail(friend_t *f);
void PrintList();
friend_t RemoveHead();
friend_t RemoveTail();
int SearchList(friend_t *f);
void AddMore();
void DeleteMore();
int ConfirmDelete();
void UpdateMore();

int main() 
{
  Menu();
  return 0;
}

void AddToTail(friend_t *f) 
{ 
  node_t *current;
  node_t *new_node = (node_t*) malloc(sizeof(node_t));

  new_node->val = *f;
  new_node->next = NULL;

  if (head == NULL) 
    head = tail = new_node;
  else
  {
    current = tail;
    current->next = new_node;
    tail = new_node;
  }
}

friend_t RemoveTail()
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

friend_t RemoveHead()
{
  friend_t retval;
  node_t *next_node = NULL;

  next_node = head->next;
  retval = head->val;
  free(head);
  head = next_node;
  return retval;
}

void SearchAndUpdate(int n, friend_t *f, int t)
{ 
  node_t *current = head;

  for (int i=0; i<n; i++)
  {
    if (current->next == NULL) return;
    current = current->next;
  }

  if (t == 1) 
    memcpy(current->val.lname, &(*f->lname), 41*sizeof(char));
  else if (t == 2)
    memcpy(current->val.fname, &(*f->fname), 31*sizeof(char));
  else if (t == 3)
  {
    current->val.bdate = f->bdate;
    int year = f->bdate % 10000;
    current->val.age = 2019 - year;
  }
  else if (t == 4)
  {
    if (current->val.gender == 'M')
      current->val.gender = 'F';
    else 
      current->val.gender = 'M';
  }
  else if (t == 5)
    memcpy(current->val.color, &(*f->color), 16*sizeof(char));
}

int SearchList(friend_t *f)
{
  printf("\nEnter last name: ");
  scanf(" %[^\n]s", &(*f->lname));
  printf("Enter first name: ");
  scanf(" %[^\n]s", &(*f->fname));

  int index = -1, found = -1;
  node_t *current = head;

  while (current != NULL)
  {
    ++index;
    if (strcmp(current->val.lname, &(*f->lname)) == 0)
      if (strcmp(current->val.fname, &(*f->fname)) == 0)
      { 
        found = index;
        break;
      }
    current = current->next;
  } 

  return found;
}

void PrintList()
{
  node_t *current = head;
  int count = 1;
  while (current != NULL)
  {
    printf("friend #%d\n", count);
    printf("first name: %s\n", current->val.fname);
    printf("last name: %s\n", current->val.lname);
    printf("birthdate: %d\n", current->val.bdate);
    printf("age: %d\n", current->val.age);
    printf("gender: %c\n", current->val.gender);
    printf("favourite color: %s\n\n", current->val.color);
    current = current->next;
    count++;
  }
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
  friend_t *temp = (friend_t*) malloc(sizeof(friend_t)); 
  GetFriendInfo(temp);
  
  AddToTail(temp);
  printf("\nSuccessfully added %s\n\n", temp->fname);

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

void DeleteFriend()
{
  friend_t *temp = (friend_t*) malloc(sizeof(friend_t));
  int index = SearchList(temp);

  int confirm, delete_another;
  if (index != -1)
  {
    printf("\ncontinue deleting?\n");
    confirm = ConfirmDelete();

    if (confirm == 1)
    {
      friend_t del;
      if (strcmp(head->val.lname, temp->lname) == 0 && strcmp(head->val.fname, temp->fname) == 0)
        del = RemoveHead();    
      else if (strcmp(tail->val.lname, temp->lname) == 0 && strcmp(tail->val.fname, temp->fname) == 0)
        del = RemoveTail();
      else
      {
        node_t *current = head;
        while (current->next != NULL)
        {
          if (strcmp(current->next->val.lname, temp->lname) == 0 && strcmp(current->next->val.fname, temp->fname) == 0)
          { 
            node_t *temp_node = current->next->next;
            del = current->next->val;
            free(current->next);
            current->next = temp_node;
            break;
          }
        }
      }

      printf("\nsuccessfully deleted %s\n\n", del.lname);
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
  free(temp);
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
  friend_t *temp = (friend_t*) malloc(sizeof(friend_t));
  int index = SearchList(temp);

  int confirm_update, update_another;
  if (index != -1)
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

    friend_t *temp2 = (friend_t*) malloc(sizeof(friend_t));

    if (confirm_update == 1)
    {
      printf("\nEnter new last name: ");
      scanf(" %[^\n]s", temp2->lname);

      SearchAndUpdate(index, temp2, confirm_update);
      printf("\nUpdated last name to %s\n\n", temp2->lname);
    }
    else if (confirm_update == 2)
    {
      printf("\nEnter new first name: ");
      scanf(" %[^\n]s", temp2->fname);

      SearchAndUpdate(index, temp2, confirm_update);
      printf("\nUpdated first name to %s\n\n", temp2->fname);
    } 
    else if (confirm_update == 3)
    {
      printf("\nEnter new birthdate (MMDDYYYY): ");
      scanf(" %d", &temp2->bdate);

      SearchAndUpdate(index, temp2, confirm_update);
      printf("\nUpdated birthdate to %d\n\n", temp2->bdate);
    } 
    else if (confirm_update == 4)
    {
      SearchAndUpdate(index, temp2, confirm_update);
      printf("\nUpdated gender\n\n");
    }
    else if (confirm_update == 5)
    {
      printf("\nEnter new favourite color: ");
      scanf(" %[^\n]s", temp2->color);

      SearchAndUpdate(index, temp2, confirm_update);
      printf("\nUpdated favourite color to %s\n\n", temp2->color);
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
  free(temp);
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
  if (head == NULL) 
    printf("\nNo friends yet.\n");
  else 
  {
    printf("\nFriends:\n\n");
    PrintList();
  }
  Menu();
}

void swap(node_t *a, node_t *b) 
{ 
  friend_t temp = a->val; 
  a->val = b->val; 
  b->val = temp; 
} 

void BubbleSort()
{
  int swapped, i; 
  node_t *ptr1; 
  node_t *lptr = NULL; 

  /* Checking for empty list */
  if (head == NULL) 
    return; 

  do
  { 
    swapped = 0; 
    ptr1 = head; 
    while (ptr1->next != lptr) 
    { 
      if (ptr1->val.lname[0] > ptr1->next->val.lname[0]) 
      {  
        swap(ptr1, ptr1->next); 
        swapped = 1; 
      }
      else if (ptr1->val.lname[0] == ptr1->next->val.lname[0])
        if (ptr1->val.lname[1] > ptr1->next->val.lname[1]) 
        {  
          swap(ptr1, ptr1->next); 
          swapped = 1; 
        }
      ptr1 = ptr1->next; 
    } 
    lptr = ptr1; 
  } 
  while (swapped); 

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
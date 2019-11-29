#include <stdio.h>
#include <string.h>

#define EMPTY 0
#define REMOVED 1
#define FULL 2



typedef struct HashEntry {
  int flag;
  int hash;
  char s[20];
} HashEntry;

typedef struct HashTable {
  int size;
  HashEntry entries[101];
} HashTable;

int hash_function(char *s) {
  long sum = 0;
  long i = 1;
  while(*s != '\0') {
    sum += (*s) * i;
    ++i;
    ++s;
  }
  return (19 * sum) % 101;
}

int hash_find(HashTable *h, char *string) {
  int hash = hash_function(string);
  int j;
  for(j = 0; j < 20; ++j) {
    int loc = (hash + 23 * j + j * j) % 101;
    if(h->entries[loc].flag == EMPTY) return 0;
    if(h->entries[loc].flag == REMOVED) continue;
    if(h->entries[loc].hash == hash && (strcmp(h->entries[loc].s, string) == 0)) {
      return 1;
    }
  }
  return 0;
}

void hash_insert(HashTable *h, char *string) {
  int hash = hash_function(string);
  int j;

  if (hash_find(h, string) == 1) return;

  for(j = 0; j < 20; ++j) {
    int loc = (hash + 23 * j + j * j) % 101;
    if(h->entries[loc].flag == EMPTY || h->entries[loc].flag == REMOVED) {
      (h->size)++;
      h->entries[loc].flag = FULL;
      h->entries[loc].hash = hash;
      strcpy(h->entries[loc].s, string);
      break;
    }
  }
  return;
} 

void hash_delete(HashTable *h, char *string) {
  int hash = hash_function(string);
  int j;
  for(j = 0; j < 20; ++j) {
    int loc = (hash + 23 * j + j * j) % 101;
    if(h->entries[loc].flag == EMPTY) return;
    if(h->entries[loc].flag == REMOVED) continue;
    if(h->entries[loc].hash == hash && (strcmp(h->entries[loc].s, string) == 0)) {
      h->entries[loc].flag = REMOVED;
      (h->size)--;
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    HashTable hash_table;

    int i, j;
    for(i = 0; i < 101; ++i) {
      hash_table.entries[i].flag = EMPTY;
    }
    hash_table.size = 0;

    int n;
    scanf("%d", &n);

    char string[50];
    for(i = 0; i < n; ++i) {
      scanf("%s", string);
      if(string[0] == 'A') {
        
        hash_insert(&hash_table, string + 4);
      } else {
        
        hash_delete(&hash_table, string + 4);
      }
    }

    printf("%d\n", hash_table.size);
    for(i = 0; i < 101; ++i) {
      if(hash_table.entries[i].flag == FULL) {
        printf("%d:%s\n", i, hash_table.entries[i].s);
      }
    }
  }
  return 0;
}
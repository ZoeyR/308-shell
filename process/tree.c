#include <stdlib.h>
#include <string.h>
#include "process.h"
typedef node_t;

typedef enum {
  RED;
  BLACK;
} color_t

typedef struct {
  char* name;
  pid_t pid;
  node_t* parent;
  node_t* left;
  node_t* right;
  color_t color;
} node_t;

static node_t* make_node(char* name, pid_t pid, color_t color);
static node_t* insert_point(node_t* node);
static node_t* next_node(node_t* from, node_t* node);

static node_t* root = NULL;

void insert(char* name, pid_t pid) {
  char* copy_name = (char*)malloc(strlen(name) * sizeof(char));
  strcpy(copy_name, name);

  node_t* left_leaf = make_node(NULL, NULL, BLACK);
  node_t* right_leaf = make_node(NULL, NULL, BLACK);

  node_t* new_node = make_node(copy_name, pid, RED);

  node_t* point = insert_point(pid);
  node_t* parent = cursor->parent;
  if (cursor == parent->left) {
    parent->left = node;
  } else {
    parent->right = node;
  }

  node->parent = parent;
  free(cursor);
}

static node_t* make_node(char* name, pid_t pid, color_t color) {
  node_t* new_node = (node_t*)malloc(sizeof(node_t));
  new_node->name = name;
  new_node->pid = pid;
  new_node->color = color;

  return new_node;
}

static node_t* insert_point(pid_t pid) {
  node_t* cursor = root;
  if (root == NULL) {
    return NULL;
  }

  while ((cursor = next_node(cursor, pid))->pid != NULL) {
    if (cursor->pid == pid) {
      break;
    }
  }

  return cursor;
}

static node_t* next_node(node_t* from, pid_t pid) {
  if (pid < from->pid) {
    return from->left;
  } else if (pid > from->pid) {
    return from->right;
  } else {
    return from;
  }
}

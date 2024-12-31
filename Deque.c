/*
 * Copyright ©2024 Travis McGaha.  All rights reserved.  Permission is
 * hereby granted to students registered for University of Pennsylvania
 * CIS 2400 for use solely during Fall Semester 2024 for purposes of
 * the course.  No other use, copying, distribution, or modification
 * is permitted without prior written consent. Copyrights for
 * third-party components of this work must be honored.  Instructors
 * interested in reusing these course materials should contact the
 * author.
 */

#include <stdio.h>
#include <stdlib.h>

#include "Deque.h"

///////////////////////////////////////////////////////////////////////////////
// Deque implementation.

Deque* Deque_Allocate() {
  Deque* deque = malloc(sizeof(Deque));
  deque->num_elements = 0;
  deque->front = deque->back = NULL;
  return deque;
}

void Deque_Free(Deque* dq) {
  DequeNode* current = dq->front;
  while (current != NULL) {
    DequeNode* next = current->next;
    free(current);
    current = next;
  }

  free(dq);
}

int Deque_Size(Deque* dq) {
  return (dq->num_elements);
}

void Deque_Push_Front(Deque* dq, rat_num payload) {
  DequeNode* node = malloc(sizeof(DequeNode));
  *node = (DequeNode){.payload = payload, .next = dq->front, .prev = NULL};
  if (dq->front != NULL) {
    dq->front->prev = node;
  }
  dq->front = node;
  if (dq->num_elements == 0) {
    dq->back = node;
  }
  (dq->num_elements)++;
}

bool Deque_Pop_Front(Deque* dq, rat_num* payload_ptr) {
  if (dq->num_elements == 0) {
    return false;
  }
  DequeNode* front = dq->front;
  *payload_ptr = dq->front->payload;
  dq->front = dq->front->next;
  if (dq->front) {
    dq->front->prev = NULL;
  }
  free(front);
  (dq->num_elements)--;
  return true;
}

bool Deque_Peek_Front(Deque* dq, rat_num* payload_ptr) {
  if (dq->num_elements == 0) {
    return false;
  }
  DequeNode* front = dq->front;
  *payload_ptr = front->payload;
  return true;
}

void Deque_Push_Back(Deque* dq, rat_num payload) {
  DequeNode* node = malloc(sizeof(DequeNode));
  *node = (DequeNode){.payload = payload, .next = NULL, .prev = dq->back};
  if (dq->back != NULL) {
    dq->back->next = node;
  }
  dq->back = node;
  if (dq->num_elements == 0) {
    dq->front = node;
  }
  (dq->num_elements)++;
}

bool Deque_Pop_Back(Deque* dq, rat_num* payload_ptr) {
  if (dq->num_elements == 0) {
    return false;
  }
  DequeNode* back = dq->back;
  *payload_ptr = dq->back->payload;
  dq->back = dq->back->prev;
  if (dq->back) {
    dq->back->next = NULL;
  }
  free(back);
  (dq->num_elements)--;
  return true;
}

bool Deque_Peek_Back(Deque* dq, rat_num* payload_ptr) {
  if (dq->num_elements == 0) {
    return false;
  }
  DequeNode* back = dq->back;
  *payload_ptr = back->payload;
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// DQIterator implementation.

DQIterator* DQIterator_Allocate(Deque* dq) {
  DequeNode* front = dq->front;
  if (!front) {
    return NULL;
  }
  DQIterator* iter = malloc(sizeof(DQIterator));
  iter->deque = dq;
  iter->node = front;
  return iter;
}

void DQIterator_Free(DQIterator* iter) {
  free(iter);
}

bool DQIterator_IsValid(DQIterator* iter) {
  return iter->node;
}

bool DQIterator_Next(DQIterator* iter) {
  iter->node = iter->node->next;
  if (iter->node) {
    return true;
  }
  return false;
}

void DQIterator_Get(DQIterator* iter, rat_num* payload) {
  *payload = iter->node->payload;
}

bool DQIterator_Remove(DQIterator* iter) {
  DequeNode* curr = iter->node;
  Deque* dq = iter->deque;
  if (dq->num_elements == 1) {
    dq->front = dq->back = NULL;
    iter->node = NULL;
  } else if (curr->next == NULL) {
    iter->node = curr->prev;
    dq->back = curr->prev;
    dq->back->next = NULL;
    curr->prev->next = NULL;
  } else if (curr->prev == NULL) {
    iter->node = curr->next;
    dq->front = curr->next;
    dq->front->prev = NULL;
    curr->next->prev = NULL;
  } else {
    iter->node = curr->next;
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  }
  free(curr);
  dq->num_elements--;
  return dq->num_elements > 0;
}

void DQIterator_Rewind(DQIterator* iter) {
  iter->node = iter->deque->front;
}
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

#include <cstdlib>
#include "./catch.hpp"

extern "C" {
  #include "./Deque.h"
}

// global constants:
const rat_num kOne =   {1, 1};
const rat_num kTwo =   {2, 1};
const rat_num kThree = {3, 1};
const rat_num kFour =  {4, 1};
const rat_num kFive =  {5, 1};

// This is C++ code to define the == operator to compare two rat_nums
// you do not have to know how this works.
bool operator==(const rat_num& lhs, const rat_num& rhs) {
  return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

TEST_CASE("Test_Deque", "[Basic]") {
  // Try creating a deque.
  Deque* dqp = Deque_Allocate();
  REQUIRE(dqp != NULL);
  REQUIRE(0 == Deque_Size(dqp));
  REQUIRE(NULL == dqp->front);
  REQUIRE(NULL == dqp->back);

  // Try deleting the (empty) deque.
  Deque_Free(dqp);
  dqp = NULL;
}

TEST_CASE("Test_Deque", "[PushPop_Front]") {
  // Creating a deque.
  Deque *dqp = Deque_Allocate();
  REQUIRE(dqp != NULL);
  REQUIRE(0 == Deque_Size(dqp));
  REQUIRE(NULL == dqp->front);
  REQUIRE(NULL == dqp->back);

  // Insert an element.
  rat_num payload_ptr;
  Deque_Push_Front(dqp, kOne);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);
  REQUIRE(Deque_Peek_Front(dqp, &payload_ptr));
  REQUIRE(kOne == payload_ptr);

  // Pop the element.
  REQUIRE(Deque_Pop_Front(dqp, &payload_ptr));
  REQUIRE(kOne == payload_ptr);
  REQUIRE(0 == Deque_Size(dqp));

  // Try (and fail) to pop the element a second time.
  REQUIRE_FALSE(Deque_Peek_Front(dqp, &payload_ptr));
  REQUIRE_FALSE(Deque_Pop_Front(dqp, &payload_ptr));
  REQUIRE_FALSE(Deque_Peek_Front(dqp, &payload_ptr));

  // Insert two elements.
  Deque_Push_Front(dqp, kOne);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);

  Deque_Push_Front(dqp, kTwo);
  REQUIRE(2 == Deque_Size(dqp));
  REQUIRE(dqp->front != dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(dqp->back == dqp->front->next);
  REQUIRE(dqp->front == dqp->back->prev);
  REQUIRE(kTwo == dqp->front->payload);
  REQUIRE(kOne == dqp->back->payload);
  REQUIRE(Deque_Peek_Front(dqp, &payload_ptr));
  REQUIRE(kTwo == payload_ptr);

  // Pop the first element.
  REQUIRE(Deque_Pop_Front(dqp, &payload_ptr));
  REQUIRE(kTwo == payload_ptr);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);

  // Free the non-empty deque.
  Deque_Free(dqp);
  dqp = NULL;
}

TEST_CASE("Test_Deque", "[PushPop_Back]") {
  // Creating a deque.
  Deque *dqp = Deque_Allocate();
  REQUIRE(dqp != NULL);
  REQUIRE(0 == Deque_Size(dqp));
  REQUIRE(NULL == dqp->front);
  REQUIRE(NULL == dqp->back);

  // Insert an element.
  rat_num payload_ptr;
  Deque_Push_Back(dqp, kOne);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);
  REQUIRE(Deque_Peek_Back(dqp, &payload_ptr));
  REQUIRE(kOne == payload_ptr);
  

  // Delete the element.
  REQUIRE(Deque_Pop_Back(dqp, &payload_ptr));
  REQUIRE(kOne == payload_ptr);
  REQUIRE(0 == Deque_Size(dqp));
  

  // Delete the element a second time.
  REQUIRE_FALSE(Deque_Peek_Back(dqp, &payload_ptr));
  REQUIRE_FALSE(Deque_Pop_Back(dqp, &payload_ptr));
  REQUIRE_FALSE(Deque_Peek_Back(dqp, &payload_ptr));
  

  // Insert two elements.
  Deque_Push_Back(dqp, kOne);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);

  Deque_Push_Back(dqp, kTwo);
  REQUIRE(2 == Deque_Size(dqp));
  REQUIRE(dqp->front != dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(dqp->back == dqp->front->next);
  REQUIRE(dqp->front == dqp->back->prev);
  REQUIRE(kOne == dqp->front->payload);
  REQUIRE(kTwo == dqp->back->payload);
  REQUIRE(Deque_Peek_Back(dqp, &payload_ptr));
  REQUIRE(kTwo == payload_ptr);
  

  // Delete the first element.
  REQUIRE(Deque_Pop_Back(dqp, &payload_ptr));
  REQUIRE(kTwo == payload_ptr);
  REQUIRE(1 == Deque_Size(dqp));
  REQUIRE(dqp->front == dqp->back);
  REQUIRE(NULL == dqp->front->prev);
  REQUIRE(NULL == dqp->back->next);
  REQUIRE(kOne == dqp->front->payload);
  

  // Delete the non-empty deque.
  Deque_Free(dqp);
  dqp = NULL;
}

TEST_CASE("Test_DQIterator", "[Basic]") {
  // Create a deque.
  Deque *dqp = Deque_Allocate();

  // Add some data to the deque.
  Deque_Push_Back(dqp, kFive);
  Deque_Push_Back(dqp, kFour);
  Deque_Push_Back(dqp, kThree);
  Deque_Push_Back(dqp, kTwo);
  Deque_Push_Back(dqp, kOne);

  // Create the iterator.
  DQIterator *dqi = DQIterator_Allocate(dqp);
  REQUIRE(dqi != NULL);
  REQUIRE(dqp == dqi->deque);
  REQUIRE(dqp->front == dqi->node);
  

  // Navigate using the iterator.
  rat_num payload;
  DQIterator_Get(dqi, &payload);
  REQUIRE(kFive == payload);
  REQUIRE(DQIterator_Next(dqi));
  DQIterator_Get(dqi, &payload);
  REQUIRE(kFour == payload);
  REQUIRE(DQIterator_Next(dqi));
  DQIterator_Get(dqi, &payload);
  REQUIRE(kThree == payload);
  REQUIRE(DQIterator_Next(dqi));
  DQIterator_Get(dqi, &payload);
  REQUIRE(kTwo == payload);
  REQUIRE(DQIterator_Next(dqi));
  DQIterator_Get(dqi, &payload);
  REQUIRE(kOne == payload);
  REQUIRE_FALSE(DQIterator_Next(dqi));
  REQUIRE_FALSE(DQIterator_IsValid(dqi));
  

  // The deque contains 5 elements; try a delete from the front of the deque.
  DQIterator_Rewind(dqi);
  DequeNode *prev,
    *next = dqi->node->next,
    *nextnext = dqi->node->next->next;
  REQUIRE(DQIterator_Remove(dqi));
  REQUIRE(next == dqp->front);
  REQUIRE(next == dqi->node);
  REQUIRE(NULL == dqi->node->prev);
  REQUIRE(nextnext == dqi->node->next);
  REQUIRE(4 == Deque_Size(dqi->deque));

  DQIterator_Get(dqi, &payload);
  REQUIRE(kFour == payload);
  

  // Delete the rest, but move the iterator forward by one to test removing
  // from the middle (ie, the 2nd element).
  REQUIRE(DQIterator_Next(dqi));
  prev = dqi->node->prev;
  next = dqi->node->next;
  nextnext = dqi->node->next->next;
  REQUIRE(DQIterator_Remove(dqi));
  REQUIRE(3 == Deque_Size(dqi->deque));
  REQUIRE(next == dqi->node);
  REQUIRE(prev == dqi->node->prev);
  REQUIRE(nextnext == dqi->node->next);
  REQUIRE(prev->next == dqi->node);
  REQUIRE(dqi->node == nextnext->prev);

  // We're stidq deleting from the middle (ie, the 2nd element).
  next = dqi->node->next;
  prev = dqi->node->prev;
  REQUIRE(DQIterator_Remove(dqi));
  REQUIRE(2 == Deque_Size(dqi->deque));
  REQUIRE(next == dqi->node);
  REQUIRE(prev == dqi->node->prev);
  REQUIRE(NULL == dqi->node->next);
  REQUIRE(prev->next == dqi->node);

  // This deletes from the back position, since we are at the second element of
  // a two-element deque.
  prev = dqi->node->prev;
  REQUIRE(DQIterator_Remove(dqi));
  REQUIRE(1 == Deque_Size(dqi->deque));
  REQUIRE(NULL == dqi->node->next);
  REQUIRE(prev == dqi->node);
  REQUIRE(NULL == dqi->node->prev);
  REQUIRE(prev == dqp->back);  // edge case found 17sp

  // Remove the remaining node from the deque.
  REQUIRE_FALSE(DQIterator_Remove(dqi));
  REQUIRE(0 == Deque_Size(dqi->deque));
  REQUIRE(NULL == dqi->node);
  REQUIRE(NULL == dqp->front);
  REQUIRE(NULL == dqp->back);

  // Free the iterator.
  DQIterator_Free(dqi);
  

  // Free the deque.
  Deque_Free(dqp);
}


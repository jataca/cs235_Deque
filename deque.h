/***********************************************************************
 * Header:
 *    Lesson 04, deque
 *    Brother Helfrich, CS 235
 * Author:
 *   Jacob Casperson <8 Hrs>
 *   Justin Stucki   <2 Hrs>
 * Summary:
 *    This header contains the necessary methods and variables to mimic
 *    the std deque container.
 *    The hardest part was a mix between getting the deque pointers
 *    working correctly and learning how to correctly throw exceptions
 ************************************************************************/
#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>

/********************************************
* DEQUE (template) - CLASS DEFINITION
* Meant to behave the same as the std::deque
********************************************/
template <class T>
class Deque
{
  public:
   //Default Constructor
   Deque<T>()
   : data(NULL), numItems(0), maxItems(0), iHead(1), iTail(0) {}

   //Non-Default Constructor              //Could throw
   Deque<T>(int maxItems)                 throw (const char*)
   : data(NULL), numItems(0), maxItems(0), iHead(1), iTail(0)
   {
      if (maxItems > 0)      //Check that Resize wont just *0
         resize(maxItems);   //Resize to new capacity
   }

   //Copy Constructor                     //Could throw
   Deque<T>(const Deque<T> & rhs)         throw (const char*)
   : data(NULL), numItems(0), maxItems(0), iHead(1), iTail(0)
   {
      *this = rhs;
   }
   //Destructor
   ~Deque()
   {
      if (NULL != data)   //Check if empty pointer
         delete [] data;  //Delete allocated memory
   }
   //Modifier functions
   void push_front(const T & t) throw (const char*);
   void pop_front ()            throw (const char*);
   void push_back (const T & t) throw (const char*);
   void pop_back  ()            throw (const char*);
   void clear     () { numItems =0; iHead = 1; iTail = 0; }
   //Getter functions
   bool empty   ()   const { return numItems == 0; }
   int  size    ()   const { return numItems;      }
   int  capacity()   const { return maxItems;      }

   //Overloaded Assignment Operator
   Deque<T> & operator =  (const Deque<T> & rhs);

   //Return data at iHead, the front of the deque
   T & front() throw (const char*)
   {
      if (numItems < 1)
         throw "ERROR: unable to access data from an empty deque";
      else
         return data[iHead];
   }
 
   //Return data at iTail, the back of the deque
   T & back () throw (const char*)
   {
      if (numItems < 1)
         throw "ERROR: unable to access data from an empty deque";
      else
         return data[iTail];
   }

  private:
   void resize(int newMaxItems) throw (char*);    //Grow deque
   T *  data;               //Pointer to array
   int  maxItems;           //Capacity of array
   int  numItems;           //Number of items currently in deque
   int  iHead;              //Index of front of deque
   int  iTail;              //Index of back of deque
};

/******************************************
 * DEQUE (template) - PUSH FRONT
 * Adds an element to the head of the deque
 ******************************************/
template <class T>
void Deque<T> :: push_front(const T & t) throw (const char*)
{
   if (empty())               //Resize if empty
      resize(1);
   if (numItems == maxItems)  //Resize if full
      resize(maxItems * 2);
   
   if (iHead == 1)            //Make sure iHead
      iHead -= 1;             // in the right place
   else
      iHead = (iHead + maxItems - 1) % maxItems;
   data[iHead] = t;           //Place element in deque
      
   numItems++;                //Keep tally of items
}


/******************************************
* DEQUE (template) - PUSH BACK
* Adds an element to the tail of the deque
******************************************/
template <class T>
void Deque<T> :: push_back(const T & t) throw (const char*)
{
   if(empty())                //Resize if empty
      resize(1);
   if (numItems == maxItems)  //Resize if full
      resize(maxItems * 2);
  iTail = (iTail + maxItems + 1) % maxItems;  
  data[iTail] = t;            //Place data in deque

  numItems++;                 //Keep tally of items
}


/**********************************************
* DEQUE (template) - POP FRONT
* Removes an element from the head of the deque
***********************************************/
template <class T>
void Deque<T> :: pop_front() throw (const char*)
{
   if (numItems < 1) // throw if there's nothing to pop
      throw "ERROR: unable to pop from the front of empty deque";
   //if iHead doesn't equal max item increment iHead
   if (iHead != maxItems - 1)
   {
      iHead++;
      numItems--;
   }
   //otherwise set iHead to 0
   else
   {
      iHead = 0;
      numItems--;
   }
}

/**********************************************
* DEQUE (template) - POP BACK
* Removes an element from the back of the queue
***********************************************/
template <class T>
void Deque<T> :: pop_back() throw (const char*)
{
   if (numItems < 1) // throw if there's nothing to pop
      throw "ERROR: unable to pop from the back of empty deque";
   // if iTail doesn't = 0 decrement iTail
   if (iTail != 0)
   {
      iTail--;
      numItems--;
   }
   //otherwise set iTail to the end
   else
   {
      iTail = maxItems -1;
      numItems--;
   }
}

/******************************************
* DEQUE (template) - = OPERATOR
* Overloaded '=' operator
* Adapted from example from Bro.Helfrich
******************************************/
template <class T>
Deque<T> & Deque<T>::operator = (const Deque<T> & rhs)
{
   numItems = 0;                       //Clear old data from receiving object

   if (rhs.maxItems > maxItems)        //Resize if necessary
      resize(rhs.maxItems);

   numItems = rhs.numItems;            //Copy new data into old

   for (int i = 0; i < numItems; i++)  //Copy old data from the old queue
      data[i] = rhs.data[(rhs.iHead + i) % rhs.maxItems];

   return *this;
}

/**************************************
* DEQUE (template) - RESIZE
* Reallocates a larger capacity
* Adapted from example from Bro.Helfrich
**************************************/
template <class T>
void Deque<T> :: resize(int newMaxItems) throw (char*)
{
   //Check for valid capacity
   if (newMaxItems < 0 || newMaxItems < maxItems)
      return;                        //Do nothing if invalid new capacity

   T * pNew;                         //Create new variable
   try                               //Error check
   {
      pNew = new T[newMaxItems];     //Bad allocation?
   }
   catch (std::bad_alloc)            //Show error for bad alloc
   {
      throw "ERROR: Unable to allocate a new buffer for the deque\n";
      return;
   }

   //Resize and copy data into new array
   for (int iNew = 0; iNew < maxItems; iNew++)
   {
      if (iHead != maxItems -1)
      {
         pNew[iNew] = data[iHead];
         iHead++;
      }
      else
      {
         pNew[iNew] = data[iHead];
         iHead = 0;
      }
   }

   iHead = 0;                        //Reset indicies
   iTail = numItems - 1;
   delete [] data;                   //Delete old set
   data = pNew;                      //Make the swap
   maxItems = newMaxItems;           //Set new capacity
  }

#endif

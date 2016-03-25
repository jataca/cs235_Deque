/***********************************************************************
* Implementation:
*    NOW SERVING
* Summary:
*    This contains the implementation for nowServing() 
* Author
*    Justin Stucki <2.5 Hrs>
*    The hardest part was probably just solving infinite loops if data
*    wasn't entered correctly. Asserts fixed this well.
*    Sorry if the std:: get annoying, but i was under the impression
*    we need to remove the namespace std - correct me if I'm wrong
**********************************************************************/
#include <iostream>
#include "nowServing.h" // for nowServing() prototype
#include <string>
#include <cassert>
#include "deque.h"      // for DEQUE

/************************************************
 * WAITING - CLASS DEFINITION
 * This class contains all the methods to parse a 
 * help request, get data, and store variables for
 * a student waiting for help
 ***********************************************/
class Waiting
{
   public:
      //Default constructor
      Waiting() : emergency(false), className(), student(), minutes(0) {}
      //Method to get data from the request string
      bool parse(std::string &input);
      //Accessor functions
      bool        getEmergency()   const { return emergency; }
      std::string getClass    ()   const { return className; }
      std::string getStudent  ()   const { return student;   }
      int         getMinutes  ()   const { return minutes;   }
      //Modifier method
      void decMinutes ()            { minutes--;        }
   private:   
      bool        emergency;   //If a request is an emergency
      std::string className;   //Class student is in
      std::string student;     //Name of student
      int         minutes;     //Minutes needed for help
};

/************************************************
 * PARSE - WAITING CLASS
 * This method decides if a request is an emergency
 * and stores data appropriately
 ***********************************************/
bool Waiting::parse (std::string &input)
{
   std::cin >> input;                 //Get first part of input
   switch (input[0])                  //Figure out what type of request
   {
      case 'n':                       //Do nothing
      case 'f':                       //Finished
         return false;                //Return without any student info
      case '!':                       //If an emergency
         emergency = 1;               //Set emergency flag
         std::cin >> input;           //Prep for default case
      default:
         className = input;           //First input goes in className
         std::cin >> student;         //Get student name
         std::cin >> minutes;         //Get minutes needed
         assert(className != "");     //Check that info isn't missing
         assert(student   != "");     //Check that info isn't missing

                                      //This assert always fires even with
//         assert(std::cin.fail());   //correct input and I don't understand
                                      //why, any ideas?
         
         return true;                 //Return that there is info to store
   }
}

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   //Instructions
   std::cout << "Every prompt is one minute.  "
             << "The following input is accepted:\n"
   << "\t<class> <name> <#minutes>    : a normal help request\n"
   << "\t!! <class> <name> <#minutes> : an emergency help request\n"
   << "\tnone                         : no new request this minute\n"
   << "\tfinished                     : end simulation\n";

   std::string input;            //Input request
   Deque<Waiting> line;          //Line of student waiting
   int timeElapsed = 0;          //Time elapsed counter
   Waiting current;              //Current student being helped
   bool currentHelping = false;  //Assistant currently helping student

   do                            //Loop until input == finished
   {
      //Display timeElapsed
      std::cout << "<" << timeElapsed << "> ";
      //If a new person awaits add them to the list
      Waiting request;
      if (request.parse(input))
         //Push emergencies to the front
         request.getEmergency() ?
            line.push_front(request):
            line.push_back(request) ;
      //Bring first in line out of line to be helped
      if (!currentHelping && !line.empty())
      {
         currentHelping = true;
         current = line.front();
         line.pop_front();
      }
      //Output for helping emergencies
      if (currentHelping && current.getEmergency())
         std::cout << "\tEmergency for " << current.getStudent()
                   << " for class " << current.getClass()
                   << ". Time left: " << current.getMinutes() << std::endl;
      //Ouput for regular helping
      else if (currentHelping)
         std::cout << "\tCurrently serving " << current.getStudent()
                   << " for class " << current.getClass()
                   << ". Time left: " << current.getMinutes() << std::endl;
      //Decrement minutes left of help needed
      current.decMinutes();
      //If time left == 0, assistant isn't helping them anymore
      if (!current.getMinutes())
         currentHelping = false;
      //Increment time elapsed
      timeElapsed++;
   }
   while (input != "finished");

   // finished!
   std::cout << "End of simulation\n";
}



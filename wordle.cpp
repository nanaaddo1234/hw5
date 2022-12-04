// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
std::string combocreator(std::string wrdchk,const std::set<std::string>& dict,std::vector<int> alphas,std::vector<int> alphastwo);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::vector<int> alphas; // determine the unknown positions to be filled with the alphabet, after the floating has been filled in
    std::string wrdchk = "";
    if(wrdchk.length() == 0){
      wrdchk = in;
    }
   // how to avoid resetting
    std::string saver; // to save chars erased from floater to aid recursion
    std::string floater = "";  
    floater = floating;
    
   // how to avoid resetting
    std::set<std::string> validwords;
    
    
    
    if(floater.length() == 0 ){    // base case for recursion when changeable array of floating character is empty
                                   //now it is time to create all possibilities with remaining blanks
      for(int i = 0;i < wrdchk.length(); i++){ 
        if(wrdchk.substr(i,1) == "-"){        //iterate through word and find blanks
          alphas.push_back(i);                    // add them to a vector that stores ther position
          wrdchk.substr(i,1) =(char)(65);       // initialize each of the remaining blanks to a's to start 
        }
      }
     std::vector<int> alphastwo = alphas; // created so that we can retain the positions that iterate through whole alphabet
      if(dict.find(wrdchk) != dict.end()){
         validwords.insert(wrdchk);  //check for case when their is all a's in blanks, since helper func won't
      }
     validwords.insert(combocreator(wrdchk,dict,alphas,alphastwo)); // check all combos after floating character have been placed in spots
     return validwords;  // return set 
    }

    else{
          for(int q = 0; q < wrdchk.length(); q++){      // iterate through word
            if(wrdchk.substr(q,1) == "-" &&  floater.length() > 0){
               wrdchk.substr(q,1) = floater.front();    //oldest character in floater into blank
              saver.push_back(floater.front());          //add that character to saver
               floater.erase(0,1);                       // remove it from floater so that the same character isn't added twice
               wordle(in,floating,dict);                  // recurse
                wrdchk.substr(q,1) = "-";                //after we return to previous recursion, delete the filled in character so we can backtrack
                floater.push_back(saver.back());         // return the char to floater so it can be set again in a new position
                saver.pop_back();                         
            }
          }
        }
       return validwords;
}
    


    

    



// Define any helper functions here
std::string combocreator(std::string wrdchk, const std::set<std::string>& dict, std::vector<int> alphas,std::vector<int> alphastwo ){
  std::vector<int>::iterator itr;
  
  if(wrdchk[alphas.back()] == (char)(90)){     
    while(wrdchk[alphas.back()] == (char)(90)){
      if(alphas.size() == 0){ 
        break;
      }
      wrdchk[alphas.back()] = (char)(65);
      alphas.pop_back();
      
    }
  }
  
  if(alphas.size() == 0){   //check to see if all z's in blanks case is a word
        if(dict.find(wrdchk) != dict.end()){
                return wrdchk;   //if the word is part of a the dictionary return it 
        }
        else{
               return "";
        }
  }

 if(alphas.size() != 0){
    for(int j = 0; j < wrdchk.length(); j++){
      itr = find (alphas.begin(), alphas.end(), j); // see if j is part of alphas meaning it is one of the pos that goes A-Z
      if(itr!= alphas.end() && j == alphas.back()){ // if j is apart of alphas we must be on the last pos, because (if the alphabet was only a-c) the order of my iteration for the blank spaces is aaa aab aac aba abb abc aca 
          for(int q = 0; q < 26; q++){                         // when there are all z's everything would be popped out of alpha, so the func would exit
            if(wrdchk[j] == (char)(65+q)){
              wrdchk[j] = (char)(66+q);
              if(alphas.size() != alphastwo.size()){     //if alphas.size() != the const vector.size() , set them equal to retain original positions
                alphas = alphastwo;
              }
              combocreator(wrdchk,dict,alphas,alphastwo);  // recurse to find other possible words
              if(dict.find(wrdchk) != dict.end()){
                return wrdchk;   //if the word is part of a the dictionary return it, wrong  
              }
              else{
                 return "";
              }

            }  
          } 
      } 
    }
  }
 
  return "";

}

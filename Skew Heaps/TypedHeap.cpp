using namespace std;

#include "TypedHeap.h"


void TypedHeap::insertToHeaps(vector<string> vec){


  //use isdigit and stoi
  
  int size = vec.size();
  int stringSize;

  bool check = false;

  int count = 0;

  //loop through vector
  for(int i =0; i < size; i++){
    //while(count < size && check == false){

    vec.at(i).erase(0,vec.at(i).find_first_not_of(' '));
    vec.at(i).erase(vec.at(i).find_last_not_of(' ') + 1);


    stringSize = vec.at(i).length();
        
    //loop through string
    //for(int j = 0; j < stringSize && check != true; j++){
    while(count < stringSize && check == false){
    
      //it's a string
      if(!isdigit(vec.at(i)[count])){
	
	stringHeap.insert(vec.at(i));
	
	check = true;	
      }	


      count++;
    }
    
    //it's an int
    if(check == false){
      
      intHeap.insert(stoi(vec.at(i)));

      //      cout << stoi(vec.at(i)) << endl;
    }

    check = false;
    count = 0;
    
  }
    
  }


void TypedHeap::combineHeaps(){

  //totalHeap = intHeap;
  totalHeap.skewHeapMerge(intHeap);
  
  totalHeap.skewHeapMerge(stringHeap);
}

void TypedHeap::printHeaps() const{

  cout << "IntHeap Holds:" << endl;

  if(intHeap.empty() == false){

    intHeap.dump();
  }
  
  cout << "StringHeap Holds:" << endl;

  if(stringHeap.empty() == false){
    
    stringHeap.dump();

  }
  
  cout << "TotalHeap Holds:" << endl;

  if(totalHeap.empty() == false){
    totalHeap.dump();

  }
}


void TypedHeap::changePriority(pri_fn pri){

  intHeap.setPriFn(pri);

  stringHeap.setPriFn(pri);

  totalHeap.setPriFn(pri);

}

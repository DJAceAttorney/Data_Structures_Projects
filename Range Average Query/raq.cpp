#include "raq.h"
#include <iostream>
#include <cmath>

RAQ::RAQ(std::vector<float> data){
    
  float average;
  int currAverages = 1;
  int numAmount;
  _size = data.size();


  _averagesVECT.resize(_size);
  
  for(int i = 0; i < _size; i++){
    _averagesVECT.at(i).resize(_size);
    
  }
    

  //while we aren't at the end of the vector
  for(int i = 0; i < _size; i++){
    
    average = data.at(i);
    
    _averagesVECT.at(i).at(i) = average;
      
    
    for(int j = i + 1; j < _size; j++){
      
      //amount of numbers being averaged
      numAmount = j + 1 - i;
      
      //current amount of numbers averaged
      currAverages = numAmount -1;

      //gets average of numbers
      average = ( (currAverages * average) + data.at(j) )  / numAmount;
      
      _averagesVECT.at(i).at(j) = average;
    }
  }
}

//returns the average at the values requested
float RAQ::query(int i, int j) const{
  
  //i or j are incorrect values
  if(j < i || i > _size || j > _size){
    
    throw std::domain_error("RAQ::query selected range is incorrect");
    
  }
  
  return _averagesVECT.at(i).at(j);
      
}

void RAQ::dump() const{

  for(int i = 0; i < _averagesVECT.size(); i++){
	
    for(int j = i; j < _averagesVECT.at(i).size(); j++){
      
      std::cout << _averagesVECT.at(i).at(j) << " ";
	  
    }
    std::cout << std::endl;
  }        
  
}

BlockRAQ::BlockRAQ(std::vector<float> data){
  
  float average;
  _size = data.size();
  _blockSize = (int)sqrt( (float)_size);
  int currIndex;
  
  //copies the values from original to copy vector
  for(int i = 0; i < data.size(); i++){
    _dataValues.push_back(data.at(i));
    
  }
  
  //averages the values in each block
  for(int i = 0; i < _size; i+=_blockSize){
    
    for(int j = i; j < _blockSize + i; j++){
      
      average += data.at(j);
      
      currIndex = j;
    }
    
    average = average / _blockSize;
    _averages.push_back(average);
    
    //resets average
    average = 0;
  }
  
  int counter;
  
  //checks if there were extra values
  bool flag = false;
  
  //averages the remaining values
  for(int i = currIndex + 1; i < _size-1; i++){
    
    average += data.at(currIndex);
    counter++;
    
    flag = true;
  }
  
  if(flag == true){
    
    average = average/counter;
    _averages.push_back(average);
  }
  
}

float BlockRAQ::query(int i, int j) const{
  
  //i or j are incorrect values
  if(j < i || i > _size || j > _size){
    
    throw std::domain_error("BlockRAQ::query selected range is incorrect");
    
  }
  
  int currIndex = i;
  float averages = 0;
  int totalNums= 0;
  
  //keeps track of index of _averages vector
  int counter = i/ _blockSize;
  
  //while we aren't at the end of the range
  while(currIndex <= j){
    
    //If we are at the start of a block
    if(currIndex % _blockSize == 0){
      
      //if j is more than a block away
      if(j > currIndex + (_blockSize -1)){
	
	averages += _averages[counter] * _blockSize;
	
	counter++;
	
	currIndex += _blockSize;
	
	totalNums += _blockSize;
      }
      
      //j is less than a block away
      else{
	
	averages += _dataValues[currIndex];
	
	currIndex++;
	
	totalNums++;
	
      }
    }
    
    //we are not at the start of a block
    else{
      
      averages += _dataValues[currIndex];
      currIndex ++;
      
      totalNums++;
      
      //if we are now in a new block
      if(currIndex % _blockSize == 0){
	
	counter++;
	
      }
    }
  }
  
  averages = averages / totalNums;
	
	
  return averages;
}

void BlockRAQ::dump() const{

  std::cout << "Number of blocks: " << _averages.size() << std::endl;
  
  std::cout << "Block size: " << _blockSize << std::endl;
  
  int counter = 0;
  
  std::cout << "Block averages: " << std::endl;
  
  while(counter < _averages.size()){
    
    std::cout << _averages.at(counter) << " ";
    
    counter++;
  }
  
  std::cout << std::endl;
  
  
}







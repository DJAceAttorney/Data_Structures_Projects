#include "heap.h"
#include "donut.h"
using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

using namespace std;
int main(){


  Heap<Donut> box;

  cout << box.size() << endl;

  if(box.empty() == true)

    cout << "true" << endl;

  else

    cout << "false" << endl;


  if(box.used() == true)
    cout << "true" << endl;
  else
    cout << "false" << endl;


  Donut d1("Plain", 5, "");
  box.insert(d1);
  Donut d2("Super",10,"");
  box.insert(d2);
  Donut d3("Sweet",6,"");
  box.insert(d3);
  Donut d4("Salty",7,"");
  box.insert(d4);
  Donut d5("Strawberry",30,"");
  box.insert(d5);
  Donut d6("Cake",1,"");
  box.insert(d6);
  Donut d7("Blueberry",100,"");
  box.insert(d7);
  Donut d8("Chocolate",2,"");
  box.insert(d8);
  Donut d9("Sour",8,"");
  box.insert(d9);
  
  box.removeTop();
  box.removeTop();
  box.removeTop();

  box.dump();

  return 0;

}
    
  

  
  

  

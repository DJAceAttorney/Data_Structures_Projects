#include <stdexcept>
#include "maze.h"

Maze::Maze(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::Maze(): ncell must be >= 1");
  }

  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

Maze::~Maze() {
  // IMPLEMENT DESTRUCTOR

  delete[] _maze;
  _maze = nullptr;
  
}

void Maze::readFile(std::string fileName) {
  int numCells;
  int cell, n1, n2, n3, n4; 
  std::ifstream dataFile;
  
  dataFile.open(fileName);

  if (dataFile.is_open()) {
    dataFile >> numCells;
    this->reset(numCells);

    for (int i = 0; i < numCells; i++) {
      dataFile >> cell >> n1 >> n2 >> n3 >> n4;
      this->insert(cell_t(cell, n1, n2, n3, n4));
    }
  }
}

int Maze::getNcell() const {
  return _ncell;
}

void Maze::reset(int ncell) {
  if (ncell < 1) {
    throw std::invalid_argument("Maze::reset(): ncell must be >= 1");
  }

  if (_maze != nullptr) {
    delete [] _maze;
  }
  
  _ncell = ncell;
  _maze = new cell_t[_ncell];
}

void Maze::insert(cell_t cell) {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::insert(): attempt to insert into uninitialized Maze object");
  }
  if (cell.cellNum < 0 || cell.cellNum >= _ncell) {
    throw std::invalid_argument("Maze:insert(): invalid cell number");
  }
  _maze[cell.cellNum] = cell;
}
  
cell_t Maze::retrieve(int nc) const {
  if (_maze == nullptr) {
    throw std::domain_error("Maze::retrieve(): attempt to retrieve from an uninitialized Maze object");
  }
  if (nc < 0 || nc >= _ncell) {
    throw std::invalid_argument("Maze:retrieve(): invalid cell index");
  }
  
  return _maze[nc];
}

void Maze::dump() const {

  std::cout << "[*] Dumping the maze cells..." << std::endl;
  
  for (int i = 0; i < _ncell; i++) {
    int nc = _maze[i].cellNum;
    if (nc != i) {
      std::cerr << "Warning: maze cell at index " << i
		<<" has cellNum of " << nc << std::endl;
    }
    std::cout << "Cell " << i << " has neighbor cells: ";
    neighbor_t nbs = _maze[i].neighbors;
    int n0, n1, n2, n3;
    if ( nbs[0] >= 0 ) std::cout << nbs[0] << " ";
    if ( nbs[1] >= 0 ) std::cout << nbs[1] << " ";
    if ( nbs[2] >= 0 ) std::cout << nbs[2] << " ";
    if ( nbs[3] >= 0 ) std::cout << nbs[3] << " ";
    std::cout << std::endl;
  }
}

std::vector<int> Maze::solve() const {
  // IMPLEMENT THE SOLVE METHOD

  //checks if _stack is empty
  if (_ncell == 0){
    throw std::domain_error("Maze::SolveStack::solve attempt to solve on an empty _stack");
  }

  SolveStack solver;

  //copy array of oringal maze
  cell_t *copyMaze = new cell_t[_ncell];

  //copies the value of _maze into copyMaze
  for(int i = 0; i < _ncell; i++){

    copyMaze[i] = _maze[i];

    copyMaze[i].neighbors = _maze[i].neighbors;
    
  }
  
  //vector to hold solution
  std::vector<int> mazeSolution;
  
  //creating starting pair
  src_dest_t cellPair = src_dest_t(VACANT,0);

  mazeSolution.push_back(0);
  
  // SolveStack solver;

  //pushes starting pair into stack
  solver.push(cellPair);

  //holds neighbor cell value
  int neighbor = 0;

  //number to be removed
  int removeNum = 0;

  //boolean to check if neighbor is found
  bool checkN = false;

  //keeps track of current cell
  int currentCell = 0;
  
  std::cout << "[*] Start of call to solve()..." << std::endl;
  
  //while maze can still be solved (haven't reached end and a solution still exists)
  while(currentCell != _ncell-1 && !solver.empty()){
  
    //stores current cell
    currentCell = solver.read().second;
    
    //default value of checkN
    checkN = false;
    
    //going through and finding neigbors
    for(int i =0; i < 4 && !checkN; i++){
    
      //gets neighbor of current cell
      //neighbor = _maze[solver.read().second].neighbors.at(i);
      neighbor = copyMaze[solver.read().second].neighbors.at(i);
      
      //if neighbor hasn't been visited
      if(neighbor != VACANT && neighbor != solver.read().first){
	
	//creates pair with neighbor cell and previous cell
	cellPair = (src_dest_t(solver.read().second, neighbor));

	//pushes pair onto stack
	solver.push(cellPair);

	//adds cell to solution vector
	mazeSolution.push_back(neighbor);
	
	//neighbor was found
	checkN = true;
	     
      }
    }
    
    //checks if neighbor was not found
    if(checkN == false){
      
      //neighbor to be removed
      removeNum = solver.read().second;

      //remove pair from stack
      solver.pop();
      
      //removes cell from solution vector
      mazeSolution.erase(mazeSolution.end() - 1);

      //makes sure stack isn't empty
      if(!solver.empty()){
	
	//changes invalid neighbor to VACANT
	for(int i = 0; i < 4; i++){

	  //if this is the neighbor to remove
	  if(copyMaze[solver.read().second].neighbors.at(i) == removeNum){
	  
	    copyMaze[solver.read().second].neighbors.at(i) = VACANT;
	    
	  }

	}
	
      }
      
    }
  }
  
  //no solution for maze found
  if(solver.empty()){

    std::cout << "[-] No solution found." << std::endl;
  }

  //solution for maze found
  else{

    std::cout << "[+] Solution found!" << std::endl;

    //adds the last cell of the maze into solution vector
    mazeSolution.push_back(_ncell-1);
    
  }

  //deletes copy array
  delete[] copyMaze;
  copyMaze = nullptr;

  

  return mazeSolution;

}


Maze::SolveStack::SolveStack() {
  _stack = nullptr;
}

Maze::SolveStack::~SolveStack() {
  // IMPLEMENT DESTRUCTOR

  //if the stack isn't empty
  if(!empty()){
  
    StackEntry *temp;
    
    //while there are still values in stack
    while(_stack != nullptr){
	  
      temp = _stack -> next;

      delete _stack;
    
      _stack = temp;  
    }
    
    delete temp;
    _stack = nullptr;
    temp = nullptr;
  }
}

bool Maze::SolveStack::empty() const {
  return _stack == nullptr;
}
				   
void Maze::SolveStack::push(src_dest_t src_dest) {

  //new stack entry with numbers given (src_dest pair)
  StackEntry *entry = new StackEntry(src_dest);

  //node after entry to be _stack
  entry ->next = _stack;

  //moving front 
  _stack = entry;

}

src_dest_t Maze::SolveStack::pop() {
 
  //checks if _stack is empty
  if (empty()){
    throw std::domain_error("Maze::SolveStack::pop attempt to pop on an empty _stack");
  }
  
  //creates new pointer to head
  StackEntry *temp = _stack;

  //changes head to next node
  _stack = _stack -> next;

  //value to be returned 
  src_dest_t returnPair = temp ->src_dest;

  delete temp;
  temp = nullptr;
  
  //returns popped pair
  return returnPair;
}

src_dest_t Maze::SolveStack::read() const {
 
  //checks if _stack is empty
  if (empty()) {
    throw std::domain_error("Maze::SolveStack::pop attempt to read on an empty _stack");
  }
    
    return _stack -> src_dest;
  
}

#include <iostream>
using namespace std;

 
int minCoins(int N, int M, int tempArray[], int coins[], int coinsUsed[])
{
  //fills array with dummy values greater than denomination values
  for(int i = 0;i<=N;i++)
    tempArray[i] = N+1;
    
  
  tempArray[0] = 0;
  
  //loops total change amount of times
  for(int i = 1;i<=N;i++)
  {
    
    //loops total denomination amount of times
    for(int j = 0;j<M;j++)
    {
      
      //if coin value is less than or equal to current i
      if(coins[j] <= i)
      {
        //stores the number of coins used  
        tempArray[i] = min(tempArray[i], 1 + tempArray[i - coins[j]]);
        
      }

      //determines which coins to be used for optimal solution
      else{
        coinsUsed[j] = coins[j];
      }
    }
  }
  return tempArray[N];
}

int main() {

  int change = 4;
  int total_coins = 3;

  int tempArray [change+1] = {0};
  int coins[] = {1,2,3};
  int coinsUsed[change] = {0};
  cout << minCoins(change, total_coins, tempArray, coins,coinsUsed) << endl;

  for(int i = 1; i <= minCoins(change, total_coins, tempArray, coins,coinsUsed); i++){
      cout << coinsUsed[i] << endl;

  }

}
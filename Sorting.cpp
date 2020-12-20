#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include "Sorting.h"
using namespace std;

Sorting::Sorting(string fileName)
{
  ifstream file;
  string line;
  file.open(fileName);

  if (file.is_open())
  {
    // make an array for each sorting method
    getline(file, line);
    numOfItems = stoi(line); // number of items to sort (first line of file)
    qsArr = new double[numOfItems];
    msArr = new double[numOfItems];
    ssArr = new double[numOfItems];
    isArr = new double[numOfItems];
    bsArr = new double[numOfItems];

    for (int i = 0; i < numOfItems; i++)
    {
      // fill each array with items from file
      getline(file, line);
      qsArr[i] = stod(line);
      msArr[i] = stod(line);
      ssArr[i] = stod(line);
      isArr[i] = stod(line);
      bsArr[i] = stod(line);
    }
  }

  else
  {
    cout << "File not found." << endl;
  }
  file.close();
}

Sorting::~Sorting()
{
  delete[] qsArr;
  delete[] msArr;
  delete[] ssArr;
  delete[] isArr;
  delete[] bsArr;
}

// runs all the sorting methods
void Sorting::sortAll()

{
  // QUICK SORT
  cout << " " << endl;
  cout << "QUICK SORT:" << endl;

  clock_t qsStart = clock(); // start time
  quicksort(qsArr, 0, (numOfItems-1)); // operation
  clock_t qsEnd = clock(); // end time

  double qsDuration = ((double)(qsEnd - qsStart) / CLOCKS_PER_SEC);
  cout << fixed << "Duration: " << qsDuration << " seconds" << endl;


  //  MERGE SORT
  cout << " " << endl;
  cout << "MERGE SORT:" << endl;

  clock_t msStart = clock();
  mergeSort(msArr, 0, (numOfItems-1));
  clock_t msEnd = clock();

  double msDuration = ((double)(msEnd - msStart) / CLOCKS_PER_SEC);
  cout << fixed << "Duration: " << msDuration << " seconds" << endl;

  // SELECTION SORT
  cout << " " << endl;
  cout << "SELECTION SORT:" << endl;

  clock_t ssStart = clock();
  selectionSort(ssArr, numOfItems);
  clock_t ssEnd = clock();

  double ssDuration = ((double)(ssEnd - ssStart) / CLOCKS_PER_SEC);
  cout << fixed << "Duration: " << ssDuration << " seconds" << endl;

  // INSERTION SORT
  cout << " " << endl;
  cout << "INSERTION SORT:" << endl;

  clock_t isStart = clock();
  insertionSort(isArr, numOfItems);
  clock_t isEnd = clock();

  double isDuration = ((double)(isEnd - isStart) / CLOCKS_PER_SEC);
  cout << fixed << "Duration: " << isDuration << " seconds" << endl;

  // BUBBLE SORT
  cout << " " << endl;
  cout << "BUBBLE SORT:" << endl;

  clock_t bsStart = clock();
  bubbleSort(bsArr, numOfItems);
  clock_t bsEnd = clock();

  double bsDuration = ((double)(bsEnd - bsStart) / CLOCKS_PER_SEC);
  cout << fixed << "Duration: " << bsDuration << " seconds" << endl;

}

// QUICK SORT
int Sorting::partition(double numbers[], int lowIndex, int highIndex)
{
   // middle element is the pivot
   int midpoint = lowIndex + (highIndex - lowIndex) / 2;
   double pivot = numbers[midpoint];

   bool done = false;
   while (!done)
   {
      // increment low index
      while (numbers[lowIndex] < pivot)
      {
         lowIndex += 1;
      }
      // decrement high index
      while (pivot < numbers[highIndex])
      {
         highIndex -= 1;
      }

      if (lowIndex >= highIndex)
      {
         done = true;
      }

      else
      {
         // swap low index and high index
         int temp = numbers[lowIndex];
         numbers[lowIndex] = numbers[highIndex];
         numbers[highIndex] = temp;

         // update low index and high index
         lowIndex += 1;
         highIndex -= 1;
      }
   }

   return highIndex;
}

void Sorting::quicksort(double numbers[], int lowIndex, int highIndex)
{
  // check is partition is sorted
   if (lowIndex >= highIndex)
   {
      return;
   }
   // run partion function
   int lowEndIndex = partition(numbers, lowIndex, highIndex);

   // recursively sort
   quicksort(numbers, lowIndex, lowEndIndex);
   quicksort(numbers, lowEndIndex + 1, highIndex);
}

//
// MERGE SORT
void Sorting::merge(double numbers[], int i, int j, int k)
{
   int mergedSize = k - i + 1; // size of merged partition
   int mergePos = 0;
   int leftPos = 0;
   int rightPos = 0;
   int mergedNumbers[mergedSize]; // array for merged numbers

   leftPos = i;
   rightPos = j + 1;

   // add smallest item from left/right partition to merged numbers array
   while (leftPos <= j && rightPos <= k)
   {
      if (numbers[leftPos] <= numbers[rightPos])
      {
         mergedNumbers[mergePos] = numbers[leftPos];
         ++leftPos;
      }
      else
      {
         mergedNumbers[mergePos] = numbers[rightPos];
         ++rightPos;
      }

      ++mergePos;
   }

   // add remaining items to merged numbers if left pos is not empty
   while (leftPos <= j)
   {
      mergedNumbers[mergePos] = numbers[leftPos];
      ++leftPos;
      ++mergePos;
   }

   // add remaining items to merged numbers if right pos is not empty
   while (rightPos <= k)
   {
      mergedNumbers[mergePos] = numbers[rightPos];
      ++rightPos;
      ++mergePos;
   }

   // copy merged numbers into main array
   for (mergePos = 0; mergePos < mergedSize; ++mergePos)
   {
      numbers[i + mergePos] = mergedNumbers[mergePos];
   }
}

void Sorting::mergeSort(double numbers[], int i, int k)
{
   int j = 0;

   if (i < k)
   {
      j = (i + k) / 2;  // find midpoint

      // recursively sort
      mergeSort(numbers, i, j);
      mergeSort(numbers, j + 1, k);

      // merge in the correct order
      merge(numbers, i, j, k);
   }
}

//
// SELECTION SORT
void Sorting::selectionSort(double numbers[], int numbersSize)
{
   int indexSmallest = 0;
   int temp = 0;

   for (int i = 0; i < numbersSize - 1; ++i)
   {
      // find smallest remaining item
      indexSmallest = i;
      for (int j = i + 1; j < numbersSize; ++j)
      {
         if (numbers[j] < numbers[indexSmallest] )
         {
            indexSmallest = j;
         }
      }

      // put smallest item at the front
      int temp = numbers[i];
      numbers[i] = numbers[indexSmallest];
      numbers[indexSmallest] = temp;
   }
}

//
// INSERTION SORT
void Sorting::insertionSort(double numbers[], int numbersSize)
{
   int j = 0;
   int temp = 0;

   for (int i = 1; i < numbersSize; ++i)
   {
      j = i;
      // insert items in correct positions
      while (j > 0 && numbers[j] < numbers[j - 1])
      {
         temp = numbers[j];
         numbers[j] = numbers[j - 1];
         numbers[j - 1] = temp;
         --j;
      }
   }
}

//
// BUBBLE SORT
void Sorting::swap(double *xPos, double *yPos)
{
  int temp = *xPos;
  *xPos = *yPos;
  *yPos = temp;
}

void Sorting::bubbleSort(double numbers[], int numbersSize)
{
  // use swap function until sorted
  for (int i = 0; i < numbersSize-1; i++)
  {
    for (int j = 0; j < numbersSize-i-1; j++)
    {
      if (numbers[j] > numbers[j+1])
      {
        swap(&numbers[j], &numbers[j+1]);
      }
    }
  }
}

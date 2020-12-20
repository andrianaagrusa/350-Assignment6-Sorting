#include <iostream>
#include <string>
using namespace std;

class Sorting
{
public:
  Sorting(string fileName);
  ~Sorting();

  int numOfItems;
  double *qsArr;
  double *msArr;
  double *ssArr;
  double *isArr;
  double *bsArr;

  void sortAll();
  
  // QUICK SORT
  int partition(double numbers[], int lowIndex, int highIndex);
  void quicksort(double numbers[], int lowIndex, int highIndex);

  // MERGE SORT
  void merge(double numbers[], int i, int j, int k);
  void mergeSort(double numbers[], int i, int k);

  // SELECTION SORTED
  void selectionSort(double numbers[], int numbersSize);

  // INSERTION SORT
  void insertionSort(double numbers[], int numbersSize);

  // BUBBLE SORT
  void swap(double *xPos, double *yPos);
  void bubbleSort(double numbers[], int numbersSize);
};

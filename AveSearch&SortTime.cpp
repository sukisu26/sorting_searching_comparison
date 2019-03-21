/**
* AveSearch&SortTime: this program does sequential and binary search, and linear selection sort and bubble sort
*
* Author: WanQi Su                                           
*/
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;

// globle constant variables
const int ROW = 3; 
const int COLUMN = 100;
const int SIZE = 500;

//functions
void fillArrayRandom(int array[]); // this function fills up the array
void printArray(int array[][COLUMN]); // this funtion prints out a two dimensional array
void printArray(int array[][COLUMN], const int size); // this function prints out the binseqArray
void copyArray(int array[], int array2[]); // this function copys an array from another array
void swap(int array[], int index1, int index2); // this function swap the value in the specific index with the value in another index in the array
int sequentialSearch(int array[], int key); // this function does the sequential search for the passing array
int binarySearch(int array[], int key); // this function does the binary search for the passing array
void linearSelectionSort(int array[], int& comparision1, int& exchange1); // this function does the linear selection sort for the passing array
void bubbleSort(int array[], int& comparision2, int& exchange2); // this function does the bubble sort for the passing array
double calAve(int array[][COLUMN]); // this function calcluate the average sort time;
void calSearchAve(int array[][COLUMN]); // this function calculate the comparision time for  searches

int main(){
	//initialization
	const int size = 2;
	int lArray[ROW][COLUMN]; 
	int bArray[ROW][COLUMN];
	int binseqArray[size][COLUMN];
	int a1[SIZE]; // create an array
	int a2[SIZE]; // create another array to copy the first array
	int key = 2; // the key we need to find
	int result; // if item was found, result stores the index of the found item. otherwise, result = -1.
	srand((unsigned)time(NULL));
	
	//print information to test
	for(int i = 0; i < COLUMN; i++){
		int comparision1 = 0;
		int comparision2 = 0;

		int exchange1 = 0;
		int exchange2 = 0;
		
		fillArrayRandom(a1);
		copyArray(a1, a2);
		
		linearSelectionSort(a1, comparision1, exchange1);
		bubbleSort(a2, comparision2, exchange2);
		
		lArray[0][i] = comparision1;
		lArray[1][i] = exchange1;
		lArray[2][i] = lArray[0][i] + lArray[1][i];

		bArray[0][i] = comparision2;
		bArray[1][i] = exchange2;
		bArray[2][i] = bArray[0][i] + bArray[1][i];

		binseqArray[0][i] =  sequentialSearch(a2, key);
		binseqArray[1][i] = binarySearch(a2, key);
		
	}
	
	//print the linear selection sort array
	cout<<"Linear Selection Sort: "<<endl;
	printArray(lArray);
	cout<<endl;
	
	//print the bubble sort array
	cout<<"Bubble sort: "<<endl;
	printArray(bArray);
	cout<<endl;
	
	//print the comparsion between the liear selection sort and the binary sort
	cout<<"Linear Selection Sort VS Bubble Sort: "<<endl;
	cout<<"The average sort time of linearSelectionSort is: "<<calAve(lArray)<<endl;
	cout<<"The average sort time of bubbleSort is: "<<calAve(bArray)<<endl;
	if(calAve(bArray) > calAve(lArray)){
		cout<<"Therefore, linear selection sort is faster than bubble Sort."<<endl;
	}
	else if(calAve(bArray) < calAve(lArray)){
		cout<<"Therefore, bubble Sort is faster than linear selection Sort."<<endl;
	}
	else{
		cout<<"Therefore, the linear selection sort and the bubble sort have the same speed."<<endl;
	}
	cout<<endl;
	
	printArray(binseqArray, size);	
	cout<<"Sequential Search VS Binary Search: "<<endl;
	calSearchAve(binseqArray);
	
	return 0;
}

 // this function fills up the array
void fillArrayRandom(int array[]){

	for(int i = 0; i < SIZE; i++){
		array[i] = rand()%10;   
	}   
}

void printArray(int array[][COLUMN]){
	for(int i = 0; i < ROW; i++){
		if (i == 0){
			cout << "Comparison: ";
		}else if (i == 1){
			cout << "Exchange: ";
		}else{
			cout << "Total: ";
		}
	
		for (int j = 0; j < COLUMN; j++){
			cout << array[i][j] << " ";
		}
		cout<<endl;
	}
}


void printArray(int array[][COLUMN], const int size){
	for(int i = 0; i < size; i++){
		if (i == 0){
			cout << "Sequential Search: ";
		}else{
			cout << "Binary Search: ";
		}
	
		for (int j = 0; j < COLUMN; j++){
			cout << array[i][j] << " ";
		}
		cout<<endl;
	}	
	cout<<endl;
}

// this function copys an array from another array
void copyArray(int array[], int array2[]){
	for(int i = 0; i < SIZE; i++){
		array2[i] = array[i];   
	}   
}

// this function swap the value in the specific index with the value in another index in the array
void swap(int array[], int index1, int index2){
	if(index1 >=0 && index1 < SIZE && index1 >=0 && index1 < SIZE){
		int tmp = array[index1];
		array[index1] = array[index2];
		array[index2] = tmp;
	}
	else{
		cout<<"Your index is out of the boundary"<<endl;   
	}
}


 // this function does the sequential search for the passing array
int sequentialSearch(int array[], int key){
	int comparision = 0; // a variable to store the comparision time
	
	for(int i = 0; i < SIZE; i++){
		comparision++;
		//if array[i] = key, the key is found, return the index i
		if(array[i] ==  key){
			return comparision;
		} 
	}
	
	return comparision;
}

// this function does the binary search for the passing array
int binarySearch(int array[], int key){
	int comparision = 0;
	int mid, start = 0, end = SIZE - 1; // set start to be the index 0 and set end to be the last index of the array
	while(end >= start){
		mid = (start + end) / 2; // mid is the middle position between the start and the end
		if(array[start] < key){
			comparision++; //  when the if statement satisfy, it compares once
			start = start + 1;
		}
		else if(array[start] > key){
			comparision = comparision + 2; // if the if statement does not satisfy, it compares twice
			end = start - 1;
		}
		else{
			comparision = comparision + 2; // when the if statement and the else if statement do not satisfy, it compares twice
			return comparision;   
		}
		comparision++;		
	}
	return  comparision;
}

// this function does the linear selection sort for the passing array
void linearSelectionSort(int array[], int& comparision1, int& exchange1){
	int i, j;
	int jMin; // the index where the minimum value locates at
	for(i = 0; i < SIZE - 1; i++){
		jMin = i; // set the minmun index to be i
		for(j = i + 1; j < SIZE ; j++){
			comparision1++;
			// if array[j] is less than array[jMin], set Jmin to be j to keep that the minimum value stays in Jmin
			if(array[j] < array[jMin]){
				jMin = j;
			}
		}
		comparision1++;
		// set the minimum value to index i
		if(jMin != i){
			swap(array, i, jMin);  
			exchange1++;
		}
	}
}

 // this function does the bubble sort for the passing array
void bubbleSort(int array[], int& comparision2, int& exchange2){
	bool valid;
	int j = 0; // j is used to calculate the run time 
	do{
		valid = false;
		j++;
		// run from 0 to  arraySize - j because each run the last index is sorted.
		for(int i = 0; i < SIZE-j; i++){
			comparision2++;
			if(array[i] > array[i+1]){
				swap(array, i, i + 1);
				valid = true;
				exchange2++;
			}
		}
	}while(valid);
}

//this function calcluate the average sort time
double calAve(int array[][COLUMN]){
	int sum = 0;
	for(int i = 0; i < COLUMN; i++){
		sum = sum + array[2][i];
	}
	return sum/100;
}

//this function calculate the comparision time for  searches
void calSearchAve(int array[][COLUMN]){
	int seqSum = 0;
	int binSum = 0;
	
	// calculate totle comparision for sequential search and binary search
	for(int i = 0; i < COLUMN; i++){
		seqSum = seqSum + array[1][COLUMN];
		binSum = binSum + array[2][COLUMN];
	}
	cout<<"The average sort time of the sequential search is: "<<seqSum/100<<endl;
	cout<<"The average sort time of the binary search is: "<<binSum/100<<endl;
	
	if((seqSum/100) < (binSum/100)){
		cout<<"Therefore, the sequential search is faster than the binary search."<<endl;
	}
	else if((seqSum/100) > (binSum/100)){
		cout<<"Therefore, the binary search is faster than the sequential search."<<endl;
	}
	else{
		cout<<"Therefore, the binary search and the sequential search have the same speed."<<endl;
	}
}

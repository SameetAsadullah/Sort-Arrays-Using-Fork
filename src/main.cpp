#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int main () {
	int size, size1, *arr, *arr1, *arr2;

	cout << "Enter size of 1st array: ";
	cin >> size;
	cout << "Enter size of 2nd array: ";
	cin >> size1;

	arr = new int [size];
	arr1 = new int [size1];

	cout << endl;

	for (int i = 0 ; i < size ; i++) {
		cout << "Enter value " << i + 1 << " for array: ";
		cin >> arr[i];
	}

	cout << endl;

	for (int i = 0 ; i < size1 ; i++) {
		cout << "Enter value " << i + 1 << " for array1: ";
		cin >> arr1[i];
	}

	pid_t pid = fork();

	if (pid > 0) {	//Parent Process
		wait(NULL);
		pid = fork();

		if (pid > 0) {	//Parent Process
			wait(NULL);			
		}

		else if (pid == 0) {	//Child Process
			for (int i = 1 ; i < size1 ; i++) {	//Sorting 2nd array
				int temp = arr1[i], j;
				for (j = i ; j > 0 && temp < arr1[j - 1] ; j--) {
					arr1[j] = arr1[j - 1];
				}
				arr1[j] = temp;
			}

			cout << "Sorted Array 2: ";
			for (int i = 0 ; i < size1 ; i++) {	//Displaying 2nd Array
				cout << arr1[i] << " " ;
			}
			cout << endl;

			exit(1);
		}

		else {
			cout << "Fork Failed" << endl;
		}
	}

	else if (pid == 0) {	//Child Process
		for (int i = 1 ; i < size ; i++) {	//Sorting 1st array
			int temp = arr[i], j;
			for (j = i ; j > 0 && temp < arr[j - 1] ; j--) {
				arr[j] = arr[j - 1];
			}
			arr[j] = temp;
		}

		cout << endl << "Sorted Array 1: ";
		for (int i = 0 ; i < size ; i++) {	//Displaying 1st array
			cout << arr[i] << " " ;
		}
		cout << endl;

		exit(1);
	}

	else {
		cout << "Fork Failed" << endl;
	}

	return 0;
}

#include "stdio.h"

int selection(int array[], int length, int rank);

int main() {
	int arr[] = {1, 6, 4, 3, 2, 5, 0};
	for (int i = 0; i <= 6; i++) {
		printf("%d\n", selection(arr, 7, i));	
	}
}

int selection(int array[], int length, int rank) {

	if (length == 1) {
		return array[0];
	}
	else {
		int pivot = array[length / 2];
		array[length / 2] = array[0];
		array[0] = pivot;

		int left[length];
		int right[length];
		int left_i = 0;
		int right_i = 0;
		for (int i = 1; i < length; i++) {
			if (array[i] <= pivot) {
				left[left_i] = array[i];
				left_i++;
			}
			else {
				right[right_i] = array[i];
				right_i++;				
			}
		}


		if (rank == left_i) {
			return pivot;
		}
		else if (rank < left_i) {

			return selection(left, left_i, rank);
		}
		else {

			return selection(right, right_i, rank - left_i - 1);
		}
	}
}
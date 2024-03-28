#include <fstream>
#include <iostream>
using namespace std;

// function prototype
void displayMatrix(int **array, int row, int col);

int main() {
  // open the file
  ifstream infile;

  infile.open("data.txt");

  // check the file is opened sucessfully or not
  if (!infile) {
    cout << "Open the file Failed!" << endl;
    exit(EXIT_FAILURE);
  } else {
    cout << "Open the file Succeed!" << endl;
  }

  // read the row and column number from the data.txt
  // the first line of the data.txt
  int numRow, numCol;
  infile >> numRow >> numCol;

  // Dynamically allocate memory for 2D array in C++
  int** adjMatrix = new int *[numRow];
  for (int i = 0; i < numRow; i++)
    adjMatrix[i] = new int[numCol];

  // nested for loop to read the 2D matrix into adjMatrix
  for (int i = 0; i < numRow; i++) {
    for (int j = 0; j < numCol; j++) {
      infile >> adjMatrix[i][j];
    }
  }

  // call the function to display the adjacent matrix
  displayMatrix(adjMatrix, numRow, numCol);

  // close the data file
  infile.close();

  // release the memory for the 2D array
  for (int i = 0; i < numRow; i++)
    delete[] adjMatrix[i]; // delete the inner array

  delete[] adjMatrix; // delete the outer array

  return 0;
}

// function definition
void displayMatrix(int **array, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cout << array[i][j] << " ";
    }
    cout << endl;
  }
}
# Young-Tableaux
# Tableau Class Implementation

## Overview
This project provides a C++ implementation to handle operations (addition, subtraction, and formatted display) on multivariate polynomials represented in a map, along with functionalities for manipulating and computing properties of Young tableaux. Key operations include reading tableaux from CSV files, printing, validation, word conversion, insertion algorithms, multiplication, sliding operations, and computation of Schur polynomials.

### Notes
- Each monomial is represented by a vector of integers indicating the degrees of variables, and the map associates these vectors with their corresponding coefficients.
- The empty box of a tableau is represented by the value `0`.

## Code Structure

### Main Classes
- **Tableau**: Represents a tableau and provides various operations on it, including:
  - **Reading and printing** tableau data.
  - **Validating** tableau correctness.
  - **Insertion operations** (bumping and reverse bumping).
  - **Multiplication** using row insertion and sliding techniques.
  - **Word representation** generation (row word and column word).
  - **Computing the Schur polynomial** for a given tableau.
  - A utility function `readMultipleTableau` to read multiple tableaux from a CSV file.
  - **Addition and subtraction** of polynomials with optional scalar multiplication.
  - **Displaying** polynomials in a human-readable format.
  - Checking if a polynomial is **symmetric** (i.e., invariant under permutation of variables).

## Features

### Core Functions
- **Tableau::printTableau()**: Prints the current tableau.
- **Tableau::isValid()**: Validates that rows are weakly increasing and columns are strictly increasing.
- **Tableau::readTableau(const string& filename)**: Reads a tableau from a CSV file.
- **Tableau::tableauInsertion(int x)**: Performs row insertion of a value into the tableau.
- **Tableau::reverse_bumping(int x, int y)**: Removes an inserted value, restoring the tableau's previous state.
- **Tableau::rectification()**: Converts a skew tableau into a standard tableau by sliding elements.
- **Tableau::row_insertion_multiplication(Tableau U)**: Multiplies the current tableau by another using row insertion.
- **Tableau::rectification_multiplication(Tableau U)**: Multiplies using the sliding method.
- **Tableau::schur_polynomial(int variables)**: Computes the Schur polynomial representation of the tableau.
- **Tableau::row_word()** and **col_word()**: Converts the tableau to row or column word representations.
- **Tableau::shape()**: Returns the shape of the tableau.
- **Tableau::erase()**: Frees memory by clearing the tableau.

### File Reading
- **readMultipleTableau(const string& filename)**: Reads multiple tableaux from a CSV file where each tableau is separated by an empty line.

### Polynomial Operations
- **isSymmetricPolynomial(map<vector<int>, int> poly)**: Checks if a polynomial is symmetric.
- **print_poly(map<vector<int>, int> poly)**: Converts the polynomial map into a readable string format.
- **substraction_poly(map<vector<int>, int> poly1, map<vector<int>, int> poly2, coefficient1, coefficient2)**: Performs polynomial subtraction, `(coefficient1 * poly1 - coefficient2 * poly2)`, with optional scalar multipliers.
- **addition_poly(map<vector<int>, int> poly1, map<vector<int>, int> poly2, coefficient1, coefficient2)**: Performs polynomial addition, `(coefficient1 * poly1 + coefficient2 * poly2)`, with optional scalar multipliers.

## Usage

### Running the Program
1. **Create an Empty Tableau Object**:
   ```cpp
   Tableau T;
2. **Initializing a Tableau with given values we use a vector of vectors of the values**:
    ```cpp
   vector<vector<int>> V = {{1, 2}, {3}};
   Tableau T(V);
3. **To read tableau data from a CSV file, call the readTableau method on the Tableau object . The CSV file should contain rows of integers separated by commas, with each row representing a row in the tableau.**:
     ```cpp
    T.readTableau("filename.csv");
4. **Printing the Tableau: To display the tableau in a formatted way, use the printTableau function**:
    ```cpp
    T.printTableau();
5. **Validating the Tableau : To check if the tableau is valid, use the isValid function**:
    ```cpp
    if (T.isValid()) {
        // Tableau is valid
    } else {
        // Tableau is invalid
    }
6. ** Row word : To convert or represent the tableau as row word , use row_word function **:
      ```cpp
      T.row_word();
7. ** Column word : To convert or represent the tableau as column word , use col_word function **:
      ```cpp
      T.col_word();
8. **Retrieving the Shape of the Tableau : To get the shape of the tableau, use the shape method**:
    ```cpp
    vector<int> shape = T.shape();
9. **Clearing the Tableau : To clear the tableau and free memory, use the erase method**:
    ```cpp
    T.erase();
10. **Performing insertion: Insert an integer into the tableau using the bumpTableau method**:
    ```cpp
    T.bumpTableau(x);
11. **Rectification: Convert a skew tableau into a standard tableau using the rectification method**:
     ```cpp
      T.rectification();
12. **Insertion Multiplication: Multiply the current tableau by another using row insertion with row_insertion_multiplication**:
    ```cpp
    T.row_insertion_multiplication(U);
13. **Rectification Multiplication: Multiply using sliding and rectification with rectification_multiplication**:
    ```cpp
    T.rectification_multiplication(U);
14. ** Schur polynomial : To get the schur polynomial corresponding to the tableau and n number of variables**:
    ```cpp
    map<vector<int>,int> poly=T.schur_polynomial(n); 
15. **Converting a Polynomial to a Readable Form: To display the polynomial map in a human-readable format, use print_poly:
    ```cpp
    print_poly(polynomial_map);
16. **Adding or Subtracting Polynomials: Use the addition_poly and subtraction_poly methods to perform operations with optional scalar multipliers**:
    ```cpp
    map<vector<int>,int> result_add = addition_poly(poly1, poly2, coefficient1, coefficient2);
    map<vector<int>,int> result_sub = subtraction_poly(poly1, poly2, coefficient1, coefficient2);

#include <iostream>
using namespace std;

template <typename T>
class Matrix {
private:
  int width;
  int height;
  // Other data representation not shown

public:
  // Initializes the matrix to the appropriate size
  // Implementation not shown.
  Matrix(int num_rows, int num_cols);

  // Provides access to the element at the given position.
  // Both const and non-const versions are available.
  // Implementations not shown.
  const T & at(int row, int col) const;
  T & at(int row, int col);

  class RowIterator {
  private:

    // The matrix this iterator is associated with
    Matrix *mat;
    int row;
    int col;

    // Private constructor. Creates a row iterator associated
    // with the given matrix at the specified row/column
    RowIterator(Matrix* mat_in, int row_in, int col_in)
     : mat(mat_in), row(row_in), col(col_in) { }

    // Anything else you need in the RowIterator class
    
    friend class Matrix;

  public:
    // Public default constructor. Creates a row iterator, but not one
    // that is meaningfully associated with a Matrix or row/column.
    // (Do not use this constructor in your answer.)
    RowIterator() { }

    // REQUIRES: this iterator is a valid, dereferenceable iterator
    // EFFECTS: Provides access the the element that the iterator is
    // currently "pointing" to
    
T&
 operator*(
) const {
      
return mat->at(row,col); 

    }

    // REQUIRES: this iterator is a valid, dereferenceable iterator
    // EFFECTS: Increments the iterator to "point" to the next element in the row
    
RowIterator&
 operator++(
) {
      
col++; 
return *this; 

    }

    // REQUIRES: the iterators being compared are valid iterators from the
    //           same row in the same matrix
    // EFFECTS: Returns whether or not two iterators are "pointing" at the same element
    
bool
 operator==(
RowIterator &rhs
) const {
      
return col == rhs.col; 

    }

    // NOTE: operator!= is not shown, but assumed similar to operator==

  }; // End of RowIterator class

  // REQUIRES: 0 <= row < height
  // EFFECTS: Returns a row iterator for the given row starting at column 0
  RowIterator row_begin(int row) {
    
return RowIterator(this,row,0);

  }

  // REQUIRES: 0 <= row < height
  // EFFECTS: Returns an end iterator for the given row, which represents
  //          "one-past-the-end" of the sequence of values in that row
  RowIterator row_end(int row) {
    
return RowIterator(this,row,width);

  }
}; // End of Matrix class

int main() {

  // Creates a matrix with 3 rows and 4 columns
  Matrix<int> mat(3,4);

  // Assume code is present that fills the matrix with:
  // 7, 2, 6, 7
  // 2, 5, 2, 1
  // 3, 9, 1, 4

  // This code will print out 7, 2, 6, 7 (on newlines)
  auto it = mat.row_begin(0);
  auto end = mat.row_end(0);
  while(!(it == end)) {
    cout << *it << endl;
    ++it;
  }

  // This code will fill the last row of the matrix with 0
  it = mat.row_begin(2);
  end = mat.row_end(2);
  while(!(it == end)) {
    *it = 0;
    ++it;
  }

  // Note that ++ operations may be chained, e.g.
  it = mat.row_begin(0);
  ++(++it);
}
  // it now "points" at the 6 in the first row
// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Matrix_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.

TEST(test_at_constant){
  Matrix *mat = new Matrix;
  Matrix_init(mat,3,2);
  Matrix_fill_border(mat,10);
  const Matrix *cmat = new Matrix(*mat);
  ASSERT_EQUAL(*Matrix_at(mat,1,1),10);
  ASSERT_EQUAL(*Matrix_at(mat,0,0),10);
  ASSERT_EQUAL(*Matrix_at(cmat,1,1),10);
  ASSERT_EQUAL(Matrix_width(cmat),Matrix_width(mat));
  ASSERT_EQUAL(Matrix_width(cmat),3);
  delete cmat;
  delete mat;
}

TEST(test_innit_max){
  Matrix *mat = new Matrix;
  Matrix_init(mat,MAX_MATRIX_WIDTH,MAX_MATRIX_HEIGHT);
  ASSERT_EQUAL(Matrix_width(mat),500);
  ASSERT_EQUAL(Matrix_height(mat),500);
  delete mat; 
}


TEST(test_border_basic){
  
  Matrix *mat = new Matrix;
  Matrix_init(mat,3,3);
  Matrix_fill(mat,3);
  Matrix_fill_border(mat,1);
  ASSERT_EQUAL(*Matrix_at(mat,0,0),1);
  ASSERT_EQUAL(*Matrix_at(mat,0,1),1);
  ASSERT_EQUAL(*Matrix_at(mat,0,2),1);
  ASSERT_EQUAL(*Matrix_at(mat,1,0),1);
  ASSERT_EQUAL(*Matrix_at(mat,1,1),3);
  ASSERT_EQUAL(*Matrix_at(mat,1,2),1);
  ASSERT_EQUAL(*Matrix_at(mat,2,0),1);
  ASSERT_EQUAL(*Matrix_at(mat,2,1),1);
  ASSERT_EQUAL(*Matrix_at(mat,2,2),1);

  delete mat;
}

TEST(test_border_1x1){
  Matrix *mat = new Matrix;
  Matrix_init(mat,1,1);
  Matrix_fill_border(mat,10);
  ASSERT_EQUAL(*Matrix_at(mat,0,0),10);
  delete mat;
}

TEST(test_border_2x2){
  Matrix *mat = new Matrix;
  Matrix_init(mat,2,2);
  Matrix_fill_border(mat,1);
  ASSERT_EQUAL(*Matrix_at(mat,0,0),1);
  ASSERT_EQUAL(*Matrix_at(mat,0,1),1);
  ASSERT_EQUAL(*Matrix_at(mat,1,0),1);
  ASSERT_EQUAL(*Matrix_at(mat,1,1),1);
  delete mat;
}

TEST(test_column_value_min_basic){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  *Matrix_at(mat,1,2) = -1; 
  *Matrix_at(mat,1,3) = 2; 
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,1,3),-1);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,4),2);
  delete mat;
}

TEST(test_column_value_fill){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,0,5),42);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,5),0);
  delete mat;
}

TEST(test_column_value_min_limit){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  *Matrix_at(mat,2,1) = 100; 
  *Matrix_at(mat,2,2) = 6; 
  *Matrix_at(mat,2,3) = 2; 
  *Matrix_at(mat,2,4) = 4; 
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,2,1,5),3);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,2,2,5),2);
  delete mat;
}

TEST(test_column_value_min_tie){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  *Matrix_at(mat,1,0) = 4;
  *Matrix_at(mat,1,1) = 2; 
  *Matrix_at(mat,1,2) = 2; 
  *Matrix_at(mat,1,3) = 4; 
  *Matrix_at(mat,1,4) = 2; 
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,0,0,4),0);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,0,1,4),42);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,0,4),1);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,1,4),2);
  delete mat;
}

TEST(test_column_value_min_last_column_case){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 5, 3);
  Matrix_fill(mat, value);
  *Matrix_at(mat,1,4) = 2; 
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat,1,4,5),4);
  ASSERT_EQUAL(Matrix_min_value_in_row(mat,1,4,5),2);
  delete mat;
}

TEST(test_max_basic){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  *Matrix_at(mat,1,2) = 100; 
  ASSERT_EQUAL(Matrix_max(mat),100);
  delete mat;
}

TEST(test_max_tie){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);
  *Matrix_at(mat,1,2) = 100; 
  *Matrix_at(mat,2,2) = 100; 
  ASSERT_EQUAL(Matrix_max(mat),100);
  delete mat;
}

TEST(test_max_1x1){
  Matrix *mat = new Matrix;
  const int value = 42;
  Matrix_init(mat, 1, 1);
  Matrix_fill(mat, value);
  ASSERT_EQUAL(Matrix_max(mat),42);
  delete mat;
}

TEST(test_row_column_basic){
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 5, 3);
  *Matrix_at(mat,1,2) = 12; 
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,1,2)),1);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,1,2)),2);
  delete mat;
}

TEST(test_row_column_1x1){
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 1, 1);
  *Matrix_at(mat,0,0) = 12; 
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,0)),0);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,0,0)),0);
  delete mat;
}

TEST(test_row_column_start_end){
  Matrix *mat = new Matrix; 
  Matrix_init(mat, 5, 3);
  *Matrix_at(mat,0,0) = 12; 
  *Matrix_at(mat,2,4) = 12;
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,0,0)),0);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,0,0)),0);
  ASSERT_EQUAL(Matrix_row(mat,Matrix_at(mat,2,4)),2);
  ASSERT_EQUAL(Matrix_column(mat,Matrix_at(mat,2,4)),4);
  delete mat;
}

TEST(test_init_width_height_basic){
  Matrix *mat = new Matrix;
  const int width = 5;
  const int height = 3;
  Matrix_init(mat, 5, 3);
  ASSERT_EQUAL(Matrix_height(mat),height);
  ASSERT_EQUAL(Matrix_width(mat),width);

  delete mat;
}

TEST(test_at_basic){
  Matrix *mat = new Matrix;
  Matrix_init(mat,5,3);
  *Matrix_at(mat,1,3) = 13;
  ASSERT_EQUAL(*Matrix_at(mat,1,3),13);
  delete mat;
}

TEST(test_at_start_end){
  Matrix *mat = new Matrix;
  Matrix_init(mat,5,3);
  *Matrix_at(mat,0,0) = 13;
  *Matrix_at(mat,2,4) = 13;
  ASSERT_EQUAL(*Matrix_at(mat,0,0),13);
  ASSERT_EQUAL(*Matrix_at(mat,2,4),13);
  delete mat;
}

TEST(test_fill_basic) {
  Matrix *mat = new Matrix; // create a Matrix in dynamic memory

  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(mat, 3, 5);
  Matrix_fill(mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
    }
  }
  delete mat; // delete the Matrix
}

TEST(test_print_basic){
  Matrix *mat = new Matrix;
  Matrix_init(mat,5,3);
  Matrix_fill(mat,5);
  *Matrix_at(mat,1,2) = 3;
  Matrix_fill_border(mat,1);
  ostringstream actual; 
  Matrix_print(mat,actual);

  ostringstream expected; 
  expected << "5 3\n"
  << "1 1 1 1 1 \n"
  << "1 5 3 5 1 \n"
  << "1 1 1 1 1 \n";

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

TEST(test_print_1x1){
  Matrix *mat = new Matrix;
  Matrix_init(mat,1,1);
  Matrix_fill(mat,5);
  Matrix_fill_border(mat,1);
  ostringstream actual; 
  Matrix_print(mat,actual);

  ostringstream expected; 
  expected << "1 1\n"
  << "1 \n";

  ASSERT_EQUAL(expected.str(), actual.str());

  delete mat;
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.h as needed.


// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

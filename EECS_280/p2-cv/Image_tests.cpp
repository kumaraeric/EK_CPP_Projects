// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

TEST(test_image_width){
Image *img = new Image;
Image_init(img,4,2); 
ASSERT_EQUAL(Image_width(img), 4);
delete img; 
}

TEST(test_image_height){
  Image *img = new Image;
  Image_init(img,4,2); 
  ASSERT_EQUAL(Image_height(img), 2);
  delete img; 
}

TEST(test_fill_basic){
  Image *img = new Image;
  Image_init(img,5,3);
  Pixel color = {1,2,3}; 
  Image_fill(img,color);
  for(int i =0;i<Image_height(img);++i){
    for(int j=0;j<Image_width(img);++j){
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,i,j),color));
    }
  }
  delete img;
}

TEST(test_set_get_basic){

  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel blue = {0, 0, 255};

  Image_init(img, 1, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 1, 0, blue);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,0),red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,0),blue));

  delete img;
}

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.

TEST(test_set_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

TEST(test_spacing_basic) {
  Image *img = new Image;
  string input = "P3 2 \n3\t255 \n255 \t0 \t\t0\n0\n255 0 \n0 0"
  " \t255 \t255 \t\t255 \n\n255 \n0 \t\t0 \n255 \t255 255 255 \n";
  istringstream ss_input(input);
  Image_init(img, ss_input);
  ASSERT_EQUAL(Image_width(img), 2);
  ASSERT_EQUAL(Image_height(img), 3);

  // Should be well behaved when you print it though!
  string output_correct = "P3\n2 3\n255\n255 0 0 0 255 0 \n0 0 255 " 
  "255 255 255 \n0 0 255 255 255 255 \n";

  ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  ASSERT_EQUAL(actual, output_correct);

  delete img;
}

// TEST(test_reading_and_print_horses_300x382) {
//   Image *img = new Image;
//   string filename = "horses_300x382.correct.ppm";
//   string line;
//   string correct = "";
//   ifstream fin,gin;
//   fin.open(filename);
//   while(getline(fin,line)){
//     correct = correct + line +"\n";
//   }
//   fin.close();
//   gin.open(filename);
//   Image_init(img,gin);
//   ASSERT_EQUAL(Image_width(img), 300);
//   ASSERT_EQUAL(Image_height(img), 382);
//   gin.close();
//   ostringstream ss_output;
//   Image_print(img, ss_output);
//   string actual = ss_output.str();
//   ASSERT_EQUAL(actual,correct);
//   delete img;
// }

TEST(test_reading_and_print_dog){
  Image *img = new Image;
  string filename = "dog.ppm";
  string line;
  ifstream gin;
  gin.open(filename);
  Image_init(img,gin);
  ASSERT_EQUAL(Image_width(img), 5);
  ASSERT_EQUAL(Image_height(img), 5);
  gin.close();
  string correct ="P3\n"
"5 5\n"
"255\n"
"0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n255 255 250 126 66 0 126 66 0 126 66 0 "
"255 255 250 \n126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n255 219 183 255 219 183 "
"0 0 0 255 219 183 255 219 183 \n255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n";

  ostringstream ss_output;
  Image_print(img, ss_output);
  string actual = ss_output.str();
  ASSERT_EQUAL(actual,correct);
  delete img;
}
// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here

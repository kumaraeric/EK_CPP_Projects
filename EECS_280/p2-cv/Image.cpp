// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  assert(0<width && width <=MAX_MATRIX_WIDTH);
  assert(0<height && height <=MAX_MATRIX_HEIGHT); 
  img->width=width;
  img->height=height;
  Matrix_init(&img->red_channel,width,height);
  Matrix_init(&img->green_channel,width,height);
  Matrix_init(&img->blue_channel,width,height);
// TODO Replace with your implementation!
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
static void Image_init_channel_fill(Matrix* mat,int counter,int p_value){
  int column = counter%Matrix_width(mat);
  int row = (counter-column)/Matrix_width(mat);
  *Matrix_at(mat,row,column) = p_value;

}

void Image_init(Image* img, std::istream& is) {
  string word;
  int width,height,max;

  for(int count=0;count<4;++count){
    is >> word; 
    if(count==1){
      width = atoi(word.c_str());
    }
    if(count==2){
      height = atoi(word.c_str());
    }
    if(count==3){
      max = atoi(word.c_str());
    }
  }
  assert(max<=MAX_INTENSITY);
  Image_init(img,width,height);

  //checkpoint

  int r_counter = 0;
  int b_counter = 0;
  int g_counter = 0;
  int counter = 0; 

  while(is >> word){
    int p_value = atoi(word.c_str()); 
    assert(p_value <= MAX_INTENSITY); 
    if(counter%3==0){
      Image_init_channel_fill
      (&img->red_channel,r_counter,p_value);
      r_counter++;
    }

    if(counter%3==1){
      Image_init_channel_fill
      (&img->green_channel,g_counter,p_value);
      g_counter++;
    }

    if(counter%3==2){
      Image_init_channel_fill
      (&img->blue_channel,b_counter,p_value);
      b_counter++;
    }

    counter++; 
  }
  
   // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3\n";
  os <<Image_width(img)<<" "<< Image_height(img)<<"\n";
  os <<"255\n";
  string holder;

  for(int i=0;i<Image_height(img);++i){
    holder="";
    for(int j=0;j<Image_width(img);++j){
      holder = holder + to_string(*Matrix_at(&img->red_channel,i,j)) 
      + " " + to_string(*Matrix_at(&img->green_channel,i,j))
      + " " + to_string(*Matrix_at(&img->blue_channel,i,j)) + " ";
    }
    os << holder + "\n";
  } // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return Matrix_width(&img->blue_channel); // TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return Matrix_height(&img->blue_channel);// TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  assert(0<=row&&row<Image_height(img));
  assert(0<=column&&column<Image_width(img));
  Pixel pixel;
  pixel.r = *Matrix_at(&img->red_channel,row,column);
  pixel.g = *Matrix_at(&img->green_channel,row,column);
  pixel.b = *Matrix_at(&img->blue_channel,row,column);
  return pixel;// TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  assert(0<=row&&row<Image_height(img));
  assert(0<=column&&column<Image_width(img));
  *Matrix_at(&img->red_channel,row,column) 
  = color.r; 
  *Matrix_at(&img->green_channel,row,column) 
  = color.g;
  *Matrix_at(&img-> blue_channel,row,column)
   = color.b;// TODO Replace with your implementation!
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  Matrix_fill(&img->red_channel,color.r);
  Matrix_fill(&img->green_channel,color.g);
  Matrix_fill(&img->blue_channel,color.b); // TODO Replace with your implementation!
}

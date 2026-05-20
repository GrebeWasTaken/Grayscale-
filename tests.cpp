//----------------------------------------------------------
// CS162 Assignment Starter Code
// Copyright Andrew Scholer (ascholer@chemeketa.edu)
// Neither this code, nor any works derived from it
//    may be republished without approval.
//----------------------------------------------------------

// Bring in unit testing code and tell it to build a main function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

// Use Approx from doctest without saying doctest::Approx
using doctest::Approx;

//-----------------------------------------------------------------------------------

#include "GrayscaleImage.h"

using namespace std;

// Helpers:

void wipe(GrayscaleImage& img)
{
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      img.setPixel(i, j, 0);
    }
  }
}
void getGradientFill(GrayscaleImage& img)
{
  uint8_t data[3][5] = {
      {0, 63, 127, 191, 255}, {0, 63, 127, 191, 255}, {0, 63, 127, 191, 255}};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      img.setPixel(i, j, data[i][j]);
    }
  }
}

// Tests:
TEST_CASE("constructor")
{
  cout << "1: Basic Contructor" << endl;
  GrayscaleImage g(3, 5);

  REQUIRE(g.getWidth() == 5);
  REQUIRE(g.getHeight() == 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      REQUIRE(g.getPixel(i, j) == 0);
    }
  }
}

TEST_CASE("setPixel")
{
  cout << "2: setPixel" << endl;
  GrayscaleImage g(3, 5);

  REQUIRE(g.getWidth() == 5);
  REQUIRE(g.getHeight() == 3);

  // Test setting a pixel
  g.setPixel(1, 2, 100);
  REQUIRE(g.getPixel(1, 2) == 100);

  // Test that other pixels are unchanged
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 5; j++) {
      if (i == 1 && j == 2)
        continue;
      REQUIRE(g.getPixel(i, j) == 0);
    }
  }
}

TEST_CASE("fill")
{
  cout << "3: fill" << endl;
  GrayscaleImage g(10, 8);

  g.fill(101);

  for (int i = 0; i < g.getHeight(); i++) {
    for (int j = 0; j < g.getWidth(); j++) {
      REQUIRE(g.getPixel(i, j) == 101);
    }
  }
}

TEST_CASE("toString")
{
  cout << "4: toString" << endl;
  GrayscaleImage g(2, 3);
  g.setPixel(0, 1, 100);
  g.setPixel(1, 0, 25);
  g.setPixel(1, 2, 50);

  string produced = g.toString();

  string desired = "0\t100\t0\t\n25\t0\t50\t\n";

  REQUIRE(produced == desired);
}

TEST_CASE("operator==")
{
  cout << "5: Operator ==" << endl;
  GrayscaleImage g(3, 5);
  GrayscaleImage g2(3, 5);
  GrayscaleImage g3(2, 2);

  CHECK(g == g2);
  CHECK(!(g == g3));

  // Try changing pixels and make sure == behaves correctly
  g2.setPixel(2, 4, 100);
  CHECK(!(g == g2));

  g.setPixel(2, 4, 100);
  CHECK(g == g2);

  g2.setPixel(1, 0, 100);
  CHECK(!(g == g2));
}

// TEST_CASE("copy constuctor")
// {
//   cout << "6: Copy ctor" << endl;
//   GrayscaleImage g(3, 5);
//   getGradientFill(g); // Add some stuff to it

//   GrayscaleImage g2(g);
//   REQUIRE(g == g2);

//   // Make sure we have a deep copy
//   wipe(g);

//   GrayscaleImage gradient(3, 5);
//   getGradientFill(gradient);
//   REQUIRE(g2 == gradient);
// }

// TEST_CASE("assignment")
// {
//   cout << "7: Assignment operator" << endl;
//   GrayscaleImage g(3, 5);
//   getGradientFill(g); // Add some stuff to it

//   GrayscaleImage g2(1, 1);
//   g2 = g;
//   REQUIRE(g == g2);

//   // Make sure we have a deep copy
//   wipe(g);
//   GrayscaleImage gradient(3, 5);
//   getGradientFill(gradient);
//   REQUIRE(g2 == gradient);
// }

TEST_CASE("addFrame")
{
  cout << "8: addFrame" << endl;
  GrayscaleImage g(3, 5);
  getGradientFill(g); // Add some stuff to it

  // Make a version with a 1 px border with brightness 111
  GrayscaleImage g2 = g.addFrame(1, 111);

  // These will display if you fail this test
  INFO("g original:\n", g.toString());
  INFO("g2 (frame):\n", g2.toString());

  REQUIRE(g2.getHeight() == 5);
  REQUIRE(g2.getWidth() == 7);
  // Test a few pixels
  REQUIRE(g2.getPixel(0, 2) == 111);
  REQUIRE(g2.getPixel(1, 0) == 111);
  REQUIRE(g2.getPixel(2, 6) == 111);
  REQUIRE(g2.getPixel(4, 3) == 111);
  REQUIRE(g2.getPixel(3, 3) == 127);

  // Make a version with 2 px black border around the 1px 111 border
  GrayscaleImage g3 = g2.addFrame(2, 0);

  // These will display if you fail this test
  INFO("g2:\n", g2.toString());
  INFO("g3:\n", g3.toString());

  REQUIRE(g3.getHeight() == 9);
  REQUIRE(g3.getWidth() == 11);
  // Test a few pixels
  REQUIRE(g3.getPixel(0, 1) == 0);
  REQUIRE(g3.getPixel(2, 4) == 111);
  REQUIRE(g3.getPixel(4, 4) == 63);
}

TEST_CASE("crop")
{
  cout << "9a: crop" << endl;
  GrayscaleImage g(3, 5);
  getGradientFill(g); // Add some stuff to it

  GrayscaleImage g2 = g.crop(0, 0, 2, 3);

  // These will display if you fail this test
  INFO("g original:\n", g.toString());
  INFO("g2 (crop) :\n", g2.toString());

  REQUIRE(g2.getHeight() == 2);
  REQUIRE(g2.getWidth() == 3);

  REQUIRE(g2.getPixel(0, 0) == 0);
  REQUIRE(g2.getPixel(1, 1) == 63);
  REQUIRE(g2.getPixel(1, 2) == 127);

  GrayscaleImage g3 = g.crop(1, 2, 2, 2);

  // These will display if you fail this test
  INFO("g original:\n", g.toString());
  INFO("g3 (crop) :\n", g3.toString());

  REQUIRE(g3.getHeight() == 2);
  REQUIRE(g3.getWidth() == 2);

  REQUIRE(g3.getPixel(0, 0) == 127);
  REQUIRE(g3.getPixel(1, 1) == 191);
}

TEST_CASE("invalid crop")
{
  cout << "9b: invalid crop" << endl;
  GrayscaleImage g(3, 5);

  bool caught = false;

  try {
    GrayscaleImage g3 = g.crop(1, -1, 2, 2);
  } catch (out_of_range& e) {
    caught = true;
  }
  REQUIRE(caught);

  caught = false;
  try {
    GrayscaleImage g3 = g.crop(1, 1, 6, 2);
  } catch (out_of_range& e) {
    caught = true;
  }
  REQUIRE(caught);
}

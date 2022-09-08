// Task 2: Create a class definition for an interactable object in The Sims

#include <iostream>
#include <string>

using namespace std;

class Binder {
public:
  string size;
  string color;

public:
  Binder(string initSize, string initColor) {
    size = initSize;
    color = initColor;
  }
  void changeColor(string newColor) {
    color = newColor;
  }
  void changeSize(string newSize) {
    size = newSize;
  }
};

int main() {
  Binder binderObj1("small", "black");

  binderObj1.changeColor("blue");
  cout << binderObj1.size << ", " << binderObj1.color << " binder";

  return 0;
}

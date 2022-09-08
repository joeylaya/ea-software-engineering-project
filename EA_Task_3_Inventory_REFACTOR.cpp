// Task 3: Improve a simple inventory system for adding and removing objects

#include<iostream>
#include<map>
#include<iterator>
#include<string.h>
#include<stdlib.h>

using namespace std;

class Item {
  public:
    Item(string init_name, float init_price, int init_quantity) {
      name = init_name;
      price = init_price = 0.00;
      quantity = init_quantity = 0;
    }
    void set_name(string);
    void set_price(float);
    void set_quantity(int);

    string get_name();
    float get_price();
    int get_quantity();

  private:
    string name;
    float price;
    int quantity;    
};

class Inventory {
  public:
    Inventory() {
      money = 0.00;
    }
    void add_item();
    void remove_item(string);
    void edit_item_name(string);
    void sell_item(string);

    Item* get_item(string);
    float get_total_money();    
    float get_total_value();
    int get_item_count();

    void display_item(string);
    void display_inventory();

  private:
    map<string, Item*> items;
    float money;
};

void Item::set_name(string new_name)       { name = new_name; }
void Item::set_price(float new_price)      { price = new_price; }
void Item::set_quantity(int new_quantity)  { quantity = new_quantity; }

string Item::get_name()   { return name; }
float Item::get_price()   { return price; }
int Item::get_quantity()  { return quantity; }

void Inventory::add_item() {
  string name;
  float price;
  int quantity;
  cout << "\n\nItem name: ";
  cin >> name;
  cout << "\nItem price: ";
  cin >> price;
  cout << "\nItem quantity: ";
  cin >> quantity;
  items.insert({name, new Item(name, price, quantity)});
}
void Inventory::remove_item(string name) {
  items.erase(name);
}
void Inventory::edit_item_name(string name) {
  Item* item = get_item(name);
  string new_name;
  cout << "\n\nWhat would you like to name it?: ";
  cin >> new_name;
  items.insert({new_name, new Item(new_name, item->get_price(), item->get_quantity())});
  remove_item(name);
}
void Inventory::sell_item(string name) {
  Item* item = get_item(name);
  int quantity;
  cout << "\n\nHow many would you like to sell?: ";
  cin >> quantity;
  int current_quantity = item->get_quantity();
  if (current_quantity < quantity) {
    cout << "\nYou don't have enough in your inventory. Try again later.";
  } else {
    item->set_quantity(current_quantity - quantity);
    float total_price = item->get_price()*quantity;
    money += total_price;
    cout << "\nSale successful! You made $" << total_price;
  }
  if (item->get_quantity() == 0) {
    remove_item(name);
  }
}

Item* Inventory::get_item(string name) {
  auto result = items.find(name);
  if (result != items.end()) {
    return result->second;
  }
  return NULL;
}
float Inventory::get_total_money() {
  return money;
}
float Inventory::get_total_value() {
  float total_value = 0.00;
  map<string, Item*>::iterator it = items.begin();
  while (it != items.end()) {
    Item* item = it->second;
    float price = item->get_price();
    total_value += price;
    it++;
  }
  return total_value;
}
int Inventory::get_item_count() {
  int item_count = 0;
  map<string, Item*>::iterator it = items.begin();
  while (it != items.end()) {
    Item* item = it->second;
    int quantity = item->get_quantity();
    item_count += quantity;
    it++;
  }
  return item_count;
}

void Inventory::display_inventory() {
  cout << "\nInventory"
    << "\nItem count: " << get_item_count()
    << "\nTotal item value: " << get_total_value()
    << "\nTotal money made: " << get_total_money()
    << "\n===================";
  int count = 1;
  map<string, Item*>::iterator it = items.begin();
  while (it != items.end()) {
    Item* item = it->second;
    string name = item->get_name();
    float price = item->get_price();
    int quantity = item->get_quantity();
    cout << "\n" << count << ". " << name << "($" << price << " each): " << quantity << " available";
    it++;
    count++;
  }

  string choice;
  cout << "\n\nEnter an item name to select it or enter 'add': ";
  cin >> choice;
  if (choice == "add") {
    add_item();
  }
  display_item(choice);
}

void Inventory::display_item(string item) {
  auto result = get_item(item);
  if (result == NULL) {
    cout << "\nYou do not have an item with that name. Please look again.";
    display_inventory();
  }

  string name = result->get_name();
  float price = result->get_price();
  int quantity = result->get_quantity();
  cout << "\n" << name
    << "\n==================="
    << "\nPrice: " << price
    << "\nQuantity: " << quantity;

  int choice;
  cout << "\n\nWhat would you like to do?"
    << "\n1. Sell item"
    << "\n2. Rename item"
    << "\n3. Go back to inventory"
    << "\n4. Cancel"
    << "\n\nEnter your choice: ";
    cin >> choice;

    switch(choice) {
      case 1:
        sell_item(item);
        break;
      case 2:
        edit_item_name(item);
        break;
      case 3:
        display_inventory();
        break;
      case 4:
        exit(0);
        break;
      default:
        cout << "\nInvalid choice entered";
        display_item(item);
    }
}

int main() {
  Inventory inventory_system;
  inventory_system.display_inventory();
  return 0;
}

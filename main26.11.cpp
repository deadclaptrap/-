#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Product {
public:
    string Name;
    int Price;
    int Quantity;

    Product(string name, int pr, int q)
    {
        Name = name;
        Price = pr;
        Quantity = q;

    }
    virtual void info(){
        cout << Name << " " << Price << " " << Quantity << endl;
    }

     ~Product(){
        cout << "Product destroyed" << endl;
    }
};
class Fruit: public Product {
public:
    Fruit(
            string Name,
            int Price,
            int Quantity
    ) : Product(
            Name,
            Price,
            Quantity
    ) {}
    void info() override{
        cout << "Fruit! " << " " << Price << " " << Quantity << endl;
    }
    ~Fruit(){
        cout << "Fr destroyed" << endl;
    }
};
class Bread: public Product {
public:
    Bread(
            string Name,
            int Price,
            int Quantity
    ) : Product(
            Name,
            Price,
            Quantity
    ) {}
    void info() override{
        cout << "Bread! " << " " << Price << " " << Quantity << endl;
    }
    ~Bread(){
        cout << "Br destroyed" << endl;
    }
};
class Milk: public Product {
public:
    Milk(
            string Name,
            int Price,
            int Quantity
    ) : Product(
            Name,
            Price,
            Quantity
    ) {}
    void info() override{
        cout << "Milk! " << " " << Price << " " << Quantity << endl;
    }
    ~Milk(){
        cout << "Milk destroyed" << endl;
    }
};

int main ()
{
    ifstream f1("f1.txt");
    string n;
    int p, q;
    vector<Product*> vec;
    while(f1 >> n >> p >> q )
    {
        if (n == "Fruits") {
            Fruit *fr = new Fruit(n, p, q);
            vec.push_back(fr);
        }
        else if  (n == "Milk") {
            Milk *ml = new Milk(n, p, q);
            vec.push_back(ml);
        }
        else if  (n == "Bread") {
            Bread *br = new Bread(n, p, q);
            vec.push_back(br);
        }
        else
        {
            Product *pr = new Product(n, p, q);
            vec.push_back(pr);
        }
    }

    f1.close();
    if(vec.size() == 0)
    {
        cout << "No products!";
    }
    for(int i = 0; i < vec.size(); i++)
    {
        vec[i]->info();
    }
    return 0;
}



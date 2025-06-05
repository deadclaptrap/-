#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <vector>

using namespace std;

class vector3d{
protected:
    int z;
    int y;
    int x;
public:
    vector3d()=delete;
    vector3d(int x1, int y1, int z1)
    {
        x=x1; y= y1; z= z1;
    }
    vector3d (initializer_list<int> lst)
    {
        int i =0;
        for (const auto &l: lst) {
            if(i==0)
                x = l;
            else if(i == 1)
                y = l;
            else if ( i ==2)
                z= l;
            ++i;
        }
    }
    virtual void info() { cout << x << " " << y << " " << z << endl; }
    int get_x(){
        return x;
    }
    int get_y() {
        return y;
    }
    int get_z() {
        return z;
    }
    virtual ~vector3d() {}
};

class vector4d: private vector3d {
public:
    vector4d(int x,int y,int z,int k1) : vector3d(x,y,z)
            { w = k1;}

    vector4d(initializer_list<int> lt) : vector3d(lt)
    {
        int i =0;
        for (const auto &l: lt) {

            if(i==3)
                w = l;
            ++i;
        }

    }

    void info() override{
        cout << "4d "  << x << " " << y  << " " << z << " " << w << endl;
    }
    int get_w() {
        return w;
    }
    ~vector4d(){
       // cout << "destroyed" << endl;
    }
private:
    int w;
};


template <typename T>
class Mainfold {
private:
    T type;
    int n;
    vector<T> folder;
public:
    Mainfold(T id, int n1)
    {
        type = id;
        n =n1;
        cout << "type, vector3d: " << std::is_base_of<T,vector3d>::value << endl;
        folder.push_back(type);
    }
    T get_t() {
        return type;
    }
    void add(T elem){
        if(folder.size() > n)
        {
            cout << "no space!" << endl;
        }
        else{
            folder.push_back(elem);
            cout << "added to folder(vector)" << endl;

        }
    }
    void list(){
        for(int i  = 0; i < n; i++)
        {
            folder[i].info();
        }
    }
};



int main() {
   vector3d one(1,2,3);
   vector4d two(4, 5, 6,7);
   vector4d three({1, 2,3,4});
   one.info();
   two.info();
   three.info();
 
    return 0;
}

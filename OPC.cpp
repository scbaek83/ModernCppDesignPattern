#include <iostream>
#include <string>
#include <vector> 

using namespace std; 

enum class COLOR { RED, GREEN, BLUE }; 
enum class SIZE { SMALL, MEDIUM, LARGE }; 

struct Product {
    string m_name; 
    COLOR  m_color; 
    SIZE   m_size; 
};

// Use using as type alias
using Items = vector<Product*>;

#define ALL(C) begin(C), end(C) 

struct ProductFilter { 
    static Items by_color(Items items, const COLOR e_color) {
        Items result; 
        for (auto &i : items) 
            if (i->m_color == e_color) 
                result.push_back(i);
        return result; 
    }

    static Items by_size(Items items, const SIZE e_size) {
        Items result; 
        for (auto &i : items) 
            if (i->m_size == e_size) 
                result.push_back(i); 
        return result; 
    }

    static Items by_size_and_color(Items items, const SIZE e_size, const COLOR e_color) {
        Items result; 
        for (auto &i : items) 
            if (i->m_size == e_size && i->m_color == e_color) 
                result.push_back(i);
        return result; 
    }
};

int main() 
{
    const Items all{
        new Product{"Apple", COLOR::GREEN, SIZE::SMALL}, 
        new Product{"Tree", COLOR::GREEN, SIZE::LARGE}, 
        new Product{"House", COLOR::BLUE, SIZE::LARGE},
    };

    for (auto &p : ProductFilter::by_color(all, COLOR::GREEN)) 
        cout << p->m_name << " is green\n"; 
    
    for (auto &p : ProductFilter::by_size_and_color(all, SIZE::LARGE, COLOR::GREEN)) 
        cout << p->m_name << " is green & large\n"; 

    return EXIT_SUCCESS; 
}

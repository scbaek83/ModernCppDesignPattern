#include <iostream> 
#include <string>

using namespace std; 

enum class Color { Red, Green, Blue };
enum class Size { Small, Medium, Large };

struct Product 
{
    string name; 
    Color color; 
    Size size; 
};

// struct ProductFilter
// {
//     typedef vector<Product*> Items; 
    
    // ProductFilter::Items ProductFilter::by_color(Items items, Color color)
    // {
    //     Items result; 
    //     for (auto& i : items) {
    //         if (i->color == color)
    //         result.push_back(i); 
    //     }
    // }

    // ProductFilter::Items ProductFilter::by_size(Items items, Size size)
    // {
    //     Items result; 
    //     for (auto& i : items) {
    //         if (i->size == size) 
    //         result.push_back(i); 
    //     }
    // }    

    // ProductFilter::Items ProductFilter::by_color_and_size(Items items, Size size, Color color)
    // {
    //     Items result; 
    //     for (auto& i : items) {
    //         if (i->size == size && i->color == color) 
    //             result.push_back(i); 
    //     }
    //     return result; 
    // }

// };

template<typename T> 
struct Specification
{
    virtual bool is_satisfied(T* item) = 0; 
};

template<typename T> 
struct Filter 
{
    virtual vector<T*> filter(vector<T*> items, Specification<T>& spec) = 0; 
};

struct BetterFilter : Filter<Product> 
{
    vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override 
    {
        vector<Product*> result; 
        for (auto& p : items) {
            if (spec.is_satisfied(p))
                result.push_back(p); 
        }
        return result; 
    }
};

struct ColorSpecification : Specification<Product> 
{
    Color color; 

    explicit ColorSpecification(const Color color) : color{color} {} 

    bool is_satisfied(Product* item) override {
        return item->color == color; 
    }
};

int main(void) 
{
    std::cout << "hello world" << std::endl; 

    Product apple{ "Apple", Color::Green, Size::Small }; 
    Product tree{ "Tree", Color::Green, Size::Large }; 
    Product house{ "House", Color::Blue, Size::Large }; 

    vector<Product*> all{ &apple, &tree, &house }; 

    BetterFilter bf; 
    ColorSpecification green(Color::Green); 

    auto green_things = bf.filter(all, green); 
    for (auto& x : green_things) 
        cout << x->name << " is green" << endl; 

    return 0;
}
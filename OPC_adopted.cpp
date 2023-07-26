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

template <typename T> 
struct Specification {
    virtual ~Specification() = default; 
    virtual bool is_satisfied(T *item) const = 0; 
};

struct ColorSpecification : Specification<Product> 
{
    COLOR e_color; 
    ColorSpecification(COLOR e_color) : e_color(e_color) {} 
    bool is_satisfied(Product *item) const { return item->m_color == e_color; } 
};

struct SizeSpecification : Specification<Product>
{
    SIZE e_size; 
    SizeSpecification(SIZE e_size) : e_size(e_size) {} 
    bool is_satisfied(Product *item) const { return item->m_size == e_size; }
};

template <typename T> 
struct AndSpecification : Specification<T> {
    const Specification<T> &first; 
    const Specification<T> &second; 

    AndSpecification(const Specification<T> &first, const Specification<T> &second)
    : first(first), second(second) {} 

    bool is_satisfied(T *item) const {
        return first.is_satisfied(item) && second.is_satisfied(item); 
    }
};

template <typename T> 
AndSpecification<T> operator &&(const Specification<T> &first, const Specification<T> &second) 
{
    return {first, second}; 
}

template <typename T> 
struct Filter { 
    virtual vector<T*> filter(vector<T*> items, const Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product> {
    vector<Product *> filter(vector<Product*> items, const Specification<Product> &spec) {
        vector<Product*> result; 
        for (auto &p : items) 
            if (spec.is_satisfied(p)) 
                result.push_back(p); 
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

    auto green_things = ColorSpecification{COLOR::GREEN}; 
    auto large_things = SizeSpecification{SIZE::LARGE}; 

    BetterFilter bf; 
    for (auto &x : bf.filter(all, green_things && large_things))
        cout << x->m_name << " is green and large\n"; 

    return EXIT_SUCCESS; 
}

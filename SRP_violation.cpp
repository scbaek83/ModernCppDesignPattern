#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector> 

using namespace std; 

class Journal {
    string m_title; 
    vector<string> m_entries; 

public: 
    explicit Journal(const string &title) : m_title{title} {} 
    void add_entries(const string &entry) {
        static uint32_t count = 1; 
        m_entries.push_back(to_string(count++) + ": " + entry); 
    }

    auto get_entries() const { return m_entries; } 
    void save(const string &filename) {
        ofstream ofs(filename); 
        for (auto &s : m_entries) 
            ofs << s << endl; 
    }
};

int main() 
{
    Journal journal{" Dear XYZ"}; 
    journal.add_entries("I ate a bug"); 
    journal.add_entries("I cried today"); 
    journal.save("diary.txt"); 

    return EXIT_SUCCESS; 
}
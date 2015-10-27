// Buffer.cpp

#include "Buffer.h"

#include <fstream>
#include <iomanip>
#include <iostream>
using std::cout;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;

void Buffer::display() const
{
    int ix_stop_line = ix_top_line + window_height;
    for (int i = ix_top_line; i < ix_stop_line; ++i) {
        if (i < v_lines.size())
            cout << std::setw(6) << i+1 << "  " << v_lines[i];
        cout << '\n';
    }
}

bool Buffer::open(const string & new_file_name)
{
    std::ifstream file(new_file_name);
    if (!file) return false;

    v_lines.clear();
    // Note: the vector is cleared only after we know the file
    // opened successfully.

    string word;
    while (!file.eof())
    {
       if(file.peek() == '<a')
       {
           Anchor anchor();
           file >> anchor;
           add(anchor);
       }
       else
       {
            file >> word;
            add(word);
       }
    }

    file_name = new_file_name;
    ix_top_line = 0;
    return true;
}

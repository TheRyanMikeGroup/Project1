// Buffer.h

#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include "Anchor.h"

class Buffer
{
public:
    void display() const;
    const std::string & get_file_name() const { return file_name; }
    void move_to_next_page();
    void move_to_previous_page();
    bool open(const std::string & file_name);
    void set_window_height(int h) { window_height = h; }
    void set_line_length(int l) { line_length = l; }
    void add(const std::string & word);
    void add(const std::string & file, const std::string & text);


    std::vector<std::string> link_files;

private:
    void parseAnchor(std::ifstream & input);
    std::vector<std::string> v_lines;
    int ix_top_line = 0;
    std::string file_name;
    int window_height;
    int line_length;

};

inline void Buffer::move_to_next_page()
{
    if (ix_top_line + window_height < v_lines.size())
        ix_top_line += window_height;
}

inline void Buffer::move_to_previous_page()
{
    if (ix_top_line > 0) ix_top_line -= window_height;
}

inline void Buffer::add(const std::string & word)
{
    if(v_lines.size() == 0 || v_lines[v_lines.size()-1].size() + word.size()  + 1 > line_length)
        v_lines.push_back(word);
    else
        v_lines[v_lines.size() - 1] += " " + word;


}

inline void Buffer::add(const std::string & file, const std::string & text)
{
    std::string print_text = "<<" + text + ">>";
    print_text += "[";
    print_text += 2;
    print_text += "]";
    add(print_text);
}

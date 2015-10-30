// Buffer.h

#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include <sstream>

#include "Anchor.h"

class Buffer
{
public:
    void display() const;
    void move_to_next_page();
    void move_to_previous_page();
    void set_window_height(int h) { window_height = h; }
    void set_line_length(int l) { line_length = l; }
    void add(const std::string & word);
    void add(const std::string & file, const std::string & text);
    void break_paragraph();

    const std::string & get_file_name() const { return file_name; }

    bool open(const std::string & file_name);
    bool open(const int &index);

    int get_line_length() const { return line_length; }

private:
    std::vector<std::string> v_lines;
    std::vector<std::string> link_files;

    std::string file_name;

    int ix_top_line = 0;
    int window_height;
    int line_length;

    void parse_anchor(std::ifstream & input);
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
    else if(v_lines.back().size() > 0)
        v_lines[v_lines.size() - 1] += " " + word;
    else
        v_lines[v_lines.size() - 1] += word;


}

inline void Buffer::add(const std::string & file, const std::string & text)
{
    link_files.push_back(file);

    std::string print_text = "<<" + text + ">>";
    print_text += "[";

    std::stringstream ss;
    std::string num;
    ss << link_files.size() - 1;
    ss >> num;
    print_text += num;

    print_text += "]";
    add(print_text);
}

inline bool Buffer::open(const int & index)
{
    if(index < link_files.size())
        return open(link_files[index]);
    else
        return false;
}

inline void Buffer::parse_anchor(std::ifstream & input)
{
    std::string text;
    std::string file;

    input >> file;
    input >> text;
    text = text.substr(0, text.size() - 1);

    add(file, text);
}

inline void Buffer::break_paragraph()
{
    v_lines.push_back("");
    v_lines.push_back("");
}

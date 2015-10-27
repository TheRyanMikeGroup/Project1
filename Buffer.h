// Buffer.h

#include <vector>
#include <string>
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
    void add(const std::string & word);
    void add(const Anchor & anchor);


private:
    std::vector<std::string> v_lines;
    int ix_top_line = 0;
    std::string file_name;
    int window_height;
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

inline void add(const std::string & word)
{
    v_lines.push(word);
}

inline void add(const Anchor & anchor)
{
    add(anchor.to_string() + '[' + 2 + ']');
}

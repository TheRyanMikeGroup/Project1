#ifndef ANCHOR
#define ANCHOR

#include <string>
#include <istream>
#include <ostream>


class Anchor
{
    friend std::istream & operator>>(std::istream & input, Anchor & anchor);

public:
    Anchor(): text_(""), file_(""){}
    Anchor(const std::string & text, const std::string & file):
         text_(text), file_(file){}

    std::string text() const {return text_;}
    std::string file() const {return file_;}

    std::string to_string() const {return "<<" + text() + ">>"; }

private:
    std::string text_;
    std::string file_;

};

inline std::ostream & operator<<(std::ostream & output, const Anchor & anchor)
{
    output << anchor.to_string();
}

inline std::istream & operator>>(std::istream & input, Anchor & anchor)
{
    input.get();                                   //Removes the '<'
    input.get();                                   //Remvoes the 'a'
    input.get();                                    //Removes the ' '
    input >> anchor.file_;
    input >> anchor.text_;
    anchor.text_ = anchor.text_.substr(0, anchor.text_.size() - 1);
    anchor.text_.substr(0, anchor.text_.size());
}


#endif // ANCHOR

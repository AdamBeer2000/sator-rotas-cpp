#ifndef WORDRANGE_H
#define WORDRANGE_H

struct WordRange{
    static WordRange Empty;
private:
    int begin;
    int end;
    bool is_empty;
public:
    WordRange(int _begin,int _end):begin(_begin),end(_end)
    {
        is_empty=_end-_begin==0;
    }
    WordRange (){}
    const int size()const
    {
        return end-begin;
    }
    int getBegin() const;
    void setEnd(int newEnd);
    int getEnd() const;
    bool IsEmpty()const;
};

#endif // WORDRANGE_H

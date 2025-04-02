#ifndef WORDNODE_H
#define WORDNODE_H
#include "string"
#include "wordrange.h"
#include <memory>
#include <vector>

class WordNode
{
private:
    std::vector<std::unique_ptr<WordNode>>childrens;
    WordRange myRange;
    int depth=0;
    char lowerIndx;
    char upperIndx;
public:
    WordNode(WordRange myRange,const int depth,const int leafLevel);
    const WordRange Travers(const std::string &prefix)const;
    ~WordNode();
};

#endif // WORDNODE_H

#include "wordnode.h"
#include "worddictionary.h"
#include <climits>

WordNode::WordNode( WordRange myRange, const int depth,const int leafLevel):depth(depth),myRange(myRange)
{
    if (myRange.IsEmpty() ||  leafLevel == depth)
        return;

    char minChar = CHAR_MAX;
    char maxChar = CHAR_MIN;

    for (int indx = myRange.getBegin(); indx < myRange.getEnd(); indx++)
    {
        if ( WordDictionary::Get(indx,depth) < minChar)
            minChar =  WordDictionary::Get(indx,depth);

        if ( WordDictionary::Get(indx,depth) > maxChar)
            maxChar =  WordDictionary::Get(indx,depth);
    }

    this->lowerIndx = minChar;
    this->upperIndx = maxChar;

    childrens=std::vector<std::unique_ptr<WordNode>>(upperIndx - lowerIndx + 1);

    int begin=myRange.getBegin();
    int end=myRange.getBegin();

    int childrenIndx=0;
    for(char ch=lowerIndx;ch<=upperIndx;ch++)
    {
        while(end<myRange.getEnd()&&WordDictionary::Get(end,depth)==ch)
        {
            end++;
        }
        auto wr= WordRange(begin,end);
        childrens[childrenIndx++]=std::make_unique<WordNode>(wr,depth+1,leafLevel);
        begin=end;
        end=begin;
    }
}

const WordRange WordNode::Travers(std::string const &prefix)const
{
    if (prefix.size() == depth||myRange.size()==0)
        return myRange;

    if (prefix[depth] > this->upperIndx || prefix[depth] < this->lowerIndx)
        return WordRange::Empty;

    int indx = prefix[depth] - lowerIndx;

    if (childrens[indx] == nullptr)
        return WordRange::Empty;

    return childrens[indx]->Travers(prefix);
}

WordNode::~WordNode()
{
    childrens.clear();
}

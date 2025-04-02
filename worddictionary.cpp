#include "worddictionary.h"
std::vector<std::string> WordDictionary::Words ;
WordDictionary::WordDictionary() {}

void WordDictionary::setWords(const std::vector<std::string> &newWords)
{
    Words = newWords;
}

std::string WordDictionary::Get(int indx)
{
     return Words[indx];
}

char WordDictionary::Get(int indx,int depth)
{
    return Words[indx][depth];
}

int WordDictionary::Size()
{
    return Words.size();
}

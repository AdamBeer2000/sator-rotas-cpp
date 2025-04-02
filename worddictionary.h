#ifndef WORDDICTIONARY_H
#define WORDDICTIONARY_H

#include <string>
#include <vector>

class WordDictionary
{
private:
    static std::vector<std::string> Words;
public:
    WordDictionary();
    static std::string Get(int index);
    static char Get(int index,int depth);
    static int Size();
    static void setWords(const std::vector<std::string> &newWords);
};

#endif // WORDDICTIONARY_H

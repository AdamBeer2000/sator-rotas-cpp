#ifndef RESULTWRITER_H
#define RESULTWRITER_H

#include <stack>
class ResultWriter
{
private:
    std::stack<int*> results;
    void WriteResults();
public:
    ResultWriter();
    void AddResults();
};

#endif // RESULTWRITER_H

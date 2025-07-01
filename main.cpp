#include <algorithm>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <thread>
#include <vector>
#include <fstream>
#include <memory>

#include "lib/cxxopts/include/cxxopts.hpp"
#include "exceptions.h"
#include "radix.h"
#include "wordnode.h"
#include "worddictionary.h"

using namespace std;

bool IsValidChar(const char character)
{
    return 'A'<=character&&character<='Z'||'a'<=character&&character<='z';
}

void ReadFile(const int WORD_LENGHT,const string & path,std::vector<string>&AllWordsFromFile,bool sorted)
{
    std::ifstream reader=std::ifstream (path);

    if(!reader.is_open())
        throw sator::InvalidPathException(path);

    string nextLine;
    int lineCount=0;
    while(std::getline(reader,nextLine))
    {
        try
        {
            lineCount++;

            if(nextLine.size()!=WORD_LENGHT)
                continue;

            bool isValidStr=std::all_of(nextLine.begin(), nextLine.end(), IsValidChar);

            if(!isValidStr)
            {
                throw sator::InvalidStrException(nextLine,lineCount);
            }

            std::transform(nextLine.begin(), nextLine.end(), nextLine.begin(),
                           [](char c){ return std::tolower(c); });

            AllWordsFromFile.push_back(nextLine);
        }
        catch(const sator::exception & ex)
        {
            cout<<ex.what()<<std::endl;
        }
        catch(const std::exception & ex)
        {
            cout<<"Unhandled exception : "<<ex.what();
            throw;
        }

    }
    reader.close();

    if(AllWordsFromFile.empty())
    {
        throw sator::EmptyFileException(path,WORD_LENGHT);
    }

    AllWordsFromFile.shrink_to_fit();

    if(!sorted)
        radixSort(AllWordsFromFile);
}

int * CreateStartMatrix(const int startWord,const int wordSize)
{
    int * wordMatrix=new int[wordSize];
    wordMatrix[0]=startWord;
    std::memset(&wordMatrix[1], -1, (wordSize-1) * sizeof(int));
    return wordMatrix;
}
int * CreateStartMatrix(int * __restrict__ baseMatrix,const int newWord,const int until,const int wordSize)
{
    int * nextMatrix=new int[wordSize];
    std::memcpy(nextMatrix,baseMatrix,until*sizeof(int));
    nextMatrix[until]=newWord;
    std::memset(&nextMatrix[until+1], -1, (wordSize-until-1) * sizeof(int));
    return nextMatrix;
}

void Scan(std::stack<int*> * ressultContainer,
          int * Matrix,
          const int indx,
          const int wordSize,
          const WordNode * root
          )
{
    if(Matrix[wordSize-1]!=-1)
    {
        ressultContainer->push(Matrix);
        return ;
    }

    if(indx==wordSize)
    {
        delete[] Matrix;
        return;
    }

    string prefix="";
    for(int i=0; i<indx;i++)
    {
        prefix+=WordDictionary::Get(Matrix[i],indx);
    }

    const WordRange wr=root->Travers(prefix);

    if(wr.size()==0)
    {
        delete[] Matrix;
        return;
    }

    for(int wordIndx=wr.getBegin();wordIndx<wr.getEnd();wordIndx++)
    {
        for(int i =0;i<indx;i++)
        {
            if( wordIndx==Matrix[i])
            {
                continue;
            }
        }

        int * nextMatrix=CreateStartMatrix(Matrix,wordIndx,indx,wordSize);
        Scan(ressultContainer,nextMatrix,indx+1,wordSize,root);
    }
    delete[] Matrix;
}

void SerchThread(const int WORD_LENGHT,std::stack<int*> *results,const WordRange & node,const WordNode * root,int wordLenght)
{
    for(int wordIndx=node.getBegin();wordIndx<node.getEnd();wordIndx++)
    {
        int * wordMatrix=CreateStartMatrix(wordIndx,WORD_LENGHT);
        try
        {
            Scan(results,wordMatrix,1,WORD_LENGHT,root);
        }
        catch (std::exception & ex)
        {
            cout<<"Thread run into a exception : "<<ex.what();
        }
    }
}

void RunParaller(const std::string& OUTPUT_PATH,const int WORD_LENGHT,const int threadCount,const WordNode * root, const int wordLenght)
{
    std::vector<std::thread *> threads=std::vector<std::thread *>(threadCount);
    std::vector<std::stack<int*>> threads_res=std::vector<std::stack<int*>>(threadCount);
    int size=WordDictionary::Size();
    int chunkSize=size/threadCount+1;
    int begin;
    int end;

    for(int i=0;i<threadCount;i++)
    {
        begin=i*chunkSize;
        end=std::min(size,(i+1)*chunkSize) ;
        WordRange wr= WordRange(begin,end);
        threads_res[i]=std::stack<int*>();
        std::thread * th= new std::thread(SerchThread,WORD_LENGHT,&threads_res[i],wr,root,wordLenght);
        threads[i]=th;
    }

    for(auto th :threads)
    {
        th->join();
        delete th;
    }

    fstream stream= fstream (OUTPUT_PATH,fstream::out) ;

    std::size_t count=0;

    for(int i=0;i<threadCount;i++)
    {
        count+=threads_res[i].size();
        while(!threads_res[i].empty())
        {
            int *res=threads_res[i].top();
            for(int i=0;i<WORD_LENGHT;i++)
            {
                stream<<WordDictionary::Get(res[i])<<" ";
            }
            stream<<"\n";
            threads_res[i].pop();
            delete[] res;
        }
        stream.flush();
    }

    std::cout <<"Number of combinations : "<<count<< "\n";

    stream.close();
}

int main(int argc, char** argv)
{
    cxxopts::Options options("satorrotas", "This program searches for Sator Squares in given dictionaries and outputs the resoults.");
    options.add_options()
        ("t,threadnum", "Number Of Threads", cxxopts::value<int>()->default_value("2"))
        ("o,outputfile", "Output file path", cxxopts::value<std::string>()->default_value("out.txt"))
        ("i,inputfile", "Input file path", cxxopts::value<std::string>()->default_value("in.txt"))
        ("l,wordlenght", "Word Lenght", cxxopts::value<int>()->default_value("5"))
        ("s,sorted", "Is the dictcionary sorted", cxxopts::value<bool>()->default_value("false"))
        ("h,help", "Print help")
        ;

    try
    {
        auto result = options.parse(argc, argv);
        if (result.count("help"))
        {
            std::cout << options.help() << std::endl;
            exit(0);
        }

        auto THREAD_NUM =result["t"].as<int>();
        auto OUTPUT_PATH =result["o"].as<std::string>();
        auto INPUT_PATH =result["i"].as<std::string>();
        auto WORD_LENGHT =result["l"].as<int>();
        auto SORTED =result["s"].as<bool>();
        auto start = std::chrono::system_clock::now();

        std::ios_base::sync_with_stdio(false);

        std::vector<string> AllWordsFromFile = std::vector<string>();
        ReadFile(WORD_LENGHT,INPUT_PATH,AllWordsFromFile,SORTED);
        WordDictionary::setWords(AllWordsFromFile);
        WordRange allWord= WordRange(0,AllWordsFromFile.size());
        const WordNode * root=new WordNode(allWord,0,WORD_LENGHT);
        RunParaller(OUTPUT_PATH,WORD_LENGHT,THREAD_NUM,root,WORD_LENGHT);

        auto end = std::chrono::system_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::cout <<"Duration : "<< elapsed.count() << "ms\n";

    }
    catch (const cxxopts::exceptions::exception & ex)
    {
        cout<<"Invalid option : "<<ex.what();
    }
    catch(const sator::exception & ex)
    {
        cout<<"Exception during execution : "<<ex.what();
    }
    catch(const std::exception & ex)
    {
        cout<<"Unhandled exception : "<<ex.what();
    }
    return 0;
}

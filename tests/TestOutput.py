#!/usr/bin/python
import subprocess
import os
import shutil
import unittest
import sys
from parameterized import parameterized

def BuildRelease():
    print("Build project start")
    if(os.path.exists("build") is False):
        os.mkdir("build")
    subprocess.call(["cmake","-DCMAKE_BUILD_TYPE=Release","-S ..","-B ./build"])
    subprocess.call(["cmake","--build","./build"])
    print("Build project finished")

def RunSator(input_dictionary,output,word_lenght,thread_num):
    subprocess.call(["./build/satorrotas",f"-i{input_dictionary}",f"-o{output}",f"-l{word_lenght}",f"-t{thread_num}"],stdout=subprocess.DEVNULL)

def IsPalindrom(matrix):
    size=len(matrix)
    for i in range(0, size): 
        for j in range(0, size): 
            if(matrix[i][j]!=matrix[j][i]):
                return False
    return True

def GenerateTestCases():
    TestCases=[]
    for word_lenght in range(2, 19): 
        for thread_num in range(2, 13): 
            TestCases.append((word_lenght,thread_num))
    return TestCases

#Check : is all of the results really complies with the constraints
class TestOutputValidity(unittest.TestCase):
    expextedResultCount=[0,0,361,15590,1452042,10118682,4628694,94863,80,0,0,0,0,0,0,0,0,0,0]
    def get_path(self,word_lenght,thread_num):
            return f"./results_tmp/result_{word_lenght}_{thread_num}.txt"
    def setUp(self):
        os.mkdir("./results_tmp")  
    def tearDown(self):
        shutil.rmtree("./results_tmp")
    @parameterized.expand(GenerateTestCases())  
    def test_n_lenght_m_thread(self,word_lenght,thread_num):
        path=self.get_path(word_lenght,thread_num)
        RunSator("./dictionaries/latin.txt",path,word_lenght,thread_num)
        wordsMatrix=[]
        allValid=True
        linecount=0
        with open(path, 'r') as file:
            for line in file:
                linecount+=1
                rotasSquare=line.strip()
                wordsMatrix=rotasSquare.split(" ")
                if(IsPalindrom(wordsMatrix) is False):
                    allValid=False
                    break
        
        self.assertTrue(allValid,f'Invalid matrix in the results: word lenght of {word_lenght} and {thread_num} no. of threads Matrix : ({wordsMatrix})') 
        self.assertTrue(linecount==self.expextedResultCount[word_lenght],f' in the results: word lenght of {word_lenght} and {thread_num} no. of threads Results count: ({linecount}!={self.expextedResultCount[word_lenght]})')            

def CleanUp():
    shutil.rmtree("results_tmp")

if __name__ == '__main__':
    BuildRelease()
    unittest.main()
    CleanUp()
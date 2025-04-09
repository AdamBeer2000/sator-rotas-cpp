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
    subprocess.call(["./build/satorrotas",f"-i{input_dictionary}",f"-o{output}",f"-l{word_lenght}",f"-t{thread_num}"])

def IsPalindrom(matrix):
    size=len(matrix)
    for i in range(0, size): 
        for j in range(0, size): 
            if(matrix[i][j]!=matrix[j][i]):
                return False
    return True


def GenerateTestCases():
    TestCases=[]
    for word_lenght in range(2, 18): 
        for thread_num in range(1, 12): 
            TestCases.append((word_lenght,thread_num))
    return TestCases

class TestOutputValidity(unittest.TestCase):
    def get_path(self,word_lenght,thread_num):
        return f"./results_tmp/result_{word_lenght}_{thread_num}.txt"

    @parameterized.expand(GenerateTestCases())  
    def test_n_lenght_m_thread(self,word_lenght,thread_num):
        print(f"Runing test for {word_lenght} word lenght with {thread_num} no. of threads")
        path=self.get_path(word_lenght,thread_num)
        RunSator("./dictionaries/latin.txt",path,word_lenght,thread_num)
        self.assertTrue(TestResult(path))

def CleanUp():
    shutil.rmtree("results_tmp")

if __name__ == '__main__':
    BuildRelease()
    unittest.main()
    CleanUp()
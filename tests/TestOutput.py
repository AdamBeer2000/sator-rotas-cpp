#!/usr/bin/python
import subprocess
import os
import shutil

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

#Check : is all of the results really complies with the constraints
def TestResult(path):
    allValid=True
    print(allValid)
    try:
        with open(path, 'r') as file:
            for line in file:
                rotasSquare=line.strip()
                wordsMatrix=rotasSquare.split(" ")
                if(IsPalindrom(wordsMatrix) is False):
                    allValid=False
                    print("Invalid matrix : ",wordsMatrix)
                    break
    except:
        return False
    return allValid

def CleanUp():
    shutil.rmtree("results_tmp")

BuildRelease()

if(os.path.exists("results_tmp")):
    shutil.rmtree("results_tmp")
os.mkdir("results_tmp")   

for word_lenght in range(2, 18): 
    for thread_num in range(1, 12): 
        print(f"Wrod Lenght: {word_lenght} Number of threads : {thread_num}")
        result=f"./results_tmp/result_{word_lenght}_{thread_num}.txt"
        RunSator("./dictionaries/latin.txt",result,word_lenght,thread_num)
        isValid=TestResult(result)
        if(isValid is False):
            CleanUp()
            return

print("All test passed")

CleanUp()
import subprocess
import glob
import os
import sys

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'


languages = ['*.py','*.java','*.cpp']

#with os.open(test.cases,'r') as testcases, os.open(test.results) as testresults:
#    for l in languages:
#        if glob.glob(l):
#            #run test for l
#            subprocess.run('program',input=testcases.readall())
            

def test_program(program, testcases):
    """

    :param program: name of the program/command
    :param testcases: [(input,expected output),...]
    :return:
    """
    for i,(testcase,expOut) in enumerate(testcases):

        ret = subprocess.run(program, stdout=subprocess.PIPE, shell=True, input=testcase, universal_newlines=True)

        if ret.stdout == expOut:
            print(bcolors.OKGREEN + "Test "+str(i)+" for program \"" +program+"\" successful."+ bcolors.ENDC)
        else:
            print(bcolors.FAIL + "Test "+str(i)+" for program \"" +program+"\" failed." + bcolors.ENDC)
            print(bcolors.BOLD + "Expected Output:\n" + expOut + bcolors.ENDC)
            print(bcolors.FAIL + "Given Output:\n" + ret.stdout + bcolors.ENDC)

def test_folder(folder):
    """
    Searches folder for the following files:
    test.cases
    test.results
    build/main          -- optional
    build/main.class    -- optional
    main.py             -- optional

    if found, reads in testcases and tests each program that was found.
    :param folder: the folder to be tested
    :return:
    """
    if not folder.endswith('/'):
        folder += '/'

    if os.path.exists(folder+'test.cases'):
        with open(folder+'test.cases','r') as f:
            testcases = f.read()

    if os.path.exists(folder+'test.results'):
        with open(folder+'test.results','r') as f:
            testresults = f.read()

    if os.path.exists(folder+'build/main'):
        test_program(folder+'build/main',[(testcases,testresults)])

    if os.path.exists(folder+'build/main.class'):
        test_program('java -cp '+folder+'build '+'main',[(testcases,testresults)])

    if os.path.exists(folder+'main.py'):
        test_program('python '+folder+'main.py',[(testcases,testresults)])


if __name__ == '__main__':

    test_folder(sys.argv[1])


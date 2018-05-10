#!/usr/bin/env python
import subprocess
import glob
import os
import sys
import platform
import difflib
from timeit import default_timer as timer

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'
    
class wcolors:
    HEADER = ''
    OKBLUE = ''
    OKGREEN = ''
    WARNING = ''
    FAIL = ''
    ENDC = ''
    BOLD = ''
    UNDERLINE = ''


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
    if platform.system() == 'Windows':
        colors = wcolors
    else:
        colors = bcolors
    
    for i,(testcase,expOut) in enumerate(testcases):

        t = timer()
        ret = subprocess.run(program, stdout=subprocess.PIPE, shell=True, input=testcase, universal_newlines=True)
        elapsed_time = timer() - t

        if ret.stdout == expOut:
            print(colors.OKGREEN + "Test "+str(i)+" for program \"" +program+"\" successful."+ colors.ENDC)
            print(colors.OKGREEN + "Time: "+str(elapsed_time)+ colors.ENDC)
            print(colors.OKGREEN + "Output:\n"+colors.ENDC)
            for j,line in enumerate(ret.stdout.split('\n')):
                print(colors.OKGREEN +line+colors.ENDC)
                if j >= 20:
                    print(colors.OKGREEN + "..."+colors.ENDC)
                    break
                
        else:
            print(colors.FAIL + "Test "+str(i)+" for program \"" +program+"\" failed." + colors.ENDC)
            print(colors.FAIL + "Time: "+str(elapsed_time)+ colors.ENDC)
            #print(colors.BOLD + "Expected Output:\n" + expOut + colors.ENDC)
            #print(colors.FAIL + "Given Output:\n" + ret.stdout + colors.ENDC)
            diff = difflib.context_diff(expOut.split('\n'),ret.stdout.split('\n'),'Expected','Given')
            sys.stdout.writelines(diff)
            
            diffhtml = difflib.HtmlDiff().make_file(expOut.split('\n'),ret.stdout.split('\n'),'Expected','Given')
            with open('diff.html','w') as f:
                f.writelines(diffhtml)

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


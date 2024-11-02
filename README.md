# cmpsc472Project1

## Description of the project

    This project revolves around the problem of reading words from a file, which can be a time consuming process. The goal is to develop a program to read files from an online repository from the Calgary Corpus. 7 files are loaded and read by 7 child processes, allowing multiple processes to run concurrently, each having 3 threads to read each file, leading to faster reading times. This gives a great review of the concepts covered up to this point in the course, showing an application which can be very beneficial in solidifying those concepts and allowing students greater ease in addressing similar problems further on in the course, as well as after the course has finished. 

## Structure of the code

    The parent process and child processes utilize pipes to realize inter-process communication (IPC). From the parent to the child processes, the size of the file the process will be reading, as well as the file path are sent. This allows the child process to pass on the file path to the three threads it creates to read the file in sections. Threads are created with the POSIX Thread library and are assigned to a method which opens the files, use a pointer to iterate through a section of their assigned file, and create words based on spaces and new line characters. Error handling is addressed during child process creation by checking values of process ids and printing errors accordingly. Unfortunately, I did not complete the implementation, so the performance is not measurable. If it was complete, CPU usage, running time, as well as memory usage could be determined and used as metrics to show the performance of the program and the processes and threads within it. 

## Instructions

    The runnable code is located in this [Google Colab](https://colab.research.google.com/drive/1utlztQpHfDd3SAvBL0nwctHf-8d1yeo4?usp=sharing). To run, click the play button in the top left corner of the two code snippets below the header "Reading the files in child processes with multithreading"

## Performance evaluation

    I did experience some challenges during the implementation of this project, especially evident by my inability to finish it. I experienced the greatest difficulties with getting the words to be counted correctly. I was getting the same word count from each thread of a file, so for 7 different files, I would have 3 identical values 7 times, and was not sure how to prevent that. I was given the advice to open the files in each thread, but my current implementation contains that change, as before I was passing pointers at different locations to threads after opening the file in a child process, and I was unable to see a difference in the outcome. I also had issues setting up the pipes to initiate IPC, and I feel this could be blamed on not fully understanding how pipes are used in C, or my inability to realize what I was doing wrong for majority of the time I was spending. I also was unsure of how to store the Calgary Corpus files, as I was using Google Colab, and stored them in my Google Drive to access them more easily whenever I opened Colab to work on the project. After some testing, I realized that no one else would be able to access the files, so I may've picked the wrong place to store them. I do feel that the project has improved my understanding of these concepts, though I would be much more satisfied if I had completed the project. 

## Discussion

    Multiprocessing does allow for faster running speed, but critical sections have to be guarded by mutex locks to prevent memory addresses from being accessed concurrently. Multithreading has similar benefits, and it can lead to issues with too many resources being used concurrently. This can be limited by the number threads being created, or limiting the number of threads that can run concurrently. 

# CS203 (2021 Fall) Project: Prefetching competition

## Due: 11/29/2021

## Introduction
In this project you will be working to implement a hardware prefectcher. You will be given a basic cache simulator with an interface to a prefetcher. Your task will be to implement the prefetcher interface with a prefetching algorithm of your own choice. The effectiveness of your prefetcher will be tested against a baseline prefetcher. You will also compete against your fellow classmates for amazing awards and prizes! Notice: The project should be done individually.

## Cache Configuration:
Your prefetcher will work in the context of a well-defined memory hierarchy. The memory system is already implemented (in C++), and can be downloaded here: proj1-source.tar.gz. The Data Cache has the following stats:

- 32KB Size
- 2-way Set Associative
- 16 byte line size
- write-through
- no-write-allocate
- 1 cycle hit time
- 10 entry write-buffer
- A L2 cache (data only) has the following stats:
- 256KB Size
- 8-way set associative
- 32 byte line size
- write-back
- write-allocate
- 20 cycle access time (fully pipelined)

Because it is fully pipelined, it is possible to issue 1 request (either from the data cache or the prefetcher) to the L2 cache per cycle.
Main memory has an access time of 50 cycles and is not pipelined (i.e. only one request can be handled at a time). Accesses to main memory are held in a FIFO queue with 10 entries. If the FIFO fills up, the L2 will no longer accept requests.
## Prefetcher Interface:
Your main task in this project will be to implement a prefetcher using the given prefetching interface. The system controller provides information about all loads and stores that are issued by the CPU. The information that is provided includes the effective memory address, PC of the memory instruction, and whether the instruction was a load or a store. You may use this information in any way that you see fit. During all cycles where the CPU is not issuing a request to the L2 cache, the system controller will query the prefetcher for any memory requests that it may have. While your prefetcher may have many requests queued internally, the system will service a maximum of 1 per cycle. After the prefetching request has been satisfied (either from the L2 or main memory), it will be placed in the Data Cache.

The file prefetcher.h pre-defines four functions that must be implemented:

- bool hasRequest(u_int32_t cycle) - Value returned indicates whether there is a request waiting from the prefetcher. This function is used as a gate before getRequest() is called.
- Request getRequest(u_int32_t cycle) - Returns a request to be sent to the L2 cache. Only the addr field of the Request struct will be used.
- void CompleteRequest(u_int32_t cycle) - This function is called as soon as the last request is successfully sent to the L2 cache.
- void cpuRequest(Request req) - This function is called after a CPU request is handled. The request gives the addr, pc, cycle it was issued, and whether it was a hit or miss in the D cache.

The prefetcher is called only from the main.C file.
While you are free to examine all parts of the provided memory system, the only modifications you should make is to the prefetching interface contained in the files prefetcher.h and prefetcher.C. The only source code you will be submitting are these two files.

To aid in your understanding of the prefetcher interface, we have provided a sample prefetcher implementation. This simple prefetcher waits for misses on the D-cache and then tries to prefetch the next block in memory. You can find the sample prefetcher in the following location of the repo:  https://github.com/hungweitseng/CS203-fa21-prefetcher/tree/main/sample-pf.

## Constraints on Prefetcher:
In addition to the constraint that only a single request can be serviced per cycle, you will have one further constraint: the amount of state saved in the prefetcher. The amount of state saved in the prefetcher may not exceed 4KB. Your source code must clearly indicate which variables are used as state. Furthermore, you will need to provide a detailed accounting in your project report of how much state is kept.

## Cache Simulation
The memory hierarchy will be simulated using trace files generated by the Pin binary instrumentation tool. Each line in the trace file refers to a memory access and includes the following four pieces on information:

## Whether the instruction is a load or store
- PC of memory instruction (32 bits)
- Effective Memory Address (32 bits)
- Number of non-memory ops since the last memory operation
## Simulation Statistics
The memory system provided will output several statistics about the performance of the system. They will help you understand how your prefetcher is performing and why. The stats include:

- Total Run Time
- D-Cache Total Hit Rate
- L2 Total Hit Rate
- Average Memory Access Time
- Average Memory Queue Length
- D-Cache-to-L2 bandwidth utilization
- Memory bandwidth utilization

These stats will be placed in the file mem.trace.out, where mem.trace was the input file used.

## Trace File
Average Memory Access Time will be used for comparisons of your prefetcher to the baseline and your colleagues' prefetchers. For your report, you should test your prefetcher on traces available here: https://github.com/hungweitseng/CS203-fa21-prefetcher/tree/main/traces
. However, TA will test your prefetcher with another set of memory traces for the prefetching competition. Please consider making your design working for general cases. In addition, if TA cannot reproduce the experimental result in your report, your project will be considered as fail.

You may wish to extend the simulator to collect more stats. This is not required, and your prefetcher should not depend on these modifications.

## Collaboration
You should feel free to discuss the project with others in the class including sharing detailed performance results of your predictor. Sharing code is expressly forbidden.

## Prefetcher starting points
Here are some papers to get you thinking about different approaches to prefetching. You are not required to choose an algorithm from these papers, but they can provide some useful starting thoughts. Their bibliographies will provide pointer to other papers on the topic.

- Spectral prefetcher: An effective mechanism for L2 cache prefetching http://prod.tinker.cc.gatech.edu/journal/spectral.pdf
- A stateless, content-directed data prefetching mechanism https://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.442.3212&rep=rep1&type=pdf
- Prefetching using Markov predictors https://ieeexplore.ieee.org/document/752653/
- Memory Prefetching Using Adaptive Stream Detection https://www.cs.utexas.edu/~lin/papers/micro06.pdf
- Reducing memory latency via non-blocking and prefetching caches https://dl.acm.org/doi/10.1145/143371.143486

## Evaluation
Your grade for the project will be based on your write up the prefetcher you implemented. The performance of your prefetcher is less important than your discussion of how the prefetcher works and why it performs the way it does.

## Compilation and Execution Environment:
Your simulator should be written in either C or C++. It should compile and run on a Red Hat Enterprise Linux machine using gcc (if written in C) or g++ (for C++). CSE grad students have access to this type of environment by using sledge.cs.ucr.edu. For those who cannot access these computers (likely CSE undergrads and ECE students), you can request access to CSE Systems.

For those of you unfamiliar with developing in the linux environment, you can check out this basic tutorial (https://www.classes.cs.uchicago.edu/archive/2017/winter/51081-1/LabFAQ/lab2/compile.html) on compiling using gcc (or g++). For those of you that are rusty with your C++, I would recommend this C++ reference site https://en.cppreference.com/w/. Of course, the webboard is also a good place for more specific questions.

## Fabulous PRIZES!!!
The authors of the three top prefetcher (as measured by total run time) will receiver prizes. The prizes will be awarded in class on 12/1/2021.

## Deliverable

### Project Report
Your report for project will consist of the following sections:

- Description of Prefetcher - One or two paragraphs describing the prefetching algorithm that you are using. If your prefetcher is based on an existing design, you must explicitly state the original source. While you are free to implement existing designs, failure to provide a citation will result in you receiving no credit for the project. Your description should include the rationale for the design, supported, where appropriate data evaluating "teaks" or changes you made to improve performance.
- State Accounting - How much state your prefetcher uses as well as a detailed description of how and where the state is used. For example, if you have a prediction table, you should list its size as well as its layout.
- AMAT Graph - A bar chart showing the average memory access time (AMAT) of your prefetcher on the provided traces.
Your report should be in PDF format and have the following name:lastname_firstname_cs203_fa21_project.pdf
- Source Code
You only need to submit two source code files: prefetcher.h and prefetcher.C. Your prefetcher should be able to compile with the unmodified memory system that has been provided. The given system is written in C++ so your code should compile with the g++ command on the APE lab computers. This file should contain your name as well as your Student ID at the top.

### Electronic Submission
Please submit the report and source code file as a tarball via eLearn. Your tarball should have the following name: lastname_firstname_cs203_fa21_project.tar.gz

Any submission without following the above constraints will not be graded.

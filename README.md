# chronOS

A scheduling simulator.

* **Authors:**
  * 39489 &mdash; Jorge Miguel Louro Pissarra, UBI
  * 41266 &mdash; Diogo Castanheira Simões, UBI
  * 41381 &mdash; Igor Cordeiro Bordalo Nunes, UBI
  
* **Advisor:**
  * Paul Andrew Crocker, PhD, UBI
* **License:** GNU-GPL 3.0
* **Latest version:** 1.3.0
* **Last update:** June 19th, 2020
* **Languages:**
  * English (en-us) &mdash; for code, identifiers and general output;
  * Portuguese (pt-pt) &mdash; for some comments.


## What is _chronOS_?

**chronOS** is an operating system scheduling simulator. It is built around two main components:

* A process simulator;
* A memory manager.

It is able to use different algorithms &mdash; namely ***FCFS***, ***SJF***, ***PSA*** and ***round-robin*** &mdash; to schedule processes which are as well simulated. The processes consist of changing an unique integer variable.

The **static memory manager** uses a ***first-fit* algorithm** to accommodate new instructions of programs.

The **dynamic memory manager** uses 4 algorithms &mdash; *first-fit*, *next-fit*, *best-fit* and *worst-fit* &mdash; to test them and obtain certain comparative statistics about them.


## How to compile

There are two modes to build:

* **debug** &mdash; outputs very extensive debugging information about the execution of chronOS:
  ```
  make debug
  ```

* **release** &mdash; produces a final version of chronOS with only the absolute essential output:
  ```
  make release
  ```

It is possible to clean the current directories using `make clean`.


## Usage

How to call the program:
```
chronos
    [<--fcfs | --sjf | <--rr | --robin | --round-robin> | --psa>]
    [<<--no-heap-request | -n> | <--seed | -s> n>]
    [<--control | -c> <auto | stdin | file>]
```

Options available:
```
Flag                  Description
--------------------------------------------------------------------------------
--fcfs                Uses FCFS scheduling algorithm (mode by default).
--sjf                 Uses SJF scheduling algorithm.
--psa                 Uses PSA scheduling algorithm.
--rr
--robin
--round-robin         Uses round-robin scheduling algorithm.
--------------------------------------------------------------------------------
--no-heap-request
-n                    Turns off pseudorandom heap memory requests.
--seed n
-s n                  Uses the seed 'n' to generate the pseudorandom requests.
                      Time is used by default if seed is not given.
--------------------------------------------------------------------------------
--control x
-c x                  Changes the control to mode defined by X, being:
      auto            Automatic (mode by default);
      stdin           Manual (via stdin);
      file            By file (via control.txt text file).
--------------------------------------------------------------------------------
```

A file `plan.txt` with the list of programs, times to execute and optionally priorities is expected. Without it the program will not execute.


# DISCLAIMER

This project is an university project. The authors and advisers are NOT responsible for anything resulting from the use of this software. **USE IT AT YOUR OWN RISK!**

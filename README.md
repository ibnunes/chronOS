# chronOS

A scheduling simulator.

* **Authors:**
  * 39489 &mdash; Jorge Miguel Louro Pissarra, UBI
  * 41266 &mdash; Diogo Castanheira Simões, UBI
  * 41381 &mdash; Igor Cordeiro Bordalo Nunes, UBI
  
* **Advisor:**
  * Paul Andrew Crocker, PhD, UBI
* **License:** GNU-GPL 3.0
* **Latest version:** N/A
* **Last update:** May 9th, 2020
* **Languages:**
  * English (en-us) &mdash; for code, identifiers and general output;
  * Portuguese (pt-pt) &mdash; for some comments.


## What is _chronOS_?

**chronOS** is an operating system scheduling simulator. It is built around two main components:

* A process simulator;
* A memory manager.

It is able to use different algorithms, like ***FCFS***, to schedule processes which are as well simulated. The processes consist of changing an unique integer variable.

The **memory manager** uses a ***first-fit* algorithm** to accommodate new instructions of programs.


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

A file `plan.txt` with the list of programs and times to execute is expected. Without it the program will not execute.

_TO-DO_


# DISCLAIMER

This project is an university project. The authors and advisers are NOT responsible for anything resulting from the use of this software. **USE IT AT YOUR OWN RISK!**

# Project 1: Database Management System
### CSCE 315 with Dr. Yoonsuck Choe
### Team 11

***
** Input files are included in both Parser/ and Application/**

** Output files are included in the root folder, Parser/, and Application/input-output.txt(this has both input/output) **
***

**To compile: make all**

**To run Parser's stand-alone execution: ./run-parser**

**To run Application: ./run-app**

***

### Core Database Engine Reference

### Class: DBMS

* **open( relation_name ) -> result**

Opens a database file with name "_relation_name_.db". Returns boolean _result_ with value TRUE if successfully opened or FALSE if an error occured.

* **close( relation_name ) -> result**

Closes a database relation with name _relation_name_. Returns boolean _result_ with value TRUE if successfully closed or FALSE if an error occured.

* **save( relation_name ) -> result**

Outputs plain ASCII text in DML format(described in the project handout) to a file "_relation_name_.db". **Note:** Saving will overwrite any previous data in "_relation_name_.db".

* **exit()**

Exits the DML interpreter.

* **show()**

* **create()**

* **update()**

* **insert()**

* **delete()**

***

### Class: Relation

**Public**

**Private**

**Methods**

***

**Work Log**

* *January 26th*
  * Building a plan to break down project components into smaller pieces to be handled in groups of two.
    * Ryan Walters, Jonathan Grimes, Nathan Blattman
   * Understanding what needs to be done.
   * Jonathan and Nathan start Design Document.

* *January 27th*
   * Jonathan and Nathan finished Design Document.

* *January 28th*
   * Work has started with some progress, with the following assignments
     * Jonathan: Selection, Projection, Renaming, Update-cmd
     * Nathan: Set Union, Set difference, Cross Product
     * Victor: (conjunction, comparison, operators, etc.), close-cmd, save-cmd, exit-cmd, 
     * Ryan: Show-cmd, Create-cmd, Insert-cmd, Delete-cmd, Foundational code(Cell, Attribute, Attribute List, Tuple, Relation Classes), putting the pieces together
   * Defining what makes a Relation and Database

* *January 29th*
   * Redefined what makes a Relation and Database, including how it is to be made
   * Work is begining to pick up

* *January 30th*
   * Jonathan has uploaded a gitignore
   * Nathan created Database.h and Jonathan helped modify the shell.


* *January 31st*
   * Meet up to begin comparing and exchanging information of how the project is supposed to come together
   * Ryan has modified gitignore, and created the core classes from Database.h.
   * Jonathan has created and uploaded [a non-compiling] Selected, Renaming, and Project.
   * Nathan has created and modified the Relation classes, and set_union and set_difference.
   * Victor has created an outline of the comparison class.

* *Mon, 1 Feb 2016*
   * Nathan modified logic in set_union and set_difference.
   * Jonathan added helper functions to Relation.cpp and modified Selected, Renaming, and Project.
   * Ryan modifications to class files.

* *Tues, 2 Feb 2016*
   * Jonathan added UPDATE command, added more functionality to Select, Rename, and Project, and added a comparison function for selection.
   * Nathan overloaded “==” operator, and slight modifications to union functions.
   * Ryan working on his commands (DELETE, SHOW, CREATE, INSERT), and did modifications to core classes. 

* *Wed, 3 Feb 2016*
   * Nathan modified Relation class, added cross_product, and fixed bugs in union functions, and attempting fix to compiling error.
   * Jonathan updated and modified to Select, Renaming, and Project functions, and merged functions into DBCore. Assisted in attempting to fix compiling error.
   * Ryan trying to merge everyone’s code together, modified his commands, and attempting to fix compiling error.
   * Victor added outline of Save function, and added Save and Exit to Database.

* *Thu, 4 Feb 2016*
   * Nathan trying to fix compiling errors.
   * Jonathan attempting in fixing compiling errors.
   * Ryan trying to fix compiling errors with DB Core code.
   * Victor’s compare code has been dismissed in favor of Jonathan’s existing compare function.

* *Fri, 5 Feb 2016*
   * Ryan trying to fix compiling errors with DB Core code.
   * Nathan began Parser.h (to be used in integration) added to parser_stuff branch
   * Jonathan began to write test_parser.cpp (to be used in testing of parser) – no commits to avoid compiling errors

* *Sat, 6 Feb 2016*
   * Ryan trying to fix compiling errors with DB Core code.
   * Nathan modifications to Paser.h
   * Jonathan added test_parser with modifications to paser_stuff branch

* *Sun, 7 Feb 2016*
   * Ryan trying to fix compiling errors with DB Core code.
   * Nathan modifications to Paser.h
   * Jonathan added more stability and functionality to test_parser and added Commands to the functionality

* *Mon, 8 Feb 2016*
   * Ryan trying to fix compiling errors with DB Core code - with mild success
   * Nathan modifications to Paser.h
   * Jonathan finished test_parser to a much more stable version

* *Tue, 9 Feb 2016*
   * Ryan fixed compiling errors with DB core code
   * Jonathan made hotfixes to test_parser
   * Nathan modifications to Paser.h

* *Thu, 11 Feb 2016*
   * Ryan began looking into the application
   * Jonathan fixed a merging conflict
   * Nathan modified some of the Parser header information

* *Fri, 12 Feb 2016*
   * Ryan and Victor started application
   * Nathan began integrating the parser into the core code
   * Jonathan began to assist in parser integration

* *Sat, 13 Feb 2016*
   * Ryan and Victor working on application ideas
   * Nathan Working on the integration of parser with core code
   * Jonathan working on integration; added select and project functions.

* *Sun, 14 Feb 2016*
   * Jonathan has finished the test_parser.cpp (to be used to test correctness of command)
   * Nathan continued to work on the integration of parser.

* *Mon, 15 Feb 2016*
   * Nathan and Jonathan worked on the integrated parser.
   * Ryan worked on bringing back Core Code files that previously worked. Remerged them into the repo. Holding work on application in order to help out with parser + core code integration.
   * Ryan, Nathan and Jonathan working to fix errors on parser + core code integration

* *Tues, 16 Feb 2016*
   * Ryan, Nathan and Jonathan continue to fix error on parser + core code integration
   * Nathan fixed errors in Renaming and other functions
   * Jonathan fixed errors in Cross product and other functions
   * Ryan begins to work on Lexer for integrated parser

* *Wed, 17 Feb 2016*
   * Ryan implemented close and Save in the parser
   * Nathan and Jonathan continue to fix errors in integrated Parser

* *Thu, 18 Feb 2016*
   * Ryan, Nathan, and Jonathan began to use Ryan's Lexer-ed parser
   * Ryan started working on Application
   * Jonathan fixed Segfaults in integrated Parser and corrected error with intake in old parser (for reference).
   * Nathan began copying functionality over to new integrated Parser.
   * Victor added Application file.

* *Fri, 19 Feb 2016*
   * Ryan, Nathan, and Jonathan continued to work on the integrated parser.
   * Nathan continued to work on the new intergrated Parser.
   * Ryan continued working on the Application.

* *Sat, 20 Feb 2016*
   * Jonathan fixed Segfaults with new parser, defined project, and renaming, and put in added input for text docs
   * Nathan fixed Insert, select, and show (also fixed several Segfaults).
   * Ryan continued to work on Application.

* *Sun, 21 Feb 2016*
   * Jonathan fixed Segfaults with (BOTH inputs files that were being used, Oops), modified formating, and inhanced the intake for the running parser.
   * Nathan fixed functionality to the running parser
   * Ryan continued to work on the Application.

* *Mon, 22 Feb 2016*
   * Ryan added more functionality to the Application, like switches for different functionalities.
   * Nathan added more functionality to select, set_difference, and general functionality.
   * Jonathan Added max_lengths functionality to tables, fixed primary keys in rename and project, defined OPEN and CLOSE, and added a hand_input for run_parser, general formating fixes, and re-did original parser as a boolean test for validility check.
   * Nathan and Jonathan finished the integrated parser.

* *Tue, 23 Feb 2016*
   * Ryan continued to work deligiently on the Application
   * Jonathan fixed the boolean test, improved output, small typos, and folder\file reconstructions.
   * Victor did some to-do's Ryan has set out to do.
   * Nathan Tested different inputs, and worked on starting to comment.

* *Wed, 23 Feb 2016*
   * Ryan finished working on the Application
   * Jonathan worked on making sure inputs, work log, etc was put in place
   * Nathan worked on making sure comments, etc was properly in place.
   * Ryan and Jonathan worked on the Post Production Notes

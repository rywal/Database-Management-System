# Project 1: Database Management System
### CSCE 315 with Dr. Yoonsuck Choe

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

* *January 31st*
   * Meet up to begin comparing and exchanging information of how the project is supposed to come together

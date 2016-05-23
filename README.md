# Project 1: Database Management System
### CSCE 315 with Dr. Yoonsuck Choe

## Description

Created a Database Management System (DBMS) consisting of two parts: a Recursive Descent Parser to convert quieries to commands, and an application that runs on top of the database implementation to provide a realistic example of a possible use case for the DBMS.

### Part 1: Database Management System

The scope of our system was slimmed down to fit the time constraints of our course. Our course handout provided a grammar described in Baccus-Naur Form. We used this grammar to implement a recursive descent parser to handle queries of a similar structure to SQL. Relations in the database were output to plain ASCII text files as the queries needed to reconstruct them. These could be modified and imported again as necessary.

### Part 2: DBMS Application

Part 2 constisted of building an application that took advantage of the DBMS created in part 1. In our example, we created a convention exhibit management system. This system managed exhibitors, booths, services, attendees and inventory. The exhibit management system took advantage of the DBMS to:

1. register new exhibitor, list exhibitors, remove exhibitor, list exhibitors based on certain search criteria.
1. assign, delete, and list booth location(s) for a given exhibitor.
1. assign, delete, and list booth services to exhibitor. Must check inventory and assign certain item to the booth held by the exhibitor.
1. show invoice for exhibitor (booth, service, and the cost for each subitem, and total cost).
1. show total revenue (add up all the fees).
1. add, delete, list attendees who visited a certain exhibitor.
1. register new attendee, delete attendee, list attendees, search attendee based on a certain criteria.
1. add, delete, list inventory.

Different interfaces were shown for exhibit managers, exhibitors and attendees. These interfaces were limited according to user's role and privileges.

***

### Compile and Run

* To compile: `make all`

* To run:
  * Parser executable: `./run-parser`
  * Application executable: `./run-app`

***

_Created as part of CSCE 315 at Texas A&M University with Dr. Yoonsuck Choe_

Contributors:
* Ryan Walters
* Nathan Blattman
* Jonathan Grimes
* Victor Vasquez

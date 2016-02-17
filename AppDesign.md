# Application Design
### Documentation for a Convention Exhibit Application explained by CSCE 315 Project 1

***

### Tables
* **Exhibitors**
  * Exhibiting company _or_ Organization Name
  * Address
  * Contact Person
  * Email
  * Phone
  * Fax
  * Category(Commercial, non-profit, government)
  * Booth Personnel(name and email)
  * Company Description
  * Company website

* **Booths**
  * Columns 1-20
  * Rows 1-50

* **Services**
  * Electricity(500W, 1000W, 1500W)
  * Furniture(table, chair, sofa, how many of each)
  * Electronics(flat-screen TV, computer monitor, laptop, projector, projector screen, how many of each)
  * Bar-code scanner
  * Adertisement(Exhibitor guide, online exhibitor guide, large banner, small banner, one or more)
  * Insurance($1 million coverage or $10 million coverage)
  * Each item should have a fixed price associated with them

* **Attendees**
  * Attendee name
  * Organization
  * Address
  * Email
  * Registration fee
  * Category
    * Regular
    * Discounted
    * Exhibitor booth personnel(free)
  * Exhibits visited
    * List of exhibits visited
  * Badge Status
    * Mailed
    * On-site
    * Picked up
    * Not picked up
* **Inventory**
  * Electronics
    * TV1
    * TV2
    * ...
    * Laptop1
    * Laptop2
    * ...
  * Furniture

***

## Functions
### Exhibits
* Register new exhibitor
* List Exhibitors
* Remove Exhibitors
* List exhibitors based on criteria

### Booths
* Assign booth location to exhibitor
* Delete booth location of exhibitor
* List booth location(s) of exhibitor

### Services (These **must** check inventory and update count before assigning)
* Assign services to exhibitor
* Delete services of exhibitor
* List service(s) of exhibitor

### Finance
* **Invoices**
  * Show invoice for exhibitor
    * Must include: booth, services, cost for each subitem, total cost
* **Revenue**
  * Add up all fees and show total revenue

### Attendees
* Add attendee who visited exhibitor to list
* Delete attendee who visited exhibitor from list(Not sure why?)
* Show attendees who visited exhibitor
* Register new attendee
* Delete attendee
* List attendees
* Search attendee based on criteria

### Inventory
* Add to inventory(increment total count for item)
* Delete from inventory(decrement total count for item)
* List inventory

***

### User access levels
* **Exhibit manager** - Has access to _all_ data
* **Exhibitor** - Has access to _own_ exhibit and list of attendees who visited them
* **Attendees** - Has access to _own_ personal info and list of exhibitor names they visited

***

### Implementation
* **Main Menu**
  * The main menu should start by asking which user access level should be used
    * Save this user access level until it is changed(via a text command)
  * Main menu should output available functions based on _User Access Level_
* **Database**
  * A single instance of a database will be instantiated with name "rbdms"
  * All functions will perform database operations by calling "rdbms" and then the needed function name
    * For example: To insert a tuple you should use 
        rdbs.get_relation("relation_name").insert_tuple(values);
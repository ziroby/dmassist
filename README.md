DM Assist
=========

DM Assist helps you run pen and paper d20 games.  It aims to be quick
and light, so you can spend most of your time working with the
players, not the computer. It uses minimal information, to make it
fast to setup.  It provides a command line interface, because command
lines allow for a great deal of power and accessible easily and
quickly.  But it also has standard windowing access, so you get
started using it very quickly.


Features:

 * Combat/initiative tracker

 * Tracks hitpoints, subdual damage, and initiative rolls for
   characters.

 * Tracks limited duration effects (such as spells), removing them
   when they expire.

 * Integrated dice roller – most places which accept a number accept a
   dice equation as well.

 * Complex dice equations – multiple dice rolls summed together, like
   2 + 3d12 + 2d6 + 1d4 + 12

 * Combined windowing and command-line interface.

 * Save and load groups of characters.

DM Assist is free software, released under GPLv3.

Development
--------

I originally wrote DM Assist in Java using a Swing interface, with
model-view separation.  The engine and swing portions were 
designed with Test First Development using
JUnit tests. 

I added the Android portion later. It was on the app store for a while and got over 
20,000 downloads. I have not updated the Android code to the latest version, so it
is no longer in the store.

I am now (July 2020) adding a Spring Boot server and will then add a JavaScript React 
front end.

Design
------

![[DM Assist design diagram]](./Components.png "DM Assist design diagram")

The Engine is a pure Java app, with full unit tests. 

The Server is a Spring Boot RESTful
microservice that exposes the actions from the engine.

The Repository is a thin Java layer to access the database. 

I will decide the tech for the Database later. Changing database vendors should 
involve no change to the Repository.

Building
--------

The build uses maven. To build everything:

```shell script
    ./mvnw install
```
    
To deploy the Server, (coming soon) use:

```shell script
    ./mvnw deploy
```

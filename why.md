# Why?

## The problem

Let's say you have a data struct and each time you change this data struct you have to edit many places F1 .. FN. 

![the_problem.gif](/the_problem.gif)

## Fix 1

To solve this problem we can create a function

![the_problem.gif](/solution1.gif)

Using this solution when we change the data struct we have two places to edit. The declaration itself and the function.

## Using CPrime

Using CPrime you can reduce the editing to the declaration.

![thesolution.gif](/thesolution.gif)

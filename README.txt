--Program Information--
  Name: Cody Gonsowski & Ethan Seiber
  Date: 1/23/2020
  Assignment: Assignment #1
  Program Title: The Unix Shell
  Files required: shell.c, Queue.h/c, GlobalVars.txt

--Design Overview--
  Took advantage of queues in order to execute commands concurrently.

  Kept queue implementations in separate files to increase readability.

  Created a GlobalVars.txt file to store global instructions such as
  preprocessing statements and varaibles to be used by other files. This was
  mostly to have these instructions to play nice with the makefile.

--Known Bugs/Problems--
  The only known bug is if you have a command typo in your batch file this
  will initially cause the commands after to be executed twice. Any more typos
  than this will crash the program.

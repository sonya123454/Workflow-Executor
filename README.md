Test Task. Implement Workflow Executor
Workflow provides an infrastructure for the set-up, performance and monitoring of a defined sequence of tasks, arranged as a workflow application


Please develop a program on C++/C# which reads a text file of the format below:
desc Name of the workflow
id1 = Task1
id2 = Task2
id3 = Task3
…
idN = TaskN
end
idA->idB->idC->idD->idE
idB->idD
idA->idD

The code should be covered by unit tests( stored in a separate project in the solution), well organized, OOD/OOP patterns used, no 3rd party libraries except STL, C++11 (like std::thread and so on). The solution should be developed in Visual Studio 2017 and it should be compliable with the settings by default.
List of the supported commands is:
1.	readfile filename 
The command read a text file. the command input is null, output is a text from the file
2.	writefile filename
The command writes/appends text into a file. the command input is a text, output is null. 
3.	grep word
Find all string lines (CR separated) which contains the word.
Input – text, Output – text
4.	sort 
       The command does alpha-numeric desc sorting of the string lines (CR separated) 
Input – text, Output – text
5.	replace word1 word2
the command replaces word1 with word2 in all input text
Input – text, Output – text
6.	synch 
The command synchronizes an execution of all sequences in different threads (until they are finished or stop on the command for waiting others) before moving to the next command in the sequence
Input – null, Output – null
Where
 id1..idN are unique positive numbers 
Task1..TaskN are commands with mandatory parameters from the list of the supported commands 
idA, idB, idC … idZ are positive numbers from a set of id1...idN
	is a link between tasks defines an execution sequence of the commands. Each line of the execution sequence run in parallel (in the separate thread)
Command line to execute:
executor.exe workflow.txt
Examples:
File: workflow1.txt
desc example 1
1 = replace fantasy good
2 = writefile example1.out
4 = readfile example1.in
5. sort 
6. grep wizard
7 = synch
end
4->5->1->7->2
4->5->6->2

File: workflow2.txt
desc example 2
1 = replace super good
2 = writefile example2.out
4 = readfile example2.0.in
5 = readfile example2.1.in
6. sort 
7. grep weather
8 = synch
9 = readfile example2.2.in
End
4->1->5->8->8->2
5->7->6->2->8
9->6->8->2

Про sleep – windows – linux
Не поняла про синхронизация = она же вроде один раз должна включаться?

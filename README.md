<<<<<<< HEAD
# CS 104: Class Projects

palindrome.cpp
	g++ -g -Wall parsemd.cpp -o parsemd
	./parsemd out.txt abc 4

	DESCRIPTION: Read in a string of characters and an integer size and generate all possible palindromes of the given size or less using the characters provided as your options.  Each palindrome is outputed to the given file.


parsemd.cpp
	g++ -g -Wall parsemd.cpp -o parsemd
	./parsemd input.txt output.txt

	DESCRIPTION: Read in the name of a Markdown text file, and outputs into a file, one per line, each word in the file in the order they appear.  Output shouldn't have any special characters, numbers, white space, etc.  For each link encountered, output "LINK (destination, anchor text)", where destination is where the link points, and anchor text is the displayed text.  
	Assumptions: 
	- each link [ or ( is preceded by white space, tab, newline etc
	- text inside [] or () will not containt [, ], (, or )
	- text or link location (or both) may be empty, for which the output should be an emtpy string
	- there may be text following ) and should be outputed as a new word


sequencesearch.cpp
	g++ -g -Wall sequencesearch.cpp -o sequencesearch
	./sequencesearch input.txt output.txt

	DESCRIPTION: Given a "grid" of floating point numbers, look for the longest strictly increasing sequence along a row or column (not diagonal), forward or backward, and output the longest length
=======
# CS 104 Class projects

- **Hw1**: sequence search, palindrome, parser
- **Hw2**: split a list using a linked list class
- **Hw3**: boolean expression calculator using a stack class, which uses an integer list class
>>>>>>> ca4300d95e69575750e33fb973b71459aead9b28

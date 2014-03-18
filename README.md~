FileTransferProtocol
====================

Application layer transfer protocol with support for file upload/download and   indexed searching, using both TCP and UDP protocols

How to Use:

1)Copy the code onto two different machines or two different folders on the same machine

2)Start two different sessions, compile the code ( gcc Protocol.c -o client), and run it (./client)

3) The program asks you to enter the port on which it will listen, enter a value (eg: 5000)

4) Choose the mode (O for TCP and 1 for UDP)

5) Enter the server address to which you want to connect ( Eg: 6000)

Note: Now the program tries to connect with the server listening on this port and will wait till it establishes a connection

6) Once connection is established, the program will work.

Commands - 
	
	A) Commands to check integrity of data: 
	
		1) FileHash CheckAll - Hashes all the files on the server (the OTHER folder/machine) and returns there md5 values
	
		2) FileHash Verify <filename> - Hashes the corresponding file in server and prints its md5 when compared to the local copy
	
	B) Commands to get index/list of files on server
		
		1) IndexGet ShortList <filename> - Gives info about requested file
		
		2) IndexGet LongList - Gives List of all the files on the server
		
		3) IndexGet Regex <regular epxr> - Gives info of all the files on the server matching the regex (EG: "IndexGet Regex *.c"  lists all C files present on the server)

	C) Commands to transfer file data
		
		1) Upload <filename> - Command uploads a local file to the server. It asks permission from the other user before uploading.
		
			Eg: User1 : Upload a.txt
		
			    User2 sees " 
			    		 Someone wants to Upload File a.txt
			    		 Type "Allow" to let them, "Stop" to prevent them.
					"
		
			    If User2 types "Allow" Transfer happens, else its stopped
		
		2) Download <filename> - File is downloaded
	
	D) Others
	
		1) q or Q - if written on a single line, all by itself, asks the local program to shut down. The server continues to run
	
		2) Any other data is interpreted as text and send as a chat msg. The server prints it out as such


Use this code as you wish. Suggest changes/ edits to make this better.

Cheers !

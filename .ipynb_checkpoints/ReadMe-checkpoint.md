Multithreaded File Server with Client socket programing in C

Author: Arun Baraili
Date: 05/4/2026

Project Description:
This project implements a multithreaded file server and client system using TCP sockets in C.
This server is able to handle multiple clients simultaneously using POSIX threads. 

In the client side the user is abel to, 
Upload, Download, List, Delete files from the server and also end it with the option. 
And, the server listen for client connections and processes it concurrently. 

The files that are included are: 
server.c -- server
client.c -- client 
csapp.h. -- CS:APP libaray, used from other projects
Makefile -- complie the server + client
ReadMe.txt 

Required software: 
GCC complier
JyputerHub or VS that with C language downloaded
POSIX Threads Libarary (pthread)

Run the program: 
once the client and server are complied using Makefile, 
In one port run: 
./server 3240
and another port: 
./client localhost 3240

One the server gets the client connection the user are prompted with these options: 
(1) Upload File
(2) Download File
(3) List Files
(4) Delete File
(5) Quit

Upload function: 
sends file from client to server and server saves it in the current working directory

Download: 
Gets the file from server from the server and saves it locally in client

List: 
Displays all the files in the server directory

Delete: 
Removes a file from the server

Multiple clients: 
The server is able to handle multiple clients using pthread
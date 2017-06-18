# -Linux-C-sample-socket
C Socket Programming for Linux with a Server and Client Example Code

1.Use setsockopt() to solve timeout problem.

2.Use signal() and waitpid() to solve zombie process beacuse of using fork().

# Server:
Calculates the number to the power of two by the client sent

# Client:
Send a number to server and receive a result from server

# Command line
First step

~$ make clean ; make 

Second step

~$ ./serversocket

From other terminal

~$ ./clientsocket `'num'`

# NOTE:
The `'num'` have to decimal.

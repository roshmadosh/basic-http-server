Referenced [A HTTP Server Web Server Framework Written in C (Just For Fun)](https://github.com/infraredCoding/cerveur/tree/master), with a few differences:  

- Name-casing for files, methods, etc. Mine don't follow convention.
- Makefile uses [static pattern rules](https://makefiletutorial.com/#static-pattern-rules)
- He reads the file using `fgetc`, I use `fread`. I couldn't read the file cleanly without trailing bytes using the former, and `fread` is also shorter.
- I didn't create routes, too lazy.

## Build

`make`

## Run
`./server`

## Checklist
Grabbed off some reddit post:

- [x] Create an internet socket 
- [x] Bind the socket to [localhost](localhost)
- [x] Listen on the socket
- [ ] Block on Accept until a connection is made
- [x] Read on the connected socket
- [x] Figure out how to respond
- [x] Write back on the connected socket
- [x] Close the connection
- [ ] Go back to blocking on Accept  
			
## References
Makefile tutorial: https://makefiletutorial.com/#static-pattern-rules  

Socket API: https://sites.units.it/mumolo/reti_nettuno/bsdsocket.pdf  

HTTP 1.0 spec: https://datatracker.ietf.org/doc/html/rfc1945#section-10.5

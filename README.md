Note that name-casing for files, methods, etc. don't follow convention. There's also no routes.

Grabbed the following checklist off some reddit post to guide implementation:

- [ ] Create an internet socket 
- [ ] Bind the socket to [localhost](localhost)
- [ ] Listen on the socket
- [ ] Block on Accept until a connection is made
- [ ] Read on the connected socket
- [ ] Figure out how to respond
- [ ] Write back on the connected socket
- [ ] Close the connection
- [ ] Go back to blocking on Accept  

See [references section](#references) for resources used, excluding man pages.
	
## Build

```bash
make
```

## Run

```bash
./server
```
		
## References
Makefile tutorial: https://makefiletutorial.com/#static-pattern-rules  

Socket API: https://sites.units.it/mumolo/reti_nettuno/bsdsocket.pdf  

HTTP 1.0 spec: https://datatracker.ietf.org/doc/html/rfc1945#section-10.5

Someone else's implementation: https://github.com/infraredCoding/cerveur/tree/master

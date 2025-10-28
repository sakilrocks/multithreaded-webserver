# multithreaded-webserver

a lightweight **C++ multithreaded web server** that serves static files using **POSIX sockets** and **C++ threads**.   
it can handle multiple clients concurrently and serve HTML pages directly from a `/public` directory.

---

## Features

- Multithreaded request handling  
- Serves static files (HTML, CSS, images, etc.)  
- Simple and clean architecture  
- Customizable web root directory  
- Built with standard C++17 and POSIX sockets  

---

## Project Structure

```
multithreaded-webserver/
├── include/
│   └── server.hpp          # server class header
├── src/
│   ├── main.cpp            # entry point
│   └── server.cpp          # server implementation
├── public/
│   └── index.html          # static web files
├── bin/
│   └── webserver           # compiled exe
├── Makefile                # build config
└── README.md               
```

---

## How It Works

```
  1.	The server creates a TCP socket and binds it to the given port.
  2.	It listens for incoming connections and spawns a thread for each client.
  3.	The thread reads the HTTP request, finds the requested file in /public, and returns the proper HTTP response.
  4.	Multiple clients can connect and be served concurrently.

```

---

## Run

```
./bin/webserver   
```
and visit **http://127.0.0.1:8080**

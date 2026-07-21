# 🗄️ Multithreaded File Server

> A multithreaded file server and client system built with TCP sockets in C, capable of handling multiple clients concurrently using POSIX threads.

## Overview

This project implements a client-server file management system over TCP sockets. The server listens for incoming client connections and processes each one concurrently using **POSIX threads (pthreads)**, allowing multiple clients to interact with the server at the same time without blocking one another.

On the client side, users can upload, download, list, and delete files stored on the server — essentially a lightweight remote file management tool built from the ground up in C.

## ✨ Features

- 📤 **Upload** — send a file from the client to the server, saved in the server's working directory
- 📥 **Download** — retrieve a file from the server and save it locally on the client
- 📋 **List** — display all files currently available on the server
- 🗑️ **Delete** — remove a file from the server
- 🧵 **Concurrent clients** — the server handles multiple simultaneous client connections using pthreads
- 🚪 **Graceful exit** — clients can end their session cleanly via a quit option

## 🗂️ Project Structure
```
MultithreadedFileServer/
├── server.c      # Server implementation
├── client.c      # Client implementation
├── csapp.h       # CS:APP library
├── Makefile      # Builds both server and client
└── README.md
```

## 🛠️ Built With

- **C**
- **POSIX Threads (pthreads)**
- **TCP Sockets**
- CS:APP library (`csapp.h`)

## 🚀 Getting Started

### Requirements

- GCC compiler
- A Linux/Unix environment with C support (JupyterHub, VS Code with a C toolchain, or similar)
- POSIX Threads library (`pthread`)

### Build

```bash
make
```

This compiles both the server and client executables.

### Run

Open two terminals (or two ports/sessions):

**Terminal 1 — start the server:**
```bash
./server 3240
```

**Terminal 2 — connect a client:**
```bash
./client localhost 3240
```

## 📖 Usage

Once a client connects, it's prompted with the following menu:
(1) Upload File
(2) Download File
(3) List Files
(4) Delete File
(5) Quit

| Option | Description |
|--------|-------------|
| **Upload** | Sends a file from the client to the server; the server saves it in its working directory |
| **Download** | Retrieves a file from the server and saves it locally on the client |
| **List** | Displays all files currently in the server's directory |
| **Delete** | Removes a specified file from the server |
| **Quit** | Ends the client session |

Multiple clients can connect and issue commands at the same time — the server spins up a new thread per connection to handle each independently.

## 👤 Author

**Arun Baraili**

package main

import (
    "fmt"
    "net"
    "os"
)

func handleConnection(conn net.Conn) {
    conn.Write([]byte("String"))
}

func server_listener(listener net.Listener) {
    for {
        conn, err := listener.Accept()

        if err != nil {
            fmt.Print(err);
            os.Exit(84)
        }

        handleConnection(conn)
    }
}

func main() {
    fmt.Printf("Launching server.\n")

    args := os.Args[1:]

    if len(args) != 1 {
        fmt.Printf("Error you need to give a port.\n");
        os.Exit(84);
    }

    listener, err := net.Listen("tcp", ":" + args[0])

    if err != nil {
        fmt.Print(err);
        os.Exit(84)
    }

    server_listener(listener)
}
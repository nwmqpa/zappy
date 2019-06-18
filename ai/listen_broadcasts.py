"""Listen to `Bradcast` from other players."""

import random
import sys
from threading import Thread
import time
import socket


class Broadcast_listener(Thread):
    """Thread loaded to listen to other players `Broadcast`."""

    def __init__(self, server_socket: socket.socket) -> None:
        """Init the thread."""
        Thread.__init__(self)
        # self.received_message = ""
        self.server_socket = server_socket

    def run(self) -> str:
        """Code to execute during thread execution."""
        print("IN RUN THRAD OF BROADCAST.")
        received = ""
        while (received.split(" ")[0] != "message"):
            received = self.server_socket.recv(1024).decode()
            if (received == "dead\n"):
                print("Player is dead.")
                exit(0)
            while (received[len(received) - 1] != '\n'):
                received = received + self.server_socket.recv(1024).decode()
            splitted = received.split(" ")
            if (splitted[0] == "message"):
                return (received)
            else:
                return ("")

# # Création des threads
# thread_1 = Broadcast_listener()
# # Lancement des threads
# thread_1.start()
# # Attend que les threads se terminent
# thread_1.join()

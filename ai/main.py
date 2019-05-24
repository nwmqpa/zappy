from ai.verif import basic_verif
from ai.verif import verif_args_values
from ai.get_args import get_arguments
from ai.first_connection import connect_socket
from ai.first_connection import get_client_nb_and_world_size
from ai.clear_received_message import clean_received_message
from ai.parse_inventory import parse_inventory
import socket
import sys

def test(server_socket):
    print("In test\n")

    print('Send     ->', "Look")    # send message
    server_socket.send(("Look" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")

    print('Send     ->', "Inventory")    # send message
    server_socket.send(("Inventory" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    inventory = parse_inventory(new_data)
    print("Inventory -> ", inventory)
    # print("Recv =====>", new_data, "\n")

    print('Send     ->', "Broadcast text")    # send message
    server_socket.send(("Broadcast Text Message Wesh" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")

    print('Send     ->', "Connect_nbr")    # sned message
    server_socket.send(("Connect_nbr" + "\n").encode())
    new_data = server_socket.recv(1024)     # Recv message
    # print('Received ->', repr(new_data))    # print message
    new_data = clean_received_message(repr(new_data))
    print("Recv =====>", new_data, "\n")

    # new_data = server_socket.recv(1024)     # Recv message
    # # print('Received ->', repr(new_data))    # print message
    # new_data = clean_received_message(repr(new_data))
    # print("Recv =====>", new_data, "\n")

def main():
    """Main"""
    basic_verif()
    opt = get_arguments()
    verif_args_values(opt)

    print(repr(opt))
    server_socket = connect_socket(opt)
    client_info = get_client_nb_and_world_size(server_socket, opt)
    print("Client info -> ", repr(client_info) + "\n")

    test(server_socket)


if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        sys.stderr.write(str(e))
        sys.exit(84)

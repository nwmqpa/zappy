"""Clean the message received from the server"""


def clean_received_message(old):
    """Clean and format the message received from the server"""
    # print("In clean_received_message:\nOld -> ", old)
    old = old.replace("b", "")
    old = old.replace("'", "")
    old = old.replace("\\n", " ")
    new = old
    # print("New -> ", new)
    return (new)

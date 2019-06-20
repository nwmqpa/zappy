"""Queue class."""

from typing import List


class Queue:
    """Queue class."""

    def __init__(self) -> None:
        """Create a list."""
        self.queue = list()

    def enqueue(self, data: str) -> bool:
        """Adding elements to queue."""
        self.queue.insert(0, data)
        return True

    def dequeue(self) -> int:
        """Pop out the last element from the queue."""
        if len(self.queue) > 0:
            return self.queue.pop()
        return ("Queue Empty!")

    def size(self) -> int:
        """Get the size of the queue."""
        return len(self.queue)

    def printQueue(self) -> List[str]:
        """Print the elements of the queue."""
        return self.queue

    def first_in(self) -> str:
        """Return oldest elements."""
        if (len(self.queue) >= 1):
            return (self.queue[len(self.queue) - 1])
        else:
            return ("")

# myQueue = Queue()
# print(myQueue.enqueue(5)) #prints True
# print(myQueue.enqueue(6)) #prints True
# print(myQueue.enqueue(9)) #prints True
# print(myQueue.enqueue(5)) #prints False
# print(myQueue.enqueue(3)) #prints True
# print(myQueue.size())     #prints 4
# print(myQueue.dequeue())  #prints 5
# print(myQueue.dequeue())  #prints 6
# print(myQueue.dequeue())  #prints 9
# print(myQueue.dequeue())  #prints 3
# print(myQueue.size())     #prints 0
# print(myQueue.dequeue())  #prints Queue Empty!

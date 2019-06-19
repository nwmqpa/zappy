"""Queue class."""


class Queue:
    """Queue class."""

    def __init__(self):
        """Create a list."""
        self.queue = list()

    def enqueue(self, data):
        """Adding elements to queue."""
        """Checking to avoid duplicate entry (not mandatory)."""
        if data not in self.queue:
            self.queue.insert(0, data)
            return True
        return False

    def dequeue(self):
        """Pop out the last element from the queue."""
        if len(self.queue) > 0:
            return self.queue.pop()
        return ("Queue Empty!")

    def size(self):
        """Get the size of the queue."""
        return len(self.queue)

    def printQueue(self):
        """Print the elements of the queue."""
        return self.queue

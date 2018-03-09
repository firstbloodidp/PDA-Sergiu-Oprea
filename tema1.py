#!/usr/bin/python3

import threading
import time

producLine = []
maxLength = 100

class producerClass(threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print("Starting " + self.name)
        try:
            while True:
                time.sleep(0.7)
                semaforFull.acquire()
                print("Product")
                threadLock.acquire()
                producLine.append('product')
                # Free lock to release next thread
                threadLock.release()
                semaforEmpty.release()
        except KeyboardInterrupt:
            threadLock.release()

class consumerClass(threading.Thread):
    def __init__(self, threadID, name, counter):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print("Starting " + self.name)
        try:
            while True:
                # Get lock to synchronize threads
                semaforEmpty.acquire()
                print("Consume")
                threadLock.acquire()
                del producLine[len(producLine) - 1]
                # Free lock to release next thread
                threadLock.release()
                semaforFull.release()
                time.sleep(0.5)
        except KeyboardInterrupt:
            threadLock.release()

threadLock = threading.Lock()
threads = []

semaforFull = threading.Semaphore(value=maxLength)
semaforEmpty = threading.Semaphore(value=0)

# Create new threads
producer = producerClass(1, "Producer", 1)
consumer = consumerClass(2, "Consumer", 2)

# Start new Threads
producer.start()
consumer.start()

# Add threads to thread list
threads.append(producer)
threads.append(consumer)

# Wait for all threads to complete
for t in threads:
    t.join()
print("Exiting Main Thread")
#!/usr/bin/python3

from threading import Thread, Condition
import time
import random

producLine = []
maxLength = 100
condition = Condition()
global verify 

class producerClass(Thread):
    def __init__(self, threadID, name, counter):
        Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print("Starting " + self.name)
        try:
            while True:
                time.sleep(0.7)
                #semaforFull.acquire()
                print("Product")
                condition.acquire()
                while len(producLine) == maxLength:
                    condition.wait()
                producLine.append('product')
                # Free lock to release next thread
                condition.release()
                condition.notify_all()
                #semaforEmpty.release()
        except KeyboardInterrupt:
            condition.release()

class consumerClass(Thread):
    def __init__(self, threadID, name, counter):
        Thread.__init__(self)
        self.threadID = threadID
        self.name = name
        self.counter = counter

    def run(self):
        print("Starting " + self.name)
        try:
            while True:
                # Get lock to synchronize threads
                #semaforEmpty.acquire()
                print("Consume")
                condition.acquire()
                while len(producLine) == 0:
                    condition.wait()
                del producLine[len(producLine) - 1]
                # Free lock to release next thread
                condition.release()
                condition.notify_all()
                #semaforFull.release()
                time.sleep(0.5)
        except KeyboardInterrupt:
            condition.release()

threads = []

#semaforFull = threading.Semaphore(value=maxLength)
#semaforEmpty = threading.Semaphore(value=0)

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

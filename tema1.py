#!/usr/bin/python3

import threading
import time

producLine = []
maxLength = 100

class myThread (threading.Thread):
   def __init__(self, threadID, name, counter):
      threading.Thread.__init__(self)
      self.threadID = threadID
      self.name = name
      self.counter = counter
   def run(self):
      print ("Starting " + self.name)
      try:
        while True:
          # Get lock to synchronize threads
          threadLock.acquire()
          if self.name == 'Producer':
            consume()
          else:
            produce()
          # Free lock to release next thread
          threadLock.release()
      except KeyboardInterrupt:
        threadLock.release()
        
def consume():
  time.sleep(0.5)
  if len(producLine) > 0:
    print ('Consume', len(producLine))
    del producLine[len(producLine) - 1]
  print ('Consumer wait')
  
def produce():
  time.sleep(0.7)
  if len(producLine) < maxLength:
    producLine.append('product')
    print ('Produce', len(producLine))
  print ('Producer wait')
  
threadLock = threading.Lock()
threads = []

# Create new threads
producer = myThread(1, "Producer", 1)
consumer = myThread(2, "Consumer", 2)

# Start new Threads
producer.start()
consumer.start()

# Add threads to thread list
threads.append(producer)
threads.append(consumer)

# Wait for all threads to complete
for t in threads:
   t.join()
print ("Exiting Main Thread")
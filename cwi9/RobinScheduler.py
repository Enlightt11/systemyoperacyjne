#!/usr/bin/env python3
import sys
import csv

class Process:
    def __init__(self, name, length, start):
        self.name = name
        self.remaining = length
        self.start = start

class RobinScheduler:
    def __init__(self, process, quantum):
        self.waiting = process[:]
        self.ready = []
        self.quantum = quantum
        self.time = 0

    def move_new_process(self):
        while self.waiting and self.waiting[0].start <= self.time:
            p = self.waiting.pop(0)
            print(f"T={self.time} New process {p.name} is waiting for execution (length={p.remaining})")
            self.ready.append(p)

    def run(self):
        print("T=0: No processes currently available")

        while self.waiting or self.ready:
            self.move_new_process()

            if not self.ready:
                self.time = self.waiting[0].start
                continue

            p = self.ready.pop(0)
            run_time = min(self.quantum, p.remaining)

            p.remaining -= run_time
            print(f"T={self.time}: {p.name} will be running for {run_time} time units. Time left: {p.remaining}")

            self.time += run_time
            self.move_new_process()

            if p.remaining == 0:
                print(f"T={self.time}: Process {p.name} has been finished")
            else:
                self.ready.append(p)
        print(f"T={self.time}: No more processes in queues")

def load_processes(path):
    processes = []
    with open(path) as f:
        reader = csv.reader(f)
        for name, length, start in reader:
            processes.append(Process(name, int(length), int(start)))
    return processes

def main():
    if len(sys.argv) != 3:
        print("Invalid amount of arguments!")
        sys.exit(1)

    csv_path = sys.argv[1]
    quantum = int(sys.argv[2])

    processes = load_processes(csv_path)
    rr = RobinScheduler(processes, quantum)
    rr.run()

if __name__ == "__main__":
    main()

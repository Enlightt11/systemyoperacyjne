import math

class BuddyAllocator:
    def __init__(self, size, limit):
        self.size = size
        self.limit = limit
        self.min_block= size // (limit ** 2)

        self.free_blocks = {size: [0]}
        self.used = {}

    def alloc(self, size):
        block = 2 ** math.ceil(math.log2(size))

        if block < self.min_block:
            block = self.min_block

        current = block
        while current <= self.size:
            if current in self.free_blocks and self.free_blocks[current]:
                address = self.free_blocks[current].pop()

                while current > block:
                    current //= 2
                    self.free_blocks.setdefault(current, []).append(address + current)

                self.used[address] = block
                return address, block
            current *= 2   
        return None 

    def free(self, address):
        if address not in self.used:
            return
        
        size = self.used.pop(address)

        while True:
            buddy = address ^ size
            if size in self.free_blocks and buddy in self.free_blocks[size]:
                self.free_blocks[size].remove(buddy)
                address = min(address, buddy)
                size *= 2
            else:
                self.free_blocks.setdefault(size, []).append(address)
                break

if __name__ == "__main__":
    b = BuddyAllocator(2048, 6)

    a = b.alloc(100)
    print("alloc a:", a)

    c = b.alloc(200)
    print("alloc c:", c) 

    b.free(a[0])
    print("free a")

    b.free(c[0])
    print("free c")
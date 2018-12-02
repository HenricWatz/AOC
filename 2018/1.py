
from util import *


if __name__ == "__main__":
    
    # Read input
    num_list = readInput("1.txt", "scalar_list")

    # Part one, find end frequency
    freq = 0
    for change in num_list:
        freq += change

    print("End frequency (part 1): " + str(freq))

    # Part two, find first duplicate frequency
    freq_list = []
    freq = 0
    idx = 0
    while not freq in freq_list:

        # Add and calc new frequency
        freq_list.append(freq)
        freq += num_list[idx]

        # Print length for debugging
        print("Unique frequencies detected: " + str(len(freq_list)), end='\r')
            
        # Circular list 
        idx += 1
        if idx >= len(num_list):
            idx = 0

    print("Fist duplicate found (part 2): " + str(freq))

    
    
        
    



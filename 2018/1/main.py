

def readInput( file, type ):
    
    input_file = open(file, "r")

    # row delimitered list of scalars
    if ( type == "scalar_list" ):
        output = []
        for row in input_file:
            output.append(int(row))

    # Return Output
    return output


if __name__ == "__main__":
    
    # Read input
    num_list = readInput("input_one.txt", "scalar_list")

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
        print(len(freq_list))
            
        # Circular list 
        idx += 1
        if idx >= len(num_list):
            idx = 0

    print("Fist duplicate found (part 2): " + str(freq))

    
    
        
    



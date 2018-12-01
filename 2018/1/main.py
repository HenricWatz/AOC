

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
    num_list = readInput("input_one.txt", "scalar_list")

    freq = 0
    for change in num_list:
        freq += change

    print(freq)
        
    




# Util function reading input file
def readInput( file, type ):
	
	input_file = open(file, "r")

    # row delimitered list of scalars
	if ( type == "scalar_list" ):
		output = []
		for row in input_file:
			output.append(int(row))
			
	# row delimitered list of strings
	if ( type == "text_list" ):
		output = []
		for row in input_file :
			output.append(str(row))

    # Return Output
	return output
	
	


    
    
        
    




def readInput( file, type ):
	
	input_file = open(file, "r")
			
	# row delimitered list of strings
	if ( type == "text_list" ):
		output = []
		for row in input_file :
			output.append(str(row))

    # Return Output
	return output


if __name__ == "__main__":
	
	# Read input
	string_list = readInput("2.txt", "text_list")
	
	# Part one, find checksum
	total_amount_list = [0] * 10
	for string in string_list :
	
		# Check string for uccurances
		amount_set = set([])
		for c in string:
			amount_set.add(string.count(c))				
				
		# Add string to total
		for amount in amount_set :
			
			if amount > 1 :
				total_amount_list[amount] += 1
	
	# Calc checksum
	checksum = 1
	for amount in total_amount_list[:4] :
	
		if (amount > 0) :
			checksum = checksum * amount
			
	print("Checksum (part 1):" + str(checksum))
	
	# Part two, prototype fabric
	string_lenth = len(string_list[0]) - 1
	for string_idx in range(0, (len(string_list))):
	
		for compare_idx in range(string_idx + 1, len(string_list)):
		
			# compare strings
			matches = 0
			for char_idx in range(0, string_lenth):
				if string_list[string_idx][char_idx] == string_list[compare_idx][char_idx]:
					matches += 1
					
			if matches == (string_lenth-1):
				#print ("idx " + str(string_idx) + " and idx " + str(compare_idx) + " match")
				
				# build prototype
				prototype = ""
				for char_idx in range(0, string_lenth):
					if string_list[string_idx][char_idx] == string_list[compare_idx][char_idx]:
						prototype += string_list[string_idx][char_idx]
						
				print ("Prototype (part 2): " + prototype)
				
			
				
	
		
		
		
			
			

	

	
	
		
	




from re import split
from math import floor
	
if __name__ == "__main__":
	
	# Read input
	input_file = open('3.txt', "r")
	id = []
	xpos = []
	ypos = []
	xsize = []
	ysize = []

	# build structure
	for row in input_file:
		tokens = split('#| @ |,|: |x', str(row))
		id.append(int(tokens[1]))
		xpos.append(int(tokens[2]))
		ypos.append(int(tokens[3]))
		xsize.append(int(tokens[4]))
		ysize.append(int(tokens[5]))
	
	# build claim map
	claim_map = [ [ 0 	for i in range(max(xpos)+max(xsize)) ] \
						for j in range(max(ypos)+max(ysize)) ]
						
	overlap = 0
	
	safe_ids = set([])
	for i in id:
		safe_ids.add(i)
	
	for i in range(0, len(id)):
		for x in range(xpos[i], xpos[i]+xsize[i]):
			for y in range(ypos[i], ypos[i]+ysize[i]):
				if claim_map[x][y] == 0:
					claim_map[x][y] += id[i]
				else:
					if claim_map[x][y] != -1:
						safe_ids.discard(claim_map[x][y])
						safe_ids.discard(id[i])
						claim_map[x][y] = -1
						overlap += 1
					else:
						safe_ids.discard(id[i])
	
	print("Total amount of overlap (part 1): " + str(overlap))
		
	remaining_id = set([])
	for row in claim_map:
		for elem in row:
			remaining_id.add(elem)
		
	print("Id of none overlapping pattern: " + str(safe_ids))
	
	
	

	#string_list = readInput("2.txt", "text_list")
	
	
				
			
				
	
		
		
		
			
			

	

	
	
		
	



from re import findall

def get_dimensions(points):

    best = ([1000, 0], [1000, 0])
    
    for p in points:
        
        # over x and y
        for i in range(0,2):
            # minimum
            if p[i] < best[i][0]:
                best[i][0] = p[i]

            # maximum
            if p[i] > best[i][1]:
                best[i][1] = p[i]

    return best

            

def populate_map(points):

    # Get dimensions
    x_dim, y_dim = get_dimensions(points)
    
    # Build map with closest point for each coord
    point_map = []
    for x in range(x_dim[0], x_dim[1]):
        point_map.append([])
        for y in range(y_dim[0], y_dim[1]):
            # Get closest point
            closest_dist = x_dim[1] + y_dim[1] # whole map
            for p in points:
                dist = abs(p[0] - x) + abs(p[1] - y)
                if dist < closest_dist:
                    closest_point = points.index(p)
                    closest_dist = dist
                elif dist == closest_dist:
                    closest_point = -1

            point_map[-1].append(closest_point)

    return point_map
                    

    

    
    
    

if __name__ == "__main__":

    # Read input
    input_file = open("6.txt", "r")
    points = []
    for row in input_file:
        tokens = findall('\d+', str(row))
        points.append([int(tokens[0]), int(tokens[1])])

        
    # Find area of all points
    point_map = populate_map(points)
    area_list = []
    for i in range(0, len(points)):
        area = 0
        
        if point_map[0].count(i) != 0:
            area = -1
        elif point_map[-1].count(i) != 0:
            area = -1
        else:
            for row in point_map:
                if row[0] == i:
                    area = -1
                elif row[-1] == i:
                    area = -1
                else:
                    if area != -1:
                        area += 1
        area_list.append(area)                


    best_area = max(area_list)
    print("Largest area without infinit area is(part 1): " + \
          str(best_area))

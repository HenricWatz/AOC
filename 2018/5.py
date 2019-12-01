
from re import split, findall
from datetime import *

def react(polymer):
    idx = 1
    while idx < len(polymer):
        lhs = polymer[idx - 1]
        rhs = polymer[idx]

        if (lhs.upper() == rhs.upper()):
            if ((lhs.isupper() and rhs.islower()) or \
                (lhs.islower() and rhs.isupper())):
                polymer = polymer[:idx-1] + polymer[idx+1:]
                if idx > 1:
                    idx -= 1
            else:
                idx += 1
        else:
            idx += 1

    return polymer


if __name__ == "__main__":
    
    # Read input
    input_file = open("5.txt", "r")

    polymer = input_file.read().replace('\n','')

    # React polymer
    new_polymer = react(polymer)
    print("Length or remainding polymer (part 1): " \
          + str(len(new_polymer)))

    # Improve polymer
    best_length = len(polymer)
    best_polymer = polymer
    for c in range(ord('a'), ord('z')):
        improved = polymer
        improved = improved.replace(chr(c), '')
        improved = improved.replace(chr(c).upper(), '')

        improved_length = len(react(improved))
        if improved_length < best_length:
            best_length = improved_length
            best_polymer = improved

    print("Best reacted length achived (part 2): " + str(best_length))
        

    
        

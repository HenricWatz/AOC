
from re import split, findall
from datetime import *

class activity_log():
    
    def __init__(self):
        self.ids = []
        self.time_logs = []

    # Get index of id
    def get_index_from_id(self, id):
        
        try:
            idx = self.ids.index(id)
        except ValueError:
            self.ids.append(id)
            idx = self.ids.index(id)
            self.time_logs.append([0]*60)

        return idx

    def get_id_from_index(self, idx):
        return self.ids[idx]

    
    # Add period of sleep
    def add_period(self, id, start, end):

        # Get index
        idx = self.get_index_from_id(id)

        # Add period
        for t in range(start, end):
            self.time_logs[idx][t] += 1

    def get_sleepiest(self):

        highest = 0
        for log in self.time_logs:
            if sum(log) > highest:
                highest = sum(log)
                idx = self.time_logs.index(log)
                
        return self.get_id_from_index(idx)

    def get_most_sleept_minute(self, id):
        idx = self.get_index_from_id(id)
        log = self. time_logs[idx]

        return log.index(max(log))

    def get_most_safe_min_and_id(self):

        best = 0
        for log in self.time_logs:
            if max(log) > best:
                idx = self.time_logs.index(log)
                best = max(log)
                output = (self.get_id_from_index(idx),\
                          log.index(max(log)))
                
        return output

    # Print log
    def disp(self):
        for row in self.time_logs:
            print(str(row))

if __name__ == "__main__":

    # local
    log = activity_log()
    
    # Read input
    input_file = open("4.txt", "r")

    # Read associate datetime with happening
    input_list = []
    for row in input_file:
        tokens = split('] ',row)
        time = datetime.strptime(tokens[0][1:],'%Y-%m-%d %H:%M')
        input_list.append((time, tokens[1]))

    # Sort by datetime
    input_list.sort()

    # Log Guard activity
    for entry in input_list:
        if entry[1] == "falls asleep\n":
            start_time = entry[0].minute
        elif entry[1] == "wakes up\n":
            end_time = entry[0].minute
            log.add_period(id, start_time, end_time)
        else:
            try:
                id = int(findall('\d+', entry[1])[0])
            except IndexError:
                print(entry[1])
            
    # Get "best" guard
    id = log.get_sleepiest()
    minute = log.get_most_sleept_minute(id)

    print("Best guard (part 1) is #" + str(id) + " at minute " + \
          str(minute) + " giving ans: " + str(minute*id))

    # Get safest guard
    id, minute = log.get_most_safe_min_and_id()
            
    print("Safest guard (part 2) is #" + str(id) + " at minute " + \
          str(minute) + " giving ans: " + str(minute*id))


dateRanges = []
counts = []

with open("log.inp", "r") as f :
    line = f.readline()
    while (True) :
        line = f.readline()
        if not line : break
        
        dateRange = [int(num) for num in line.split()]
        dateRanges.append(dateRange)

        counts.append(0)
        counts.append(0)

with open("syslog.txt", "r") as log :
    numLog = int(log.readline())

    for i in range(numLog) :
        line = log.readline()
        sequence = line.split()

        day = int(sequence[0])

        for j in range(len(dateRanges)) :
            if dateRanges[j][0] > day :
               counts[j * 2] = counts[j * 2] + len(sequence) - 1
            elif dateRanges[j][0] == day :
                for k in range(1, len(sequence) - 1) :
                    t = int(sequence[k])

                    if dateRanges[j][1] > t : 
                        counts[j * 2] = counts[j * 2] + 1;

            if dateRanges[j][2] > day :
               counts[j * 2 + 1] = counts[j * 2 + 1] + len(sequence) - 1
            elif dateRanges[j][2] == day :
                for k in range(1, len(sequence) - 1) :
                    t = int(sequence[k])

                    if dateRanges[j][3] > t :
                        counts[j * 2 + 1] = counts[j * 2 + 1] + 1;


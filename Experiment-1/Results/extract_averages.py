from sys import argv

if len(argv) == 1:
    print("Usage: python3 extract_averages.py <filename")
    exit(-1)

handle = open(argv[1])
contents = handle.read().split('\n')

improvements = []
oldtimes = []
newtimes = []
currOldDist = 0
currNewDist = 0

isOld = True
for line in contents:
    if len(line) == 0:
        continue

    firstWord = line.split()[0]
    if firstWord == 'Shortest' and isOld:
        currOldDist = float(line.split()[-1])
    elif firstWord == 'Shortest':
        currNewDist = float(line.split()[-1])
        print(currOldDist,currNewDist)
        improvements.append(currOldDist/currNewDist)

    if firstWord == 'time:' and isOld:
        oldtimes.append(float(line.split()[1]))
        isOld = False
    elif firstWord == 'time:':
        newtimes.append(float(line.split()[1]))
        isOld = True


ave_improvement = sum(improvements)/len(improvements)
oldAverage = sum(oldtimes)/len(oldtimes)
newAverage = sum(newtimes)/len(newtimes)

print("For",argv[1],":")
print("Average Improvement:",ave_improvement)
print("Old LLL average:", oldAverage)
print("New LLL average:", newAverage)
print("Average Speedup =", oldAverage/newAverage)

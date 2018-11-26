from sys import argv

if len(argv) == 1:
    print("Usage: python3 extract_averages.py <filename")
    exit(-1)

handle = open(argv[1])
contents = handle.read().split('\n')

oldLLLTimes = []
newLLLTimes = []
currOldDist = 0
currNewDist = 0

good_cases = []
bad_cases_dist = []

isOld = True
isGood = True
for line in contents:
    if len(line) == 0:
        continue

    firstWord = line.split()[0]
    if firstWord == 'Shortest' and isOld:
        currOldDist = float(line.split()[-1])
    elif firstWord == 'Shortest':
        currNewDist = float(line.split()[-1])

    if firstWord == 'time:' and isOld:
        oldLLLTimes.append(float(line.split()[1]))
        isOld = False
    elif firstWord == 'time:':
        newLLLTimes.append(float(line.split()[1]))
        tuple = (oldLLLTimes[-1], newLLLTimes[-1])
        if isGood:
            good_cases.append(tuple)
        else:
            isGood = True
            print(currOldDist,currNewDist)
            bad_cases_dist.append(currNewDist/currOldDist)
        isOld = True

    if firstWord == "No":
        isGood = False

oldAverage = sum(oldLLLTimes)/len(oldLLLTimes)
newAverage = sum(newLLLTimes)/len(newLLLTimes)

oldgood = [good_case[0] for good_case in good_cases ]
newgood = [good_case[1] for good_case in good_cases ]
oldAverageOld = sum(oldgood)/len(oldgood)
newAverageOld = sum(newgood)/len(newgood)

ave_bad_performance = sum(bad_cases_dist)/len(bad_cases_dist)

print("For",argv[1],":")
print("Old LLL average:", oldAverage)
print("New LLL average:", newAverage)
print("Average Speedup =", oldAverage/newAverage)
print(len(oldgood),"good cases")
print("Average Speedup in good cases =", oldAverageOld/newAverageOld)
print("Average Bad Performance =", ave_bad_performance)

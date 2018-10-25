from sys import argv

if not len(argv) == 2:
    print("Usage: python scrap_matrix.py <path to file>")
    exit(-1)

filename = argv[1]

handle = open(filename)
matrix_raw = handle.read().split('\n')

# three steps of pruning
matrix_raw.pop()
matrix_raw.pop()
matrix_raw[0] = matrix_raw[0][1:]

matrix = []
for i in range(len(matrix_raw)):
    matrix.append(matrix_raw[i][1:-1])
    # print (matrix[i])

n = len(matrix)

handle = open("matrix.txt","w+")
contents = str(n) + " " + str(n) + '\n' + '\n'.join(matrix)
# print(contents)
handle.write(contents)
handle.close()

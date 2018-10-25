from sys import argv
import requests

if not len(argv) == 2:
    print("Usage: python scrap_matrix.py <url of matrix>")
    exit(-1)

url = argv[1]

req = requests.get(url)

matrix_raw = req.content.decode('utf-8').split('\n')

# three steps of pruning
matrix_raw.pop()
matrix_raw.pop()
matrix_raw[0] = matrix_raw[0][1:]

matrix = []
for i in range(len(matrix_raw)):
    matrix.append(matrix_raw[i][1:-1])
    # print (matrix[i])

n = len(matrix)

handle = open("matrix"+str(n)+".txt","w+")
contents = str(n) + " " + str(n) + '\n' + '\n'.join(matrix)
# print(contents)
handle.write(contents)
handle.close()

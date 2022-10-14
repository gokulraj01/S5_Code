data = [
     ['Athira', 'Gokul', "Greeshma", 'Chrislin', 'George'],
     ['Athirampuzha', 'Medical College', 'Kannanmoola', 'Kudapanamkunn'],
     [f'Asset{i}' for i in range(1,10)]
 ]

import random

def makedummy():
    dummies = [random.choice(col) for col in data]
    op = "("
    for i in dummies:
        op += f"'{i}', "
    return op[:-2]+")"

n = input("How many? ")
for _ in range(int(n)):
    print(makedummy())
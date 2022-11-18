import random

comp = ["ABC", "Google", "Universal"]

f = open("dt.txt", 'r')
l = f.readlines()
for line in l:
    print(f"{line[:-1]}, '{random.choice(comp)}', '{random.randint(1000,999999)}');")
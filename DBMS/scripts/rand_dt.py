# data = [
     # ["Amy Lowe", "Kennith Lind", "Dr. Eloy Huel", "Chad Hilll", "Daphne Rogahn", "Garrett Stanton", "Mrs. Monroe Hackett", "Antonia Dooley", "Hayley Durgan", "Mrs. Alaina Ward", "Nickolas Mann", "Monserrate Davis", "Bella McClure", "Ethyl Gorczany", "Royce Mayer", "Ms. Jabari McKenzie", "Amanda Romaguera", "Juliana Morissette", "Sebastian Crona", "Katelyn Schmeler"],
     
     # [f'Branch{i}' for i in range(1,100)],
     # ["Mumbai", "Bengaluru", "Delhi", "Hyderabad", "Ahmedabad", "Chennai", "Kolkata", "Surat", "Pune", "Jaipur", "Cuddapah", "Lucknow", "Kanpur", "Nagpur", "Indore", "Thana", "Hubli", "Bhopal", "Pimpri", "Visakhapatnam", "Patna", "Vadodara", "Dhuri", "Ghaziabad", "Ludhiana", "Agra", "Madurai", "Nashik", "Faridabad", "Meerut", "Rajkot", "Kalyan", "Varanasi", "Srinagar", "Aurangabad", "Dhanbad", "Amritsar", "Navi Mumbai", "Allahabad, Uttar Pradesh", "Narsimhapur"],
     # [f'Asset{i}' for i in range(1,20)]
 # ]

import random

data = [
    [random.randint(111111, 999999) for _ in range(100)],
    [f'Branch{i}' for i in range(1,100)],
    [random.randint(0, 100000) for _ in range(100)],
]


def makedummy():
    dummies = [f""]    
    op = "("
    for i in dummies:
        op += f"'{i}', "
    return op[:-2]+"),"

n = input("How many? ")
for _ in range(int(n)):
    print(makedummy())
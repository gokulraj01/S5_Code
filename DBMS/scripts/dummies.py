TABLE = "employee"

NAMES =  ["Amy Lowe", "Kennith Lind", "Dr. Eloy Huel", "Chad Hilll", "Daphne Rogahn", "Garrett Stanton", "Mrs. Monroe Hackett", "Antonia Dooley", "Hayley Durgan", "Mrs. Alaina Ward", "Nickolas Mann", "Monserrate Davis", "Bella McClure", "Ethyl Gorczany", "Royce Mayer", "Ms. Jabari McKenzie", "Amanda Romaguera", "Juliana Morissette", "Sebastian Crona", "Katelyn Schmeler"]

STREET = ["Deal", "Vernal", "Ironwood", "Wauwatosa", "Crewkerne", "Hialeah", "Norwich", "Dubbo", "Melton Mowbray", "Nags Head", "Keynsham", "Gallipolis", "Inverell", "Potsdam", "Lorain", "Dalby", "Millburn", "Monett", "Price", "Cocoa Beach"]

CITIES = ["Mumbai", "Bengaluru", "Delhi", "Hyderabad", "Ahmedabad", "Chennai", "Kolkata", "Surat", "Pune", "Jaipur", "Cuddapah", "Lucknow", "Kanpur", "Nagpur", "Indore", "Thana", "Hubli", "Bhopal", "Pimpri", "Visakhapatnam", "Patna", "Vadodara", "Dhuri", "Ghaziabad", "Ludhiana", "Agra", "Madurai", "Nashik", "Faridabad", "Meerut", "Rajkot", "Kalyan", "Varanasi", "Srinagar", "Aurangabad", "Dhanbad", "Amritsar", "Navi Mumbai", "Allahabad", "Narsimhapur"]

BRANCH = ['Branch 0', 'Branch 1', 'Branch 2', 'Branch 3', 'Branch 4', 'Branch 5', 'Branch 6', 'Branch 7', 'Branch 8', 'Branch 9', 'Branch 10', 'Branch 11', 'Branch 12', 'Branch 13', 'Branch 14', 'Branch 15', 'Branch 16', 'Branch 17', 'Branch 18', 'Branch 19', 'Branch 20', 'Branch 21', 'Branch 22', 'Branch 23', 'Branch 24', 'Branch 25', 'Branch 26', 'Branch 27', 'Branch 28', 'Branch 29', 'Branch 30', 'Branch 31', 'Branch 32', 'Branch 33', 'Branch 34', 'Branch 35', 'Branch 36', 'Branch 37', 'Branch 38', 'Branch 39', 'Branch 40', 'Branch 41', 'Branch 42', 'Branch 43', 'Branch 44', 'Branch 45', 'Branch 46', 'Branch 47', 'Branch 48', 'Branch 49']

MAN_NAME = ["Oluwajomiloju", "Maho", "Amir", "Jozie", "Iyuna", "Keyora", "Pilot", "Dartha", "Jalyn", "Ashilee", "Jamise", "Zhyon", "Hitomi", "Virga", "Narjis", "Jayvn", "Majed", "Chanaya", "Tammyann", "Sakariye", "Shareem", "Marcuse", "Ashee", "Estee", "Xariah", "Juliaunna", "Izetta", "Coleena", "Zahcary", "Severi", "Fahad", "Shaneeka", "Govind", "Mesai", "Ifechukwu", "Azaleah", "Bunny", "Moira", "Tyrhianna", "Traherne", "Bertalan", "Yilin", "Jaquette", "Jawon", "Giles", "Breyannah", "Zaiyana", "Aurra", "Jayvion", "Sidhanth"]

LN = [424538, 192307, 929650, 666889, 773525, 967021, 268750, 740204, 719972, 839526, 792063, 669193, 446396, 111668, 929440, 149663, 882744, 224611, 893406, 854550, 191410, 500017, 560490, 424177, 773554, 544815, 593227, 490903, 160915, 798110]

AN = [49711184, 38632341, 77866071, 83343433, 72848610, 59506676, 87883464, 63044586, 18364738, 16608314, 89360760, 34124751, 92418130, 22503873, 96183129, 35684531, 94074732, 73560196, 74826117, 59621497, 51921822, 73128040, 52302415, 91927461, 91189824, 95813731, 85357257, 22919629, 69743017, 63015546, 50321490, 95027704, 35538320, 41635028, 14977666, 56390022, 59820882, 61096693, 59253212, 97275526, 11400127, 28138521, 80722199, 42313746, 60559051, 94245903, 20702139, 69953781, 71995970, 23823627]

MONTH = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"]

import random

s = []

for i in range(len(MAN_NAME)):
    v1 = MAN_NAME[i]
    v2 = random.choice(BRANCH)
    v3 = f"{random.randint(1,30)}-{random.choice(MONTH)}-{random.randint(1950,2005)}"
    v4 = random.randint(5000,450000)
    print(f"INSERT INTO {TABLE} VALUES (\"{v1}\", \"{v2}\", \"{v3}\", \"{v4}\");")
    # print(f"INSERT INTO {TABLE} VALUES (\"{v1}\", \"{v2}\", \"{v3}\");")
    # print(f"INSERT INTO {TABLE} VALUES (\"{v2}\", \"{v3}\");")

print(s)
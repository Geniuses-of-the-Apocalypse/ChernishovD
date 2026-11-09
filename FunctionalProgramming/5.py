from functools import reduce

STUDENTS = tuple ((
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5},)) 

# Уровень 1
print(tuple(map(
    lambda student: f"Имя: {student['name']}, Оценка: {student['grade']}",
    STUDENTS))) 
 

# Уровень 2
print(tuple(filter(lambda student: student["grade"] > 4.0, STUDENTS))) 

# Уровень 3 
GOOD_STUDENTS = filter(lambda student: student["grade"] > 4.0, STUDENTS)

total_age, count = reduce(
    lambda acc, student: (acc[0] + student["age"], acc[1] + 1),GOOD_STUDENTS,(0, 0))
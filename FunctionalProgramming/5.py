from functools import reduce

students = [
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5},
]

# Уровень 1
formatted_students = map(
    lambda student: f"Имя: {student['name']}, Оценка: {student['grade']}",
    students)
for line in formatted_students:
    print(line)

# Уровень 2
good_students = filter(lambda student: student["grade"] > 4.0, students)
for student in good_students:
    print(student)

# Уровень 3 
good_students = filter(lambda student: student["grade"] > 4.0, students)

total_age, count = reduce(
    lambda acc, student: (acc[0] + student["age"], acc[1] + 1),
    good_students, (0, 0))


from functools import reduce

STUDENTS = tuple((
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5}))
#1
def format_students():
    def format_student(students):
        return map(lambda s: f"Имя: {s['name']}, Оценка: {s['grade']}", students)
    return format_student

#2
def filter_by_grade():
    def is_above_grade(students):
        return filter(lambda s: s['grade'] > 4.0, students)
    return is_above_grade
    
#3
def average_age():
    def accumulate(students):
        return reduce(
            lambda acc, student: (acc[0] + student["age"], acc[1] + 1),
            filter(lambda s: s['grade'] > 4.0, students),
            (0, 0),
        )
    return accumulate
    
fs = format_students()
fbg = filter_by_grade()
aa = average_age()

print(tuple(fs(STUDENTS)))
print(tuple(fbg(STUDENTS)))
TOTAL_AGE, COUNT = aa(STUDENTS)
print(TOTAL_AGE / COUNT)

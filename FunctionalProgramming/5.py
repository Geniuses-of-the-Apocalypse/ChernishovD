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
        return f"Имя: {student['name']}, Оценка: {student['grade']}"
    return tuple(map(format_student, students))

#2
def filter_by_grade():
    def is_above_grade(students, min_grade=4.0):
        return student["grade"] > min_grade
    return tuple(filter(is_above_grade, students))
    
#3
def average_age():
    def accumulate(acc, students):
        total_age, count = acc
        return total_age + student["age"], count + 1
    total_age, count = reduce(accumulate, students, (0, 0))
    return total_age / count if count else 0
    
fs = format_students()
fbg = filter_by_grade()
aa = average_age()
print(fs(STUDENTS))
print(fbg(STUDENTS))
print(aa(FILTERED_STUDENTS))

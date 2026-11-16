from functools import reduce

STUDENTS = tuple((
    {"name": "Анна", "age": 20, "grade": 4.5},
    {"name": "Борис", "age": 22, "grade": 3.8},
    {"name": "Виктор", "age": 19, "grade": 4.2},
    {"name": "Галина", "age": 21, "grade": 4.9},
    {"name": "Дмитрий", "age": 23, "grade": 3.5}))
#1
def format_students(students):
    def format_student(student):
        return f"Имя: {student['name']}, Оценка: {student['grade']}"
    return tuple(map(format_student, students))

#2
def filter_by_grade(students, min_grade=4.0):
    def is_above_grade(student):
        return student["grade"] > min_grade
    return tuple(filter(is_above_grade, students))
    
#3
def average_age(students):
    def accumulate(acc, student):
        total_age, count = acc
        return total_age + student["age"], count + 1
    total_age, count = reduce(accumulate, students, (0, 0))
    return total_age / count if count else 0


FORMATTED_STUDENTS = format_students(STUDENTS)
print(FORMATTED_STUDENTS)

FILTERED_STUDENTS = filter_by_grade(STUDENTS)
print(FILTERED_STUDENTS)

print(average_age(FILTERED_STUDENTS))

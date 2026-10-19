from functools import partial
# Уровень 1
# Каррированная функция через вложенные lambda:
filter_by = lambda key: lambda value: lambda items: [
    item for item in items if item.get(key) == value
]

items = [
    {"name": "apple",  "category": "fruit"},
    {"name": "carrot", "category": "vegetable"},
    {"name": "banana", "category": "fruit"},]

# Пример использования
print(filter_by("category")("fruit")(items))

# Уровень 2
filter_by_category = partial(
    lambda key, value, items: [i for i in items if i.get(key) == value],
    "category",)

# Фиксируем ещё и value="fruit" -> получаем filter_fruits(items)
filter_fruits = partial(filter_by_category, "fruit")

print(filter_fruits(items))

# Уровень 3
greater_than = lambda threshold: lambda x: x > threshold

# Фиксируем порог через каррирование
over_five = greater_than(5)

numbers = [1, 6, 8, 2, 9]
filtered = list(filter(over_five, numbers))
print(filtered)
# [6, 8, 9]

# Через partial 
over_five_p = partial(lambda threshold, x: x > threshold, 5)
print(list(filter(over_five_p, numbers)))
# [6, 8, 9]

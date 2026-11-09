#e18ab9b49eb75df297bfe4b90b54eff8eb95673ce326e4ed52644fb167c922d2
from functools import partial

# Уровень 1
filter_by = lambda key: lambda value: lambda items: tuple (
    item for item in items if item.get(key) == value)

ITEMS = (
    {"name": "apple",  "category": "fruit"},
    {"name": "carrot", "category": "vegetable"},
    {"name": "banana", "category": "fruit"},)

print(filter_by("category")("fruit")(ITEMS))

#  Уровень 2
FILTER_BY_CTEGORY = partial(filter_by, "category")

# Уровень 3 
GREATER_THAN = lambda threshold: lambda x: x > threshold

NUMBERS = (1, 6, 8, 2, 9)

print(list(filter(GREATER_THAN(5), NUMBERS)))
# [6, 8, 9]

import csv
from typing import Optional

CSV_DATA = """date,item,quantity,price
2024-01-01,Apple,10,1.5
2024-01-02,Banana,5,2.0
2024-01-03,Orange,3,3.0
2024-01-04,Apple,2,1.5
2024-01-05,Grape,1,5.0
2024-01-06,Banana,7,2.0
2024-01-07,Orange,4,3.0"""


def parse_csv(data: str) -> list[dict]:
    return list(csv.DictReader(data.splitlines()))


def compute_revenue(rows: list[dict]) -> float:
    return sum(map(lambda x: int(x["quantity"]) * float(x["price"]), rows))


def top_item(rows: list[dict]) -> Optional[dict]:
    if not rows:
        return None
    try:
        return max(rows, key=lambda x: int(x["quantity"]) * float(x["price"]))
    except (ValueError, TypeError, KeyError):
        return None


rows = parse_csv(CSV_DATA)

print(f"\n1. Всего записей: {len(rows)}")
for i, x in enumerate(rows, 1):
    print(f"   {i}. {x}")

total_revenue = compute_revenue(rows)
print(f"\n2. Общая выручка: {total_revenue:.2f}")

best = top_item(rows)
if best:
    quantity = int(best.get('quantity', 0))
    price = float(best.get('price', 0))
    revenue = quantity * price
    print(f"\n3. Товар с максимальной выручкой:")
    print(f"   {best}")
    print(f"   Выручка: {revenue:.2f}")

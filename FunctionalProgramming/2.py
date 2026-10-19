#5cc74fb2ffaf4a2ca7d651bbcb2ddeac
import re
from typing import Optional
from collections import Counter

CSV_TEXT = """\
Тест, ТЕСТ  тест Т.Е.С."Т"
"""
# 1
def split_words(text: str) -> list[str]:
    return re.findall(r'[а-яё]+', text.lower())
# 2
def count_word_frequencies(words: list[str]) -> dict[str, int]:
    return dict(Counter(words))
# 3
def top_word(freq: dict[str, int]) -> Optional[str]:
    return max(freq, key=freq.get) if freq else None
  
print(CSV_TEXT)

print("Слова:", split_words(CSV_TEXT))
print("Самое частое слово:", top_word(count_word_frequencies(split_words(CSV_TEXT))))
print(f"Количество: {count_word_frequencies(split_words(CSV_TEXT))[top_word(count_word_frequencies(split_words(CSV_TEXT)))] if top_word(count_word_frequencies(split_words(CSV_TEXT))) else 0}")

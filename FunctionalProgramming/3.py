#5cc74fb2ffaf4a2ca7d651bbcb2ddeac

from dataclasses import dataclass
from enum import Enum, auto
from typing import Generic, TypeVar, Union

# 1
class LoadState(Enum):
    LOADING = auto()
    SUCCESS = auto()
    ERROR = auto()
  
# 2
@dataclass(frozen=True)
class User:
    name: str
    age: int
    email: str

# 3
T = TypeVar("T")
E = TypeVar("E")


@dataclass(frozen=True)
class Success(Generic[T]):
    value: T

@dataclass(frozen=True)
class Failure(Generic[E]):
    error: E

Result = Union[Success[T], Failure[E]]

def load_users() -> Result[list[User], str]:
    users: list[User] = [
        User(name="Art", age=46, email="321@mail.com"),
        User(name="Oleg", age=31, email="123@gmail.com"),
    ]
    if not users:
        return Failure("None users")
    return Success(users)

print(f"LoadState = {len(list(LoadState))}")  # 3

result = load_users()

match result:
    case Success(value):
        print("Users:")
        for i in value:
            print(f"   - {i.name}, {i.age}, {i.email}")
    case Failure(error):
        print(f"Error: {error}")

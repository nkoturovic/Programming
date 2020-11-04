import macros

# type
#   Length = object
#     from_size : uint64
#     to_size : uint64

# template length(ffrom : int, to : int): untyped =
#   func isSatisfied(str : string): bool =
#     return (ffrom < str.len) and (str.len < to)
#


type 
  Field = object
    type : typeOfField
    .
    .
    .

type
  Person = object
    age : Field[int, between(18,99)]
    name : Field[string, length(2, 32), capitalized]

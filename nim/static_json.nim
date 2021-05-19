import json

type
  User = object
    username : string
    age : int

static:
  const user = User(username: "necer", age: 25)
  echo(%user)

  var j = parseJson("""
    {
      "username" : "kotur",
      "age" : 25
    }
  """)

  echo(j)

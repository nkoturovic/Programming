import macros

macro model*(head, body : untyped): untyped =
  var typeName : NimNode = head
  result = newStmtList()

  template typeDecl(a): untyped =
    type a* = object

  var objType = getAst(typeDecl(typeName))

  var recList = newNimNode(nnkRecList)
  recList.add(newIdentDefs(ident("name"), ident("string")))

  objType[0][2][2] = recList
  result.add(objType)
  echo(result.treeRepr);


dumpTree:
  type
    TypeName = object
      name : string
      age : int

#let t = TypeName(name:"hello", age:3)
#echo(t)

#
model User:
  pass

let u = User(name:"hello")
echo(u)

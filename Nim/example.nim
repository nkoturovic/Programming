import strformat

type Person = object
    name: string
    age: Natural

method info(self : Person) : string = &"{self.name} is {self.age} years old"
    
func square[T](num: T): T = num * num

echo(&"Square of 2 is {square(2)}")

case 2: 
    of 1: echo("one")
    of 2: echo("two")
    else: echo("Something else")

for i in countdown(10, 1, 2):
    echo &"{i}"

let p = Person(name:"John", age:25)
echo(p)
echo(p.info)

import sequtils
import sugar

let xs = toSeq(1..10).map(x => x + 1)
echo(xs)

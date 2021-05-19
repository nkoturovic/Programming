class Point (x : Float, y : Float) {
  override def toString: String = s"[$x, $y]"
}

object Vezbanje_02 {
  def main(args: Array[String]): Unit = {
    var v : Point = new Point(1,2)
    println(v + " dskjs")

    var ptoNum = Map("x" -> 0, "y" -> 1)
    println(ptoNum("x"))

    for ((k,v) <- ptoNum)
      println(k + " -> " + v)
  }
}

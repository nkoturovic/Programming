object Vezbanje_01 {
  def main(args: Array[String]): Unit = {
    var a : Int = 2
    a += 2 // Ok -> 4
    val pi = 3.14159236
    var (x,y,z) = (1,2,3)
    // pi += 1 // Error

    for (i <- 1 to 10)
      println(i)

    for (i <- 5 to 1 by -1)
      println(i) // 1 2 3
    for (i <- 1 until 3)
      println(i) // 1 2

    for (i <- Range(1,10,2))
      println(i) // 1 3 5 7 9

    val arr : Array[String] = Array("Hello", "World") // {"". ""}
    var filledArr : Array[String] = Array.fill(2)("Text") // {"". ""}
    arr(0) = "John"; arr(1) = "Cena"
    var lst : List[Int] = List(1,2,3,4)
    lst = lst.++(List(1,2,3))
    lst = 2 :: lst // Dodavanje 2 na pocetak liste
    lst :+ 9 // Slozenost velika
    var arr1 : Array[Int] = Array[Int]()
    arr1 = arr1 :+ 2
    arr1 = 1 +: arr1
    for (e <- arr1)
      println(e)
  }
}

import java.util.concurrent.ThreadLocalRandom

object MainObject {

  def main(args: Array[String]): Unit = {
    println("Hello world")

    // Array - Demonstration
    var xs: Array[Int] = Array[Int]()
    xs = xs :+ 1
    xs = 0 +: xs
    xs = xs ++ Array(2, 3, 4)
    val ys = (5 to 10 by 2).toArray
    xs ++= ys
    xs.foreach(x => println(x))

    // Citanje za stdin
    println("Unesite tekst: ")
    val in = scala.io.StdIn.readLine
    println(in)

    // Reading file
    val linije = scala.io.Source.fromFile("fajl.txt").getLines
    val result = linije.foldRight("")(_ + " - " + _)
    println(result)
   for (i <- 1 to 5) {
     val rand = ThreadLocalRandom.current().nextInt(1,4)
     println("Sleeping for " + rand + " seconds ...")
     Thread.sleep(rand*1000)
   }
  }
}

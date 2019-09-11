import java.io.PrintWriter
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue

import scala.reflect.io.File

object Jun_1_2019 {

  def main(args: Array[String]): Unit = {

    val scStdIn = new Scanner(System.in)

    var kljucnaRec = scStdIn.next()
    val brNiti = scStdIn.nextInt()

    //var nizPutanja : Array[String] = Array[String]()
    var nizPutanja = new ConcurrentLinkedQueue[String]()

    // Otvaranje datoteke sa putanjama
    val fPutanje = File("tajni_fajl.txt")
    for (l <- fPutanje.lines()) {
      nizPutanja.add(l)
    }

    var niti : Array[NitJun1] = Array[NitJun1]()

    for (putanja <- 1 to nizPutanja.size())
      niti = niti :+ new NitJun1(kljucnaRec, nizPutanja)

    if (niti.length < brNiti)
      println("Greska: fajlova mora biti vise ili jednako nego niti.")

    for (nit <- niti)
      nit.start()

     for (nit <- niti)
      nit.join()
  }
}

import java.util.concurrent.ThreadLocalRandom
import java.util.concurrent.atomic.{AtomicBoolean, AtomicInteger}

import org.apache.spark.util.random

import scala.collection.mutable.Map

class Nit_Jun_2(izvuceno: AtomicBoolean, ucesnik : String, var izvuceniKupci : Map[String, Int]) extends Thread {
  override def run(): Unit = {

      while (!izvuceno.get()) {
        izvuceniKupci.synchronized {
          izvuceniKupci.wait
        }
      }

  izvuceniKupci.synchronized{
    if (izvuceniKupci(ucesnik) != 0)
      println("Vaucer sa " + izvuceniKupci(ucesnik) + "% popsta dobio je " + ucesnik)
  }
    //else
      //println("Nije izvucen kupac: " + ucesnik)
  }
}

object Jun_2_2018 {

  def main(args: Array[String]): Unit = {
    /* Nagradna igra */
    /* 5 vaucera sa 20% popusta */
    /* 7 vaucera sa 10% popusta */
    /* 10 vaucera sa 50% popusta */
    /* ucesnici.txt */

    val fileContents = scala.io.Source.fromFile("ucesnici.txt").getLines()
    val brUcesnika = fileContents.next.toInt
    val ucesnici: Array[String] = fileContents.toArray
    var izvuceniKupci: Map[String, Int] = Map[String, Int]()
    var niti: Array[Nit_Jun_2] = Array[Nit_Jun_2]()
    var izvuceno: AtomicBoolean = new AtomicBoolean(false)

    for (u <- ucesnici) {
      niti = niti :+ new Nit_Jun_2(izvuceno, u, izvuceniKupci)
      izvuceniKupci += (u -> 0)
    }
    niti.foreach(t => t.start())

    val vauceri : Array[Int] = Array[Int](
      20, 20, 20, 20, 20,
      10, 10, 10, 10, 10, 10, 10,
      5, 5, 5, 5, 5, 5, 5, 5, 5, 5
    )

    izvuceniKupci.synchronized {
      var preostaloNagrada: Int = vauceri.length
      while (preostaloNagrada > 0) {
        val rand = ThreadLocalRandom.current().nextInt(0, brUcesnika)
        if (izvuceniKupci(ucesnici(rand)) == 0) {
          izvuceniKupci(ucesnici(rand)) = vauceri(preostaloNagrada-1)
          preostaloNagrada -= 1
        }
      }
    }

    izvuceniKupci.synchronized {
      izvuceniKupci.notifyAll()
    }

    izvuceno.synchronized{
      izvuceno.set(true)
    }

    niti.foreach(t => t.join())
    println("Threadovi zavrsili")
  }
}

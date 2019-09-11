import java.util.concurrent.atomic.AtomicLong
// Da bismo napravili nit potrebno je da definisemo klasu koja nasledjuje klasu Thread
// i implementiramo metod run cije izvrsavanje pocinje kada nad instancom nase klase
// pozovemo metod start.

class Nit (brojac : AtomicLong) extends Thread {
  override def run() {
    val tmp = brojac.get() + 1
    brojac.set(tmp)
    println("Zdravo iz niti: " + this.getId())
  }
}

object ZdravoNiti {
  def main(args : Array[String]): Unit = {
    var prom : AtomicLong = new AtomicLong(0)

    val niti : Array[Nit] = Array.fill(4)(new Nit(prom))

    /* Pocinjemo izvrsavanja iz razlicitih niti */
    for (nit <- niti)
      nit.start()

    println("Zdravo iz main-a")

    /* Cekamo niti da zavrse izvrsavanje */
    for (nit <- niti)
      nit.join()

    println("Niti zavrsile sa izvrsavanjem.")
    println(prom)
  }
}
import java.util.concurrent.ConcurrentLinkedQueue
import scala.reflect.io.File

class NitJun1 (kljRec : String, putanje : ConcurrentLinkedQueue[String]) extends Thread {
  override def run(): Unit = {

  var fpath : String = new String("")

    putanje.synchronized {
       fpath = putanje.poll()
    }

    val fname = fpath.substring(fpath.lastIndexOf('/') + 1, fpath.length())
    var sadrzaj : String = new String()

    try {
      val fajl = File(fpath)
      var  i = 1
      for (l <- fajl.lines()) {
          if (l.contains(kljRec))
            println(fname + " " + i)
        i = i + 1
      }
    } catch {
      case e : Exception => {
        println("Greska prilikom citanja fajla: " + e)
        System.exit(1)
      }
    }
    println(s"Nit <${this.getId}> je zavrsila sa radom!")
  }
}
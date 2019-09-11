import java.io.{File, PrintWriter}
import java.util.Scanner

object Vezbanje_03 {

  def main(args: Array[String]): Unit = {
    val sc: Scanner = new Scanner(System.in)
    sc.useDelimiter("\n| |;")

    val pw : PrintWriter = new PrintWriter("izlaz.txt")
    while (sc.hasNext()) {
      pw.println(sc.next())
    }
    pw.close() // Ne zaboraviti!!!
  }
}

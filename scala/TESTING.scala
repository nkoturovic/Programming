import java.util.concurrent._

//class Nit(mapa : ConcurrentHashMap[Char, Int]) extends Thread {
//}

//object Test {
//  def main(args: Array[String]): Unit = {
//    val mapa = new ConcurrentHashMap[Char, Int]
//    mapa.synchronized {
//      for ((i, j) <- ('a' to 'z').zip(1 to 30)) mapa.put(i, j)
//    }
//    val arr: Array[Nit] = Array.fill(10)(new Nit(mapa))
//  }
//}
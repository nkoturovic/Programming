import org.apache.spark._


object Jun_1_2019_Distribuirano {
  def convert(linija : String) : String = {
  var larr = linija.split(",").toArray
  var visina = larr(3).toInt * 2.54
  var tezina = larr(4).toInt * 0.45359237
  larr(3) = visina.toString
  larr(4) = tezina.toString
  var res = larr.foldRight(" ")(_ + "," + _)
  return res.substring(0, res.length-2)
}

  def main(args: Array[String]): Unit = {
    val cfg = new SparkConf()
        .setAppName("biostats")
        .setMaster("local[4]")

    val ctx = new SparkContext(cfg)

    val RDD = ctx.textFile("biostats.csv")
    .flatMap(_.split("\n"))
    .map(S => convert(S))
    .foreach(e => println(e))
  }
}

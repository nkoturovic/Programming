# TLDR; Ispit iz Programskih Paradigmi

## Scala
Koristimo `InteliJ Idea` kao razvojno okruženje.

### Hello, World
Projekat se kreira:
```
file > new > project > sbt 
Unese se ime projekta npr. `Zadatak1`, ubuduće `Project_dir`
```
Vaše rešenje treba da se nalazi u automatski kreiranom direktorijumu projekta:
`Project_dir > src > main > scala`

Prvo što treba da uradite je da napravite novi objekat koji sadrzi `main()` metod:
* U datom direktorijumu: **scala** u `Project_dir > src > main > **scala**`
* Napravire novi objekat: `New > Scala Class > Type: Object`
* Unutar njega definisete metod `main()`:
```scala
object ZdravoSvete {
  def main(args: Array[String]): Unit = {
    println("Zdravo, svete!")
  }
}
```
- `Shift+F10` je prečica za Run, pritisnite `Shift+F10`
```Zdravo, svete!```

### 1. Zadatak


### 2. Zadatak

* Podešavanje `Scala (Apache) Spark`:
Potrebno je izmeniti fajl `build.sbt`
```
name := "Zadatak2"
version := "0.1"
scalaVersion := "2.12.8"

// Potrebno je dodati sledece:
val sparkVersion = "2.4.0"
libraryDependencies ++= Seq(
   "org.apache.spark" %% "spark-core" % sparkVersion
)
```

Napravite novi objekat sa proizvoljnim imenom `ImeObjekta`:
```scala
object ImeObjekta {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf()
        .setAppName("Aplikacija")
        .setMaster("local[4]") // 4threada

    val sk = SparkContext(conf)
    val datRDD=sk.textFile("ulaz.txt")

    val result = datRDD
        .Metod1().Metod2() // ... Niz transformacija

    sk.stop()
    print("Rezultat: ")
    println(rezultat)
  }
}

```

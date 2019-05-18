# TLDR; Ispit iz Programskih Paradigmi

Ispit se sastoji iz dve celine `Scala` i `Prolog` po dva zadatka.
Zadaci:
1. **Scala**  
*1. zadatak:* Scala [Niti]  
*2. zadatak:* [Spark]  
2. **Prolog**  
*3. zadatak:* Prolog [-]  
*4. zadatak:* Prolog [Ogranicenja]  

## Deo 1. - Scala
Koristimo `InteliJ Idea` kao razvojno okruženje.

### Program - Zdravo, Svete (Scala)
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
* Unutar njega definišete metod `main()`:
```scala
object ZdravoSvete {
  def main(args: Array[String]): Unit = {
    println("Zdravo, svete!")
  }
}
```
- `Shift+F10` je prečica za Run, pritisnite `Shift+F10`
```
Zdravo, svete!
```

### 1. Zadatak


### 2. Zadatak
#### Podešavanje `Scala (Apache) Spark`:
Pre nego što počnete sa radom, potrebno je izmeniti fajl `build.sbt`
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
* Snimite build.sbt fajl.
* Nakon izvršenih izmena, dok se još nalazite u build.sbt u gornjem desnom uglu kliknite na `import project`. 

**Spremni ste za pisanje 2. zadatka!!**

#### Kostur za 2. zadatak

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
    println(result)
  }
}

```

## Deo 2. - Prolog

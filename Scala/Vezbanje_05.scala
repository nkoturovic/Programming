import javafx.application.Application
import javafx.scene.Scene
import javafx.stage.Stage
import javafx.scene.layout._
import javafx.scene.control._
import javafx.geometry._


class GuiAplikacija extends Application {

  override def start(primaryStage: Stage) {
    primaryStage.setTitle("App Title")
    /* VBox - nizemo nase elemente jedan ispod drugog */
    val root = new VBox(50)
    root.setAlignment(Pos.CENTER)
    root.setPadding(new Insets(50, 50, 50, 50))

    /* Prvi red u root VBox-u */
    val hbox1 = new HBox(50)
    hbox1.setAlignment(Pos.CENTER)
    val lbl1 = new Label("Unesite tekst: ")
    val tf1 =  new TextField()
    val btn1 = new Button("Prepisi")
    hbox1.getChildren.addAll(lbl1, tf1, btn1)

    /* Drugi red u root VBox-u */
    val hbox2 = new HBox(50)
    hbox2.setAlignment(Pos.CENTER)
    val ta2 = new TextArea()
    ta2.setPrefColumnCount(12)
    hbox2.getChildren.addAll(ta2)

    /* Dodajemo prvi i drugi red u root VBox */
    root.getChildren.addAll(hbox1, hbox2)

    /* Akcije */
    btn1.setOnAction(e => {
      ta2.setText(tf1.getText())
    })

    primaryStage.setScene(new Scene(root, 800, 600))
    primaryStage.show()
  }
}

object Vezbanje_05 {
  def main(args: Array[String]) = {
    Application.launch(classOf[GuiAplikacija], args: _*)
  }
}

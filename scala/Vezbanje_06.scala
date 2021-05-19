import javafx.application.Application
import javafx.scene.Scene
import javafx.stage.Stage
import javafx.scene.layout._
import javafx.scene.control._
import javafx.geometry._


class GuiAplikacija1 extends Application {

  override def start(primaryStage: Stage) {
    primaryStage.setTitle("App Title")
    val root = new HBox(50)
    root.setAlignment(Pos.BASELINE_CENTER)
    root.setPadding(new Insets(50, 50, 50, 50))

    val vbox1 = new VBox(50)
    val lbl1 = new Label("Unesite tekst: ")
    vbox1.getChildren.addAll(lbl1)

    val vbox2 = new VBox(50)
    val tf2 =  new TextField()
    val ta2 = new TextArea()
    ta2.setPrefColumnCount(12)
    vbox2.getChildren.addAll(tf2, ta2)

    val vbox3 = new VBox(50)
    val btn3 = new Button("Prepisi")
    vbox3.getChildren.addAll(btn3)

    /* Dodajemo prvi i drugi red u root VBox */
    root.getChildren.addAll(vbox1, vbox2, vbox3)

    /* Akcije */
    btn3.setOnAction(e => {
      ta2.setText(tf2.getText())
    })

    primaryStage.setScene(new Scene(root, 800, 600))
    primaryStage.show()
  }
}

object Vezbanje_06 {
  def main(args: Array[String]) = {
    Application.launch(classOf[GuiAplikacija1], args: _*)
  }
}
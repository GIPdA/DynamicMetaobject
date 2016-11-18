import QtQuick 2.7
import QtQuick.Controls 2.0
//import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Text {
        text: "Text: " + dyn.toto
    }

    Component.onCompleted: {
        print("Name: " + dyn.name)
        print("Test: " + dyn.test)
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            dyn.toto = 354;

            dyn.setToto(120);

            print(dyn.name)
        }
    }
}

import QtQuick 1.1

import GraphModule 1.1

Rectangle {
    width: 600
    height: 600
    color: "#cccccc"

    GraphWidget {
        x: 20
        y: 20
        width: 560
        height: 560

        color: "green"

        Component.onCompleted: console.log("+++ graph widget qml on complete ++");
    }


}


import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Controls 1.4

import CameraPlayer 1.0
import VisionResponse 1.0


Item {
  id: root
  width: Math.min(Screen.width, 1368)
  height: Math.min(Screen.height, 768)


  VisionResponse {
    id: vres
    anchors.top:  root.top
    anchors.left: root.left
    width: 800
    height: 600
    play: true
  }

  CameraPlayer {
    id: camera
    anchors.top: root.top
    anchors.left: vres.right
    width: 240
    height: 180
    play: true
  }



}

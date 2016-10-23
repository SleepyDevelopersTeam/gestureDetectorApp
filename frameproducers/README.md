# frameproducers

This directory is created specially for placing different frame producers here.
Every descendant of `AbstractFrameProducer` should be placed here by default.

Also it would be nice if you place a brief description of your class in this README.

## About Frame Producers

**Frame producer** is an entity that provides its consumers with video frames.
When a new video frame is available, it emits signal `FRAME_PRODUCED`.

Typically, we will have the only instance of the custom frame producer in running app.

## AbstractFrameProducer

The base abstract class for every frame producer. All of them should be inherited from this class to integrate properly in the system.
Has basic functionality used by every custom frame producer.

## WebCameraFrameProducer

Uses OpenCV `CameraCapture` to obtain video frames. Emits ~30 video frames per second
(very stable FPS is guaranteed). Const `30` may change at some time (not in runtime, of course).

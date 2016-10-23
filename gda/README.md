# gda

This directory is created specially for placing different GDAs here.
Every descendant of `AbstractGDA` should be placed here by default.

Also it would be nice if you place a brief description of your class in this README.

## About GDAs

**GDA** is a Gesture Detection Algorithm. It consumes video frames (see
`../frameproducers`) and tries to detect a gesture.
When a gesture is detected, it emits signal `GESTURE_DETECTED`.

Typically, we will have the only instance of the custom GDA in running app.

## AbstractGDA

The base abstract class for every GDA. All of them should be inherited from
this class to integrate properly in the system.

## HistogramGDA

Uses user shadows histograms to detect a gesture. See wiki and `../historgam` for more.

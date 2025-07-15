# Scope of Work (SOW) - CIS25 Final Project

**Author:** Luis Ibarra  
**Course:** Computer Information Systems 25  
**Institution:** BCC (Berkeley City College)  
**Submission Date:** July 2, 2025  
**Project Deadline:** July 2, 2025

---

## Project Overview

A **Scope of Work (SOW)** is an agreement between an employee/contractor and employer outlining services work to be completed by the employee. SOWs are used commonly in technology jobs and contract work.

This document outlines the scope, deliverables, milestones, and timeline for the CIS25 Final Project - an interactive C++ application featuring real-time face detection and augmented reality mask overlay functionality.

---

## Deliverables

### Project Description

**Application Name:** Interactive Face Mask & Particle Generator  
**Programming Language:** C++  
**Primary Technologies:** OpenCV, MongoDB Atlas, CLI Interface

### What Does It Do?

An interactive C++ program that starts on the command line interface (CLI) then transitions to camera functionality to overlay digital masks on the user's face and generate particle effects based on user choices. The application combines computer vision, database management, and real-time graphics processing.

### How Does It Work?

1. **CLI Interface:** User launches the program through command line and selects mask/particle options
2. **Camera Activation:** Program activates webcam and initializes OpenCV for real-time video processing
3. **Face Detection:** Uses OpenCV face detection algorithms to identify and track facial features
4. **Mask Overlay:** Applies selected digital mask overlay aligned with detected face position
5. **Particle Generation:** Creates particle effects emanating from mouth/face area based on user selection
6. **Data Persistence:** Stores user preferences and session data in MongoDB Atlas cloud database

---

## Milestones

### Core Features (Minimum Requirements)

#### 1. C++ to MongoDB Atlas Integration

- **Objective:** Establish database connectivity for reading and writing user data
- **Functionality:**
  - Store user preferences (mask choices, particle types)
  - Save session history and statistics
  - Read configuration settings from cloud database

#### 2. C++ to OpenCV Real-time Face Detection

- **Objective:** Implement computer vision for live face tracking
- **Functionality:**
  - Initialize webcam capture
  - Detect faces in real-time video stream
  - Track facial landmarks and orientation
  - Maintain stable detection across frames

#### 3. OpenCV Mask Overlay & Particle System

- **Objective:** Render augmented reality effects on detected faces
- **Functionality:**
  - Overlay digital masks aligned with face position
  - Generate particle effects from mouth area
  - Smooth animations and real-time rendering
  - Multiple mask and particle options

---

## Special Features - Future Development

### Enhanced Video Capabilities

- **Video Recording:** Record and save augmented reality sessions with applied masks and effects
- **Playback System:** Review recorded sessions with timestamp navigation
- **Export Options:** Save videos in multiple formats (MP4, AVI, GIF)

### Improved Face Detection

- **Advanced Tracking:** Enhanced facial landmark detection for better mask alignment
- **Multiple Face Support:** Detect and apply effects to multiple faces simultaneously
- **Gesture Recognition:** Respond to facial expressions and head movements
- **3D Mask Rendering:** Three-dimensional mask overlays with depth perception

_This document serves as the official project scope agreement for the CIS25 Final Project at Berkeley City College._

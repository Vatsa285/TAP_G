# Tap_G

A lightweight, configurable Linux touchpad gesture daemon built on top of **libinput**.

Tap_G listens for touchpad gestures, detects supported gestures, and maps them to user-defined commands through a JSON configuration file. It is designed with a modular architecture, making it easy to extend with new gestures, actions, and configuration options.

---

# Features

- Multi-finger touch gesture detection using **libinput**
- Configurable gesture-to-command mapping through JSON
- Secure command execution using `fork()` + `execvp()`
- Modular architecture with clear separation of responsibilities
- Easily extensible for future gesture types
- Lightweight with minimal runtime overhead

Current Supported Gestures:

- Three Finger Tap
- Four Finger Tap

---

# Architecture

```
                Touchpad
                    │
                    ▼
              Linux Kernel
                    │
                    ▼
                libinput
                    │
                    ▼
             InputManager
                    │
                    ▼
         TapGestureDetector
                    │
                    ▼
                Gesture
                    │
                    ▼
          CommandDispatcher
                    │
        ┌───────────┴───────────┐
        ▼                       ▼
 ConfigManager          CommandExecutor
        │                       │
        ▼                       ▼
    config.json          fork() + execvp()
                                │
                                ▼
                         Linux Process
```

---

# Project Structure

```
Tap_G/
│
├── include/
│      CommandDispatcher.h
│      CommandExecutor.h
│      ConfigManager.h
│      Gesture.h
│      InputManager.h
│      TapGestureDetector.h
│
├── src/
│      CommandDispatcher.cpp
│      CommandExecutor.cpp
│      ConfigManager.cpp
│      InputManager.cpp
│      TapGestureDetector.cpp
│
├── config/
│      config.json
│
├── CMakeLists.txt
│
└── README.md
```

---

# Design Philosophy

The project follows the **Single Responsibility Principle**.

Every component has one well-defined responsibility.

## InputManager

Responsible for:

- Initializing libinput
- Polling input events
- Passing events to the gesture detector
- Dispatching detected gestures

Not responsible for:

- Gesture detection
- Command execution
- Configuration parsing

---

## TapGestureDetector

Responsible for:

- Detecting supported gestures
- Producing Gesture objects

Input:

```
libinput_event*
```

Output:

```
std::optional<Gesture>
```

The detector is completely independent from command execution.

---

## Gesture

Represents a detected gesture.

Example:

```
ThreeFingerTap

FourFingerTap
```

Gesture objects carry no execution logic.

---

## CommandDispatcher

Acts as the bridge between gesture detection and command execution.

Workflow:

```
Gesture
    │
    ▼
ConfigManager
    │
    ▼
CommandExecutor
```

The dispatcher never knows how commands are stored or executed.

---

## ConfigManager

Responsible for:

- Loading configuration
- Parsing JSON
- Mapping gestures to commands

Internally stores

```
GestureType
        │
        ▼
vector<string>
```

It has no knowledge of libinput or process creation.

---

## CommandExecutor

Responsible only for launching Linux processes.

Workflow

```
vector<string>

↓

argv[]

↓

fork()

↓

execvp()
```

No shell is involved.

---

# Gesture Detection

Current gesture detection uses libinput gesture events.

Example:

```
Finger Down

↓

LIBINPUT_EVENT_GESTURE_HOLD_BEGIN

↓

Store

• Finger Count
• Start Time

↓

LIBINPUT_EVENT_GESTURE_HOLD_END

↓

Measure Duration

↓

If duration < threshold

↓

Generate Gesture
```

Currently supported

- Three Finger Tap
- Four Finger Tap

---

# Configuration

Gesture mappings are stored in JSON.

Example

```json
{
    "ThreeFingerTap": [
        "playerctl",
        "play-pause"
    ],

    "FourFingerTap": [
        "xdotool",
        "key",
        "Alt+Tab"
    ]
}
```

Each command is represented as an array of arguments instead of a single shell command.

Advantages

- No shell parsing
- Handles spaces correctly
- Compatible with execvp()
- Safer than shell command strings

---

# Command Execution

Tap_G executes commands using

```
fork()

+

execvp()
```

instead of

```
system()
```

Workflow

```
Gesture

↓

JSON

↓

vector<string>

↓

argv[]

↓

fork()

↓

Child Process

↓

execvp()

↓

Linux Process
```

---

# Why Not system()?

Earlier versions used

```cpp
system(command.c_str());
```

This approach was replaced because `system()`:

- launches an extra shell
- requires shell parsing
- is slower
- is vulnerable to shell injection if commands are untrusted

Current implementation directly executes the requested program using `execvp()`.

Benefits:

- No shell
- Faster execution
- Cleaner architecture
- Better security
- Direct argument passing

---

# Dependencies

Required packages

```
libinput
libudev
nlohmann-json
CMake
C++17 Compiler
```

Ubuntu

```bash
sudo apt install \
libinput-dev \
libudev-dev \
nlohmann-json3-dev
```

---

# Building

```bash
git clone <repository>

cd Tap_G

mkdir build

cd build

cmake ..

make
```

Run

```bash
./tap_g
```

---

# Current Workflow

```
Touchpad

↓

libinput

↓

InputManager

↓

TapGestureDetector

↓

Gesture

↓

CommandDispatcher

↓

ConfigManager

↓

CommandExecutor

↓

fork()

↓

execvp()

↓

Linux Command
```

---

# Future Roadmap

## Version 1.0

- [x] Gesture Detection
- [x] JSON Configuration
- [x] Command Dispatcher
- [x] fork()+execvp()
- [ ] XDG Configuration Support
- [ ] Installable Project
- [ ] systemd User Service

---

## Version 1.1

- Swipe Gestures
- Pinch Gestures
- Long Press
- Logging
- Graceful Shutdown

---

## Version 2.0

- Plugin Architecture
- GUI Configuration Tool
- Per-Application Gesture Profiles
- Live Configuration Reload
- Custom Actions

---

# Planned Installation Layout

```
/usr/local/bin/
    tap_g

/usr/local/share/tap_g/
    config.json

~/.config/tap_g/
    config.json
```

The file in `/usr/local/share` serves as the default template, while each user customizes their own configuration under `~/.config/tap_g/`.


# Acknowledgements

- Linux libinput
- libudev
- nlohmann/json
- CMake
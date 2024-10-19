# 2D Infinite Runner Game

## Project Description
This is a 2D infinite runner game developed in C++ using OpenGL for graphics rendering and OpenAL for sound management.

## Setup Instructions

### Prerequisites
To run this project, you will need:
1. **OpenGL** (for rendering)
2. **OpenAL** (for audio)
3. A C++ compiler (Visual Studio, GCC, etc.)
4. **GLUT** (for handling OpenGL windowing)

### Instructions to Set Up the Environment

#### 1. Download OpenAL and OpenGL Dependencies
You need to download and install **OpenAL** and **GLUT** manually.

- **OpenAL Soft**: 
  Download from the official site: [OpenAL Soft Downloads](https://openal-soft.org/#download)

  After downloading, copy the necessary `.dll`, `.lib`, and header files to the appropriate folders (`/lib/` and `/include/`).

- **GLUT**: 
  Download the GLUT library from: [GLUT for Windows](https://www.opengl.org/resources/libraries/glut/).

- After downloading, copy the necessary `.dll`, `.lib`, and header files to the appropriate folders (`/lib/` and `/include/`) and right click on the .dll files and change "Item type" to "Copy file" to ensure it is included in build.
- Set the path to include directory from project properties to the include folder you created.
- In Linker, add glut32.lib and OpenAL32.lib to the additional dependencies.

##### Result
Your include and lib folders should look like this:
```
2D-Infinite-Runner/
├── include/
│   ├── AL/
│   │   ├── al.h
│   │   ├── alc.h
│   │   ├── alext.h
│   │   ├── efx.h
│   │   ├── efx-creative.h
│   │   └── efx-presets.h
│   └── GL/
│       └── glut.h
└── lib/
	├── OpenAL32.lib
	├── glut32.lib
	├── openAL32.def
	├── OpenAL32.dll
	├── OpenAL32.lib
	└── opengl32.lib
```

#### 2. Set Up the Project

1. Clone the repository:
   ```bash
   git clone https://github.com/yourrepo/2D-Infinite-Runner.git
   cd 2D-Infinite-Runner

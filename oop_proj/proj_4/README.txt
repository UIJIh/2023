1. Confirmed to run on Visual Studio 2022. 
2. Install the DirectX SDK June 2010 within the project, and run VS 2022 from the project folder using the .sln file.
- To build the project, press "Build" or the "F7" key.
- After a successful build, to run the program, press "Start Debugging" or "Ctrl+F5."
- press "Esc" to exit the program.
3. DirectX SDK: https://www.microsoft.com/en-us/download/details.aspx?id=6812
4. The default .gitignore for Visual Studio is applied.
5. Due to the large size of the DirectX library, it is excluded from .gitignore.
- Therefore, before running, create a folder named "DirectX" in the project folder and install the DirectX SDK, then it should build successfully.
- Since the library path in the project is set to <project folder path>/DirectX/..., do not change the path in the project properties without specifying it.
- Make sure to create the "DirectX" folder in the project, and do not install the SDK elsewhere.


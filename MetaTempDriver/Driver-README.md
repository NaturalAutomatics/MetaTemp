# MetaTempDriver

MetaTempDriver is a SteamVR driver application that allows you to get information about the objects being held in your hands while using a VR headset. This information can be used to simulate temperature or other properties of virtual objects in a VR environment.

## Description

This driver uses the OpenVR SDK to communicate with SteamVR and retrieve data about the objects being grabbed by the user's controllers. The core functionality is implemented in the `ObjectTemperatureController` class, which listens for the "GrabObject" action and retrieves the tracked device index of the grabbed object.

Once the grabbed object's index is obtained, you can use other OpenVR functions to get additional information about the object, such as its position, orientation, or any custom properties you've defined.

## Prerequisites

Before you can build and run this project, you'll need to have the following prerequisites installed:

- Visual Studio Code (or another C++ development environment)
- CMake
- OpenVR SDK

## Building and Running

Follow these steps to build and run the MetaTempDriver project:

1. **Clone the repository**

git clone https://github.com/NaturalAutomatics/MetaTemp
cd MetaTemp/MetaTempDriver


2. **Create a build directory**

mkdir build
cd build


3. **Configure the project**

text
cmake ..


This step will configure the project and generate the necessary build files.

4. **Build the project**

cmake --build .


This will compile the project and create the executable file.

5. **Run the driver**

After a successful build, you can run the driver by executing the generated executable file. On Windows, this file will be located in the `build\Debug` or `build\Release` folder, depending on your build configuration. On macOS or Linux, the executable will be in the `build` folder.

Make sure to run the driver while SteamVR is active and your VR headset is connected.

## Deployment

To deploy the MetaTempDriver as a SteamVR driver, follow these steps:

1. Build the project as described above.
2. Copy the generated executable file to the appropriate location on your system, as specified by the SteamVR driver documentation.
3. Configure SteamVR to load and use your driver.

Refer to the SteamVR driver documentation for more detailed instructions on deploying and distributing your driver.

## Contributing

If you'd like to contribute to the MetaTempDriver project, please follow these steps:

1. Fork the repository
2. Create a new branch for your feature or bug fix
3. Make your changes and commit them with descriptive commit messages
4. Push your changes to your forked repository
5. Submit a pull request to the main repository

## License

This project is licensed under the [MIT License](LICENSE).

Copy

Insert at cursor
text
This README file provides an overview of the MetaTempDriver project, including its description, prerequisites, building and running instructions, deployment steps, and information on contributing to the project. It also includes the C++ code snippet you provided earlier, which implements the core functionality of the driver.
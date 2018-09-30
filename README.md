# The Generic Controller (gentroller) platform

*Note: Please note that this project is in very early stages of elaboration.*

# Scope
The purpose of the gentroller platform is to offer a very simple framework for a Linux based control system. The platform executes in Linux user space without requiring any specialized support in the kernel. The assumption is that all the sensors and actuators are connected using Ethernet (TCP/IP), serial (RS-232, RS-422/485), GPIB, IEEE 488.2 etc. protocols. 

# Targetted architecture
At the high level the archtiecture may be broken down into three main components:
1. Controller core - A high performance core system where all the device controllers reside. The core framework as well as the device drivers are implemented using C++ with extensive use of the BOOST library.
2. Interface backend - A web interface backend, implemented in Python. The purpose of the web backend is to offer all the controller management services, offer a user interface and provice high level functions such as file management, configuration management etc. The interface backend offers a rest API to the user web interface. It bridges the user requests towards the core.
3. The user web interface - The web interface offers user graphical ingerface that enables the user to operate the controller.

*Note: More design information will be provided as the system is implemented*


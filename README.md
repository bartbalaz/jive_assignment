# Challenge implementation

## Review of the use case
The implementation performs the following tasks:
1. A registration dump file is read, parsed and stored by the server application.
2. The server application starts a TCP listener socket on a port assigned through the arguments.
3. The client sends AOR values that tirgger the server to return the registration body.
4. Queries of AOR values that are not in the registration dump file trigger the server to issue an empty line response (CR/LF).
5. After 10 seconds of inactivity the server tears down the TCP session.


## Assumptions
The following assumptions have been made:
1. There is no requirement for a complete JSON parser. Each registration is stored using a key-value scheme where the key is the AOR, while the registration record is the value in a blob format.
2. There may be multiple registrations. In that case the server will issue all available records.
3. All client requests are separated by CR/LF.
4. The client requests contain only AOR values and CR/LF characters, there are no other characters.
5. The registration dump file contains only 7-bit UTF-8 characters.
6. The implementation may have the following limitations:
- Basic logging system: No levels, not deactivated in release build etc.
- No recovery code: In some situations when facing issues the application stops instead of attempting to recover. For example, the application stops if the registration dump file is not properly formated. 
- Limited portability: The application will only execute on a single system.
- Limited corner cases: The application only covers the most obvious use (misuse) cases.
- Basic coding style: No specific coding style was specified.

## Design
The implementation consists in 3 parts:
1. Common: contains the implementation required by the client and the server. Namely it contains a trivial thread safe logging functionlity (log.c/.h) the parser and storage of the registration records (aor.c/.h) both services are compiled into library libcommon.a. The registration records are stored in a hash table in a Key-Value structure where the key is the AOR while the value is the entire registration record (includig AOR). The hash function is trivial, it consists in adding all the values of all the characters in the AOR. The hash function was not tested for efficiency. Multiple registration records may be stored with the same AOR (key).
2. Server (server.h/.c, main.c): Contains the implementation of the server main function. The server starts individual threads (pthreads) for each client connection. The client connections are polled with a 10 sec timeout if no data is received during tha time the connection is closed. The server parses each request and attemps to locate the registration record in the 
3. Client (client.h/.c main.c): Contains a trivial implementation of the basic use case. When launched the client queries the server for simple records, it queries for inexistent records and multiple records (int the case the same AOR is associated to multiple registration records). Also, it issues multiple queries in the single TCP segment.

## Environment
The code has been developped using gcc version 5.4.0-6 on Ubuntu linux 16.04 it was not tested on other environments. The only additional library required to build the application is libpthreads (which comes standard with any modern Linux distribution). The application is built using GNU Make 4.1. The make system was imported from one of my earlier projects.

## Structure of the repository and build
The main folder of the repository contains the following subdirecories:
- doc: Contains the assignment document and the registration dump file.
- evaluation: Contains all the source code.
- makefiles: Contains all the makefile rules and defintions used in the build process.
- target: This dirctory is generated by the build process it contains a tree that branches correspond the artefacts (executables, libraries, object, tests) and the build configuration (platform: Intel Linux or ARM Linux, mode: debug or release).
The application is build by issuing *make* command in *evaluation* directory. The binaries will be generated in: */target/bin/ilinux/debug* folder (by default the builds are targetting Intel *Linux* in *debug* configuration.


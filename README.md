# getpass-cli

It is a command line tool which I made to retrieve my various passwords from a hidden text file.


## Text file format

File which will be containing your passwords should follow the following format:
```
KEY_1: VALUE_1
KEY_2: VALUE_2
.
.
.
KEY_N: VALUE_N
```
#### Example:
```
Facebook: 123#xdkyslz
Google: 2@3a3#xdkyslz
.
.
.
Microsoft: 234@34u5pz
```

## Setup

- Change the password and the path to your hidden file in the program.
- Compile the program using following command:
```
g++ -std=c++17 <cpp_file_name> -o <executable_name>
```
- Set the path to the executable file directory in your environment variables.
- You are now ready to call the command from anywhere by typing ``executable_name`` in your terminal.

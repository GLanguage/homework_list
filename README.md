# homework_list
A list of homework :P  
[CHANGELOG](CHANGELOG.md)

## Usage
*NOTE: Unix-like OS only!*  
After cloning the repo, you need to do some settings.
### Change the Path
Open `./src/cli.cpp`, then you will find something like:
```cpp
const string ROOT = "/Users/Alan/homework_list/";
```
Change it to the path to *your* repo.  
*NOTE: Remember to add `/` at the end!*
### Create Folders
`cd` into the repo, and add 2 folders: `./obj` and `./bin`.
### Set PATH Variable
Open (or create) terminal profile (`.bash_profile`, `.bashrc`, `.zshrc` or something like that under `~/` or `etc/`) and add:
```shell
export PATH=[path-to-the-repo]/bin/:PATH
```
And, obviously, `[path-to-the-repo]` means the path to the repo (without `/` at the end) .  
After doing all these complicated settings, you can finally `cd` into the repo and run:
```shell
$ make
$ make clean
```
where `make` will compile the repo and `make clean` will remove the `*.o` files.  
Then, you can start the program by command `homework`. Run
```shell
$ homework help
```
for further information.  
If you want to uninstall the program *(which is strongly not recommended)* , run:
```shell
$ make uninstall
```
which will remove the executable.

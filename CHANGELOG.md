# 1.1
**BREAKING CHANGE**
## Changed
In the past, when running `append`/`remove`, subject name (or item number) is required after the command.  
But now, it is required in the command. For example,
```shell
$ homework append subject Math
$ homework remove item Math 2
```
*NOTE: Item description is still required after the command.*  
Run `homework append help` and `homework remove help` to see more.
## Removed
`show` command is removed.
## Supported
Now you can `list`/`append`/`remove` more than 1 subject/item in a single command. For example,
```shell
$ homework list Math English
$ homework append subject PE Physics
$ homework remove item History 1 4 5
```
## Fixed
None.

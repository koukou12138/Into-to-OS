# Project1

Project1, UNIX Utilities, contains three utilities that are (mostly) versions or variants of commonly-used commands.

Files: my-look.c, across.c, my-diff.c.


## my-look.c

my-look takes a string as input and return any lines in a file that contain that string as an input. If a file isn't specified, the file /usr/share/dict/words is used by default.

## Compile

```bash
prompt> gcc -o my-look my-look.c -Wall -Werror
```

## Usage

```bash
prompt> ./my-look [substring] [file_path]
```
or
```bash
prompt> ./my-look [substring]
```

## across.c

across will find words of a specified length in the file that contains a specified substring at a specified position. If a file isn't specified, the file /usr/share/dict/words is used by default.

## Compile

```bash
prompt> gcc -o across across.c -Wall -Werror
```

## Usage

```bash
prompt> ./across [substring] [substirng_start_position] [string_length] [file_path]
```
or
```bash
prompt> ./across [substring] [string_length] [substirng_start_position]
```
## my-look.c

my-diff will compare line i from file A and line i from file B; if the two lines are identical, my-diff prints nothing; if the two lines are different, my-diff prints out the line number followed by the line i from file A and from file B.  

## Compile

```bash
prompt> gcc -o my-diff my-diff.c -Wall -Werror
```

## Usage

```bash
prompt> ./my-diff [file1] [file2]
```
# lab1
> 计卓1701 张淇 U201714466

## Environment
MacOS\
flex : 2.5.35\
bison : 2.3\
clang : 11.0.0

## Build

```
To build the project :

% make

To test the project :

% make test

To compile a mini-C file:

%./parser <filename>

To compile a mini-C file and output the AST-tree in a new file:

%./parser <filename> > <output file>

To clean the project:

%make clean
```

## Support language extra details

-   struct 
    > struct newStruct\
     {\
        int a,b;\
        float n,m;\
     } \
     x,y[100];

    > struct newStruct z;
- array
    > int a[1000];
    
    >int a[10][100];

    >struct newStruct z[10][100];

    > a[i];
- char
    > char a,b[100];

    > a = 'a';
- string const
    > "abcd\n\\\"";

    > b = "abcd\n\\\"";
- for
    > for (i=1;i<=n;i++)

    > for(;i<=n;i++)

    >for(;i<=n;)
- comment\
    support C/C++ style comment
    > // Line Comment

    > /*\
        Block Comment \
    */
- ++,--
    > i++,++i
    
    >i--,--i
- +=,-=,*=,/=
- synthesize usage
    > a[2][3] = z[1][2].a;

    > z[1][2].a = z[3][4].b;

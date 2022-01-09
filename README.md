[![Build status](https://ci.appveyor.com/api/projects/status/6vcjm0uflrhkdi25?svg=true)](https://ci.appveyor.com/project/peterpostmann/byteorder-eq53k)
# byteorder
determine endianness / byte order

## Problem Statement
Following up on various sources, including this one: https://stackoverflow.com/questions/2100331/c-macro-definition-to-determine-big-endian-or-little-endian-machine I tried to find a way to detect endianess in a way, that it can be used by the preprocessor. My final goal, was to work with utf8 charackters, which I want to treat as uint32_t. There is a way to use '\Uxxxxxxxx' as wide char constant, but this is only supported recently and it does not support invalid unicode codepoints.

## Solution
This header file implements a way to determine endianess and access the information. It may seem bloated, but it's done in way which will not yield compiler warnings (respectivly turns them of the few lines where they occure).

## Usage

Simply include it in your project: ```#include "byteorder.h"```

## Examples

Check the test file for more details.

**Check for endianess**

```BO_HOST_ORDER``` can be tested against ```BO_LITTLE_ENDIAN, BO_BIG_ENDIAN, BO_PDP_ENDIAN, BO_HONEYWELL_ENDIAN```


**Get an int from bytes**

```BO_NTOH4``` can be used to get an int from bytes ```uint32_t i = BO_NTOH4('L', 'G', 'B', 'T')``` which will be equal to ```unsigned char c[] = { 'L', 'G', 'B', 'T' }```. But since everything is done by the preprocessor, you can also use it in other places, e.g. a switch-statement:

```C
unsigned char c[] = { 'L', 'G', 'B', 'T' };

switch(*((uint32_t*) c))
{
  case BO_NTOH4('L', 'G', 'B', 'T'): ...
}
```

**Check unicode codepoints**

```C
unsigned char c[] = "👭";

switch(*((uint32_t*) c))
{
  case BO_CTUTF8(0x1F46D): ...
}
```

## Limitations

This code is tested on gcc, clang and msvc.
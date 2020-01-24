# a85-native
Node.js binding for [larskholte/a85](https://github.com/larskholte/a85).

> From Wikipedia:
Ascii85, also called Base85, is a form of binary-to-text encoding developed by Paul E. Rutter for the btoa utility. By using five ASCII characters to represent four bytes of binary data (making the encoded size ​1⁄4 larger than the original, assuming eight bits per ASCII character), it is more efficient than uuencode or Base64, which use four characters to represent three bytes of data (​1⁄3 increase, assuming eight bits per ASCII character). [source](https://en.wikipedia.org/wiki/Ascii85)


## Documentation
> `a85.stringify(input: Buffer): string`
>
> - Encode a `Buffer` in ascii85

> `a85.parse(input: string): Buffer`
>
> - Decode an ascii85 string into a Buffer
>
> **Note: This method will not detect invalid ascii85 string!**

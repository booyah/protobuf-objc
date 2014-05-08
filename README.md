Protocol Buffers for Objective-C
=================

An implementation of Protocol Buffers in Objective C.

Protocol Buffers are a way of encoding structured data in an efficient yet extensible format.
This project is based on an implementation of Protocol Buffers from Google.  See the
[Google protobuf project][g-protobuf] for more information.

[g-protobuf]: https://developers.google.com/protocol-buffers/docs/overview

This fork contains only ARC version of library.

## How To Install Protobuf
1.`ruby -e "$(curl -fsSL https://raw.github.com/Homebrew/homebrew/go/install)"`

2.`brew install automake`

3.`brew install libtool`

4.`brew instal protobuf`

5.`git clone git@github.com:alexeyxo/protobuf-objc.git`

6.`./build.sh`

## Compile ".proto" files. 
`protoc --plugin=/usr/local/bin/protoc-gen-objc person.proto --objc_out="./"`

## Example

### Web

Server-side requires Ruby(2.0+) and Sinatra gem.

To start `ruby sinatra.rb` in /Example/Web

if you need to recompile ruby proto models please install ruby_protobuf gem and make 'rprotoc person.proto'

### iOS Example
/Example/iOS/Proto.xcodeproj

Project contains protobuf example and small json comparison.

### Credits

Booyah Inc.
- Jon Parise

Google Protocol Buffers, Objective C
- Cyrus Najmabadi
- Sergey Martynov

Google Protocol Buffers
- Kenton Varda, Sanjay Ghemawat, Jeff Dean, and others

protoc  --plugin=/usr/local/bin/protoc-gen-objc google/protobuf/unittest* --objc_out="./Tests";
protoc  --plugin=/usr/local/bin/protoc-gen-objc google/protobuf/descriptor* --objc_out="./Tests";
cp -f ./Tests/Unittest* ../runtime/Tests/;
cp -f ./Tests/Descriptor* ../runtime/Classes/;

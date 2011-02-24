MAINTAINERCLEANFILES = \
	Makefile.in

bin_PROGRAMS = protoc-gen-objc
protoc_gen_objc_LDFLAGS = -lprotobuf -lprotoc
protoc_gen_objc_SOURCES = 	\
	main.cc					\
	objc_enum_field.cc		\
	objc_file.cc			\
	objc_message_field.cc	\
	objc_enum.cc			\
	objc_generator.cc		\
	objc_primitive_field.cc	\
	objc_extension.cc		\
	objc_helpers.cc			\
	objc_field.cc			\
	objc_message.cc			\
	google/protobuf/objectivec-descriptor.pb.cc

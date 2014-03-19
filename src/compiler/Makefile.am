MAINTAINERCLEANFILES = \
	Makefile.in
DEFINES = OBJC_ARC
bin_PROGRAMS = protoc-gen-objc protoc-gen-objc-arc
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
protoc_gen_objc_arc_LDFLAGS = ${protoc_gen_objc_LDFLAGS}
protoc_gen_objc_arc_SOURCES = ${protoc_gen_objc_SOURCES}
protoc_gen_objc_arc_CPPFLAGS = -D${DEFINES}
